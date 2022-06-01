

#include "Vks.tpp"
#include <array>
#include <cstdint>
#include <initializer_list>
#include <vector>
#include <vulkan/vulkan_core.h>


#pragma once
inline namespace {

    VkSurfaceCapabilitiesKHR capabilities{};
}
static struct SwapChain
{
    uint32_t       imageCount;
    const VkRenderPass renderpass=createRenderPass(VK_IMAGE_LAYOUT_UNDEFINED, false);
    const VkSurfaceFormatKHR         swapChainImageFormat=setupImageFormats();
    VkPresentModeKHR presentMode;
    VkExtent2D swapChainExtent{854, 480};
    VkFramebuffer frameBuffer=createFramebuffers(renderpass);
    const VkSwapchainKHR swapChain=createSwapChain(swapChainImageFormat);;
    const std::array<VkImage, 3> image = getSwapChainImages(3U);
     std::array<VkImageView, 3> imageViews = createImageViews(image);
    SwapChain(/* VkPhysicalDevice physdevice, VkSurfaceKHR surface */) = default;;
    auto setupImageFormats() -> VkSurfaceFormatKHR;
    [[nodiscard]] auto getSwapChainImages(uint32_t) const -> std::array<VkImage, 3>;
    [[nodiscard]] auto createSwapChain(VkSurfaceFormatKHR) const -> VkSwapchainKHR;
    [[nodiscard]] auto createImageViews(std::array<VkImage, 3> image) const -> std::array<VkImageView, 3>;
    auto createFramebuffers(VkRenderPass) const -> VkFramebuffer;
    [[nodiscard]] auto createRenderPass(VkImageLayout, bool) const -> VkRenderPass;

} __attribute__((aligned(128))) SW;



auto SwapChain::setupImageFormats() -> VkSurfaceFormatKHR
{
    std::cout <<"SetupImageFormats"<<"\n";
    uint32_t count=0;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VKI.physdevice, VKI.surface, &capabilities );

    vkGetPhysicalDeviceSurfaceFormatsKHR(VKI.physdevice, VKI.surface, &count, nullptr );
    VkSurfaceFormatKHR surfaceFormats[count];
    
    if ( count != 0 )
    {
      vkGetPhysicalDeviceSurfaceFormatsKHR(VKI.physdevice, VKI.surface, &count, surfaceFormats );
    }

    vkGetPhysicalDeviceSurfacePresentModesKHR(VKI.physdevice, VKI.surface, &count, nullptr );
    VkPresentModeKHR presentModes[count];
    if ( count != 0 )
    {
      vkGetPhysicalDeviceSurfacePresentModesKHR(VKI.physdevice, VKI.surface, &count, presentModes );
    }

    VkSurfaceFormatKHR         swapChainImageFormat;

    // VkSurfaceFormatKHR surfaceFormat;
    for ( const VkSurfaceFormatKHR & surfaceFormat1 : surfaceFormats )
    {
      if ( surfaceFormat1.format == VK_FORMAT_B8G8R8A8_SRGB && surfaceFormat1.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
      {
        swapChainImageFormat = surfaceFormat1;
        break;
      }
    }

    for ( const VkPresentModeKHR & presentMode1 : presentModes )
    {
      
        presentMode = (presentMode1  == VK_PRESENT_MODE_IMMEDIATE_KHR)? VK_PRESENT_MODE_IMMEDIATE_KHR : VK_PRESENT_MODE_FIFO_KHR;
       
    }

    // return VK_PRESENT_MODE_FIFO_KHR;

    // swapChainExtent = SwapChainSupportDetails::chooseSwapExtent();
    imageCount = ( Frames );

    if ( capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount )
    {
      imageCount = capabilities.maxImageCount;
    }

    std::cout << capabilities.minImageCount << "\n";
    std::cout << capabilities.maxImageCount << "\n";
    std::cout << capabilities.currentExtent.height << "\n";
    std::cout << capabilities.currentExtent.width << "\n";

    // SwapChainSupportDetails::swapChainImageFormat = surfaceFormat;
    // SwapChainSupportDetails::swapChainExtent      = extent;

    return swapChainImageFormat;
}


auto SwapChain::getSwapChainImages(uint32_t size) const -> std::array<VkImage, 3>
{
  std::array<VkImage, 3> image;
  vkGetSwapchainImagesKHR( VKI.tst(), swapChain, &size, image.data());
  return image;
}

