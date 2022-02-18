
#pragma once
#include "Queues.hpp"

inline namespace SwapChainSupportDetails
{
  static inline VkSurfaceCapabilitiesKHR capabilities{};

  static inline VkImageLayout  depthImageView;
  static inline VkSwapchainKHR swapChain;
  static inline uint32_t       count;
  static inline uint32_t       imageCount;

  static inline VkSurfaceFormatKHR swapChainImageFormat;
  static inline VkPresentModeKHR   presentMode;
  static inline VkImageView        swapChainImageViews[VkUtilsXBase::Frames];
  static inline VkRenderPass       renderPass;
  static inline VkExtent2D         swapChainExtent;
  static inline VkImage            swapchainImages[VkUtilsXBase::Frames];
  static inline VkFramebuffer      swapChainFramebuffers[VkUtilsXBase::Frames];

  inline uint32_t clamp( uint32_t min, uint32_t max, uint32_t value )
  {
    const uint32_t a = ( max < value ? max : value );
    return ( min > a ? min : a );
  }
  inline VkExtent2D chooseSwapExtent()
  // todo: May not Detect Acutal Extent Correctly"
  {
    if ( capabilities.currentExtent.width != 0xFFFFFFFF )
    {
      return capabilities.currentExtent;
    }

    VkExtent2D actualExtent = { VkUtilsXBase::width, VkUtilsXBase::height };

    VkExtent2D minExtent = capabilities.minImageExtent;
    VkExtent2D maxExtent = capabilities.maxImageExtent;

    actualExtent.width  = clamp( minExtent.width, maxExtent.width, actualExtent.width );
    actualExtent.height = clamp( minExtent.height, maxExtent.height, actualExtent.height );

    return actualExtent;
  }

  inline void setupImageFormats()
  {
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR( Queues::physicalDevice, Queues::surface, &capabilities );

    vkGetPhysicalDeviceSurfaceFormatsKHR( Queues::physicalDevice, Queues::surface, &count, nullptr );
    VkSurfaceFormatKHR surfaceFormats[count];

    if ( count != 0 )
    {
      vkGetPhysicalDeviceSurfaceFormatsKHR( Queues::physicalDevice, Queues::surface, &count, surfaceFormats );
    }

    vkGetPhysicalDeviceSurfacePresentModesKHR( Queues::physicalDevice, Queues::surface, &count, nullptr );
    VkPresentModeKHR presentModes[count];
    if ( count != 0 )
    {
      vkGetPhysicalDeviceSurfacePresentModesKHR( Queues::physicalDevice, Queues::surface, &count, presentModes );
    }

    VkSurfaceFormatKHR surfaceFormat;
    for ( const VkSurfaceFormatKHR & surfaceFormat1 : surfaceFormats )
    {
      if ( surfaceFormat1.format == VK_FORMAT_B8G8R8A8_SRGB &&
           surfaceFormat1.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR )
      {
        surfaceFormat = surfaceFormat1;
        break;
      }
    }

    for ( const VkPresentModeKHR & presentMode1 : presentModes )
    {
      if ( presentMode1 == VK_PRESENT_MODE_IMMEDIATE_KHR )
      {
        presentMode = presentMode1;
        break;
      }
      else
      {
        presentMode = VK_PRESENT_MODE_FIFO_KHR;
      }
    }

    // return VK_PRESENT_MODE_FIFO_KHR;

    VkExtent2D extent = SwapChainSupportDetails::chooseSwapExtent();
    imageCount        = ( SwapChainSupportDetails::capabilities.minImageCount + 1 );

    if ( SwapChainSupportDetails::capabilities.maxImageCount > 0 &&
         imageCount > SwapChainSupportDetails::capabilities.maxImageCount )
    {
      imageCount = SwapChainSupportDetails::capabilities.maxImageCount;
    }

    SwapChainSupportDetails::swapChainImageFormat = surfaceFormat;
    SwapChainSupportDetails::swapChainExtent      = extent;
  }
  inline void createSwapChain()
  {
    std::cout << "ImageCount: " << imageCount << "\n";

    const uint32_t aa[] = { Queues::graphicsFamily, Queues::transferFamily };
    ;

    const VkSwapchainCreateInfoKHR createInfo{

      .sType   = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .pNext   = nullptr,
      .surface = Queues::surface,

      // Image settings
      .minImageCount    = imageCount,
      .imageFormat      = swapChainImageFormat.format,
      .imageColorSpace  = swapChainImageFormat.colorSpace,
      .imageExtent      = swapChainExtent,
      .imageArrayLayers = 1,
      .imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

      // if (graphicsFamily != presentFamily) {
      .imageSharingMode      = VK_SHARING_MODE_CONCURRENT,
      .queueFamilyIndexCount = 2,
      .pQueueFamilyIndices   = aa,
      // } else {
      // .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
      // .queueFamilyIndexCount = 0; // Optiona,
      // .pQueueFamilyIndices = nullptr; // Optiona,
      // }

      .preTransform   = SwapChainSupportDetails::capabilities.currentTransform,
      .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
      .presentMode    = presentMode,
      .clipped        = true,

      .oldSwapchain = VK_NULL_HANDLE
    };
    std::cout << Queues::device << "\n";

    // vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain);
    // auto xx=PFN_vkVoidFunction(swapChain);
    VkUtilsXBase::checkCall( vkCreateSwapchainKHR( Queues::device, &createInfo, nullptr, &swapChain ) );

    // checkCall(vkGetSwapchainImagesKHR(device, swapChain, &imageCount,
    // nullptr));

    // if(imageCount!=Frames)
    // {
    //     throw std::runtime_error("Swapchains not equal to allocated length: Bad
    //     SwapChain");
    // }
    VkUtilsXBase::checkCall( vkGetSwapchainImagesKHR( Queues::device, swapChain, &imageCount, swapchainImages ) );
  }

  inline void createImageViews()
  {
    std::cout << ( "Creating Image Views" ) << "\n";
    int i = 0;
    for ( const VkImage & swapchainImage : swapchainImages )
    {
      VkImageViewCreateInfo createInfo = {};
      createInfo.sType                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

      createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
      createInfo.format   = swapChainImageFormat.format;

      //     createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
      // createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
      // createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
      //     createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

      createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
      createInfo.subresourceRange.baseMipLevel   = 0;
      createInfo.subresourceRange.levelCount     = 1;
      createInfo.subresourceRange.baseArrayLayer = 0;
      createInfo.subresourceRange.layerCount     = 1;

      createInfo.image = swapchainImage;

      VkUtilsXBase::clPPPI(
        &createInfo,
        "vkCreateImageView",
        &SwapChainSupportDetails::swapChainImageViews[i++] );  // BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!
    }
  }

  inline void createFramebuffers()
  {
    VkFramebufferCreateInfo framebufferCreateInfo = {};
    framebufferCreateInfo.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCreateInfo.renderPass              = renderPass;
    framebufferCreateInfo.width                   = swapChainExtent.width;
    framebufferCreateInfo.height                  = swapChainExtent.height;
    framebufferCreateInfo.layers                  = 1;

    framebufferCreateInfo.attachmentCount = 1;  //(framebufferCreateInfo.address(), (attachments).remaining());
                                                //    framebufferCreateInfo.pAttachments= swapChainImageViews;
    for ( size_t i = 0; i < VkUtilsXBase::Frames; i++ )
    {
      framebufferCreateInfo.pAttachments = &swapChainImageViews[i];

      VkUtilsXBase::clPPPI( &framebufferCreateInfo, "vkCreateFramebuffer", &swapChainFramebuffers[i] );
    }
  }

}  // namespace SwapChainSupportDetails
