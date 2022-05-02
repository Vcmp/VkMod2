#pragma once

#include "Queues.hpp"
#include <vulkan/vulkan_core.h>

inline namespace SwapChainSupportDetails
{
  static constinit inline VkSurfaceCapabilitiesKHR capabilities{};

  static constinit inline VkImageLayout  depthImageView;
  static constinit inline VkSwapchainKHR swapChain;
  static constinit inline uint32_t       count;
  static constinit inline uint32_t       imageCount;

  static inline VkSurfaceFormatKHR         swapChainImageFormat;
  static constinit inline VkPresentModeKHR presentMode;
  static constinit inline VkImageView      swapChainImageViews[Frames];
  static constinit inline VkRenderPass     renderPass;

  static inline constexpr const VkExtent2D swapChainExtent{ width, height };

  static constinit inline VkImage       swapchainImages[Frames];
  static constinit inline VkFramebuffer swapChainFramebuffers[Frames];

  inline uint32_t clamp( uint32_t min, uint32_t max, uint32_t value )
  {
    const uint32_t a = ( max < value ? max : value );
    return ( min > a ? min : a );
  }

  inline void setupImageFormats()
  {
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR( Queues::physicalDevice, Queues::surface, &capabilities );

    vkGetPhysicalDeviceSurfaceFormatsKHR( Queues::physicalDevice, Queues::surface, &count, nullptr );
    VkSurfaceFormatKHR surfaceFormats[count];

    // vkGetPhysicalDeviceSurfaceCapabilitiesKHR( Queues::physicalDevice, Queues::surface, &capabilities );

    // vkGetPhysicalDeviceSurfaceFormatsKHR( Queues::physicalDevice, Queues::surface, &count, nullptr );
    // VkSurfaceFormatKHR surfaceFormats[count];

    // VkPresentModeKHR presentModes[count];
    // vkGetPhysicalDeviceSurfacePresentModesKHR( Queues::physicalDevice, Queues::surface, &count, nullptr );
    
    // if ( count != 0 )
    // {
    //   vkGetPhysicalDeviceSurfaceFormatsKHR( Queues::physicalDevice, Queues::surface, &count, surfaceFormats );
    //   vkGetPhysicalDeviceSurfacePresentModesKHR( Queues::physicalDevice, Queues::surface, &count, presentModes );
    // }


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

    // VkSurfaceFormatKHR surfaceFormat;
    for ( const VkSurfaceFormatKHR & surfaceFormat1 : surfaceFormats )
    {
      if ( surfaceFormat1.format == VK_FORMAT_B8G8R8A8_SRGB && surfaceFormat1.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR )
      {
        swapChainImageFormat = surfaceFormat1;
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

    // swapChainExtent = SwapChainSupportDetails::chooseSwapExtent();
    imageCount = ( Frames );

    if ( SwapChainSupportDetails::capabilities.maxImageCount > 0 && imageCount > SwapChainSupportDetails::capabilities.maxImageCount )
    {
      imageCount = SwapChainSupportDetails::capabilities.maxImageCount;
    }

    std::cout << SwapChainSupportDetails::capabilities.minImageCount << "\n";
    std::cout << SwapChainSupportDetails::capabilities.maxImageCount << "\n";
    std::cout << SwapChainSupportDetails::capabilities.currentExtent.height << "\n";
    std::cout << SwapChainSupportDetails::capabilities.currentExtent.width << "\n";

    // SwapChainSupportDetails::swapChainImageFormat = surfaceFormat;
    // SwapChainSupportDetails::swapChainExtent      = extent;
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
      .imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE,
      .queueFamilyIndexCount = 1,
      .pQueueFamilyIndices   = &aa[0],
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

    VkUtilsXBase::clPPPI3<PFN_vkCreateSwapchainKHR>( &createInfo, "vkCreateSwapchainKHR", &swapChain );
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

      VkUtilsXBase::clPPPI3<PFN_vkCreateImageView>( &createInfo, "vkCreateImageView", &SwapChainSupportDetails::swapChainImageViews[i++] );
    }
  }

  inline void createFramebuffers()
  {
    
    // framebufferCreateInfo.attachmentCount = 1;
    
    VkFramebufferAttachmentImageInfo FramebufferAttachmentImage
    {
      .sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO,
      .pViewFormats=&swapChainImageFormat.format,
      .viewFormatCount=1,
      .layerCount=1,
      .height= swapChainExtent.height,
      .width= swapChainExtent.width,
      .usage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT+1, //Possible Driver Bug Setting the Usage to 0x11 instead of 0x10 on the SwapChain Image Usage Flag...
    };

    // VkFramebufferAttachmentImageInfo atts[3]={FramebufferAttachmentImage, FramebufferAttachmentImage, FramebufferAttachmentImage};
    VkFramebufferAttachmentsCreateInfo FramebufferAttachments
    {
      .sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO,
      .attachmentImageInfoCount=1,
      .pAttachmentImageInfos=&FramebufferAttachmentImage,
    };
    
    VkFramebufferCreateInfo framebufferCreateInfo = {};
    framebufferCreateInfo.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
    framebufferCreateInfo.pNext                   = &FramebufferAttachments,
    framebufferCreateInfo.flags                   = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT;
    framebufferCreateInfo.renderPass              = renderPass;
    framebufferCreateInfo.width                   = swapChainExtent.width;
    framebufferCreateInfo.height                  = swapChainExtent.height;
    framebufferCreateInfo.layers                  = 1;
    framebufferCreateInfo.attachmentCount         = 1;
    framebufferCreateInfo.pAttachments            = nullptr;


    for ( size_t i = 0; i < Frames; i++ )
    {
      // framebufferCreateInfo.pAttachments = &swapChainImageViews[i];

      VkUtilsXBase::clPPPI3<PFN_vkCreateFramebuffer>( &framebufferCreateInfo, "vkCreateFramebuffer", &swapChainFramebuffers[i] );
    }
  }

}  // namespace SwapChainSupportDetails