auto SwapChain::createSwapChain(const VkSurfaceFormatKHR swapChainImageFormat) const -> VkSwapchainKHR
  {
    std::cout << "ImageCount: " << imageCount << "\n";

    const auto aa = { VKI.graphicsFamily, VKI.transferFamily };
    

    const VkSwapchainCreateInfoKHR createInfo{

      .sType   = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .pNext   = nullptr,
      .surface = VKI.surface,

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
      .pQueueFamilyIndices   = &VKI.graphicsFamily,
      // } else {
      // .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
      // .queueFamilyIndexCount = 0; // Optiona,
      // .pQueueFamilyIndices = nullptr; // Optiona,
      // }

      .preTransform   = capabilities.currentTransform,
      .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
      .presentMode    = presentMode,
      .clipped        = true,

      .oldSwapchain = VK_NULL_HANDLE
    };
    std::cout << VKI.tst() << "\n";
    VkSwapchainKHR swapChain;
    vkCreateSwapchainKHR(VKI.tst(), &createInfo, nullptr, &swapChain );
    return swapChain;
    
  }

  


//Posibel BUg fix: Don't use self-reference to the parent Struct vkImage Array and instead just use a passed VkImage paramter so it isn't accidentally Overridden!
  auto SwapChain::createImageViews(std::array<VkImage, 3> images) const -> std::array<VkImageView, 3>
  {
    std::cout << ( "Creating Image Views" ) << "\n";
    int i = 0;
    std::array<VkImageView, 3> imageViews;
    for ( const VkImage & swapchainImage : images )
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

      imageViews[i]=Vks::doPointerAlloc5<VkImageView>(&createInfo, vkCreateImageView);
      i++;
    }
    return imageViews;
  }

  auto SwapChain::createFramebuffers(VkRenderPass renderpass) const -> VkFramebuffer
  {
        std::cout << ( "Creating FrameBuffers" ) << "\n";

    // framebufferCreateInfo.attachmentCount = 1;
    
    VkFramebufferAttachmentImageInfo FramebufferAttachmentImage
    {
      .sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO,
      .pViewFormats=&swapChainImageFormat.format,
      .viewFormatCount=1,
      .layerCount=1,
      .height= swapChainExtent.height,
      .width= swapChainExtent.width,
      .usage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, //Possible Driver Bug Setting the Usage to 0x11 instead of 0x10 on the SwapChain Image Usage Flag...
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
    framebufferCreateInfo.renderPass              = renderpass;
    framebufferCreateInfo.width                   = swapChainExtent.width;
    framebufferCreateInfo.height                  = swapChainExtent.height;
    framebufferCreateInfo.layers                  = 1;
    framebufferCreateInfo.attachmentCount         = 1;
    framebufferCreateInfo.pAttachments            = nullptr;


    // for ( size_t i = 0; i < Frames; i++ )
    {
      // framebufferCreateInfo.pAttachments = &swapChainImageViews[i];

      return Vks::doPointerAlloc5<VkFramebuffer>(&framebufferCreateInfo, vkCreateFramebuffer);
    }
  

}  // namespace SwapChainSupportDetails

//COuld Turn this into an Dedicated Object or even amore complex "Scene" Aggregate"
auto SwapChain::createRenderPass(VkImageLayout initial, bool load) const -> VkRenderPass
{
    std::cout << ( "Creating RenderPass" ) << "\n";
      static const VkAttachmentDescription colorAttachment{
    .format         = VK_FORMAT_B8G8R8A8_SRGB,  // SwapChainSupportDetails::swapChainImageFormat,
    .samples        = VK_SAMPLE_COUNT_1_BIT,
    .loadOp         = VK_ATTACHMENT_LOAD_OP_NONE_EXT,
    .storeOp        = VK_ATTACHMENT_STORE_OP_NONE, //Interestign Bugs: VK_ATTACHMENT_STORE_OP_STORE_DONT_CARE
    .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
    .initialLayout  = initial,
    .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  };
  static constexpr VkAttachmentReference colorAttachmentRef{ .attachment = 0, .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
  static constexpr VkSubpassDescription  subpass{ .pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS,
                                                  .colorAttachmentCount = 1,
                                                  .pColorAttachments    = &colorAttachmentRef };

                                                  
  static constexpr VkSubpassDependency  VkSubpassDependency
  {
    .srcSubpass=VK_SUBPASS_CONTENTS_INLINE,
    .dstSubpass=VK_SUBPASS_CONTENTS_INLINE,
    .srcStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
    .dstStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
    .srcAccessMask=0,
    .dstAccessMask=VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT

  };

  constexpr VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
    //   .flags=VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,
    .attachmentCount = 1,
    .pAttachments    = &colorAttachment,
    .subpassCount    = 1,
    .pSubpasses      = &subpass,
    // .dependencyCount=1,
    // .pDependencies=&VkSubpassDependency
  };

  return Vks::doPointerAlloc5<VkRenderPass>(&vkRenderPassCreateInfo1, vkCreateRenderPass );

}