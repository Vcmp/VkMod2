#include "SwapChain.hpp"


auto SwapChain::getCurrentSwapChainSurfaceCapabilities() const -> VkExtent2D
{
   VkSurfaceCapabilitiesKHR capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physdevice, surface, &capabilities );
  return capabilities.currentExtent;
}

auto SwapChain::setupImageFormats() -> VkSurfaceFormatKHR
{
    std::cout <<"SetupImageFormats"<<"\n";
    uint32_t count=0;
    

    vkGetPhysicalDeviceSurfaceFormatsKHR(physdevice, surface, &count, nullptr );
    std::vector<VkSurfaceFormatKHR> surfaceFormats(count);
    
    {
      vkGetPhysicalDeviceSurfaceFormatsKHR(physdevice, surface, &count, surfaceFormats.data() );
    }
    vkGetPhysicalDeviceSurfacePresentModesKHR(physdevice, surface, &count, nullptr );
    std::vector<VkPresentModeKHR> presentModes(count);

    {
      vkGetPhysicalDeviceSurfacePresentModesKHR(physdevice, surface, &count, presentModes.data() );
    }

    VkSurfaceFormatKHR         swapChainImageFormat;

    // VkSurfaceFormatKHR surfaceFormat;
    for ( const VkSurfaceFormatKHR & surfaceFormat1 : surfaceFormats )
    {
      if ( surfaceFormat1.format == VK_FORMAT_B8G8R8A8_UNORM && surfaceFormat1.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
      {
        swapChainImageFormat = surfaceFormat1;
        break;
      }
    }

    for ( const VkPresentModeKHR & presentMode1 : presentModes )
    {
      
        presentMode = (presentMode1  == VK_PRESENT_MODE_IMMEDIATE_KHR)? VK_PRESENT_MODE_IMMEDIATE_KHR : VK_PRESENT_MODE_FIFO_KHR;
       
    }

    

    return swapChainImageFormat;
}


auto SwapChain::getSwapChainImages(uint32_t size) -> std::array<VkImage, Frames>
{
  std::array<VkImage, Frames> image;
  vkGetSwapchainImagesKHR( Vks::Device, swapChain, &size, image.data());
  return image;
}

auto SwapChain::createSwapChain(const VkSurfaceFormatKHR swapChainImageFormat) -> VkSwapchainKHR
  {
    std::cout << "ImageCount: " << Frames << "\n";
    

    const VkSwapchainCreateInfoKHR createInfo{

      .sType   = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .pNext   = nullptr,
      .surface = surface,

      // Image settings
      .minImageCount    = Frames,
      .imageFormat      = swapChainImageFormat.format,
      .imageColorSpace  = swapChainImageFormat.colorSpace,
      .imageExtent      = swapChainExtent,
      .imageArrayLayers = 1,
      .imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

      .imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE, //Is concurrent even needed in many cases...
      .queueFamilyIndexCount = 0,
      .pQueueFamilyIndices   = 0,
      

      .preTransform   = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
      .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
      .presentMode    = presentMode,
      .clipped        = true,

      .oldSwapchain = VK_NULL_HANDLE
    };
    std::cout << Vks::Device << "\n";
    VkSwapchainKHR swapChain;
    vkCreateSwapchainKHR(Vks::Device, &createInfo, nullptr, &swapChain );
    return swapChain;
    
  }

  


//Posibel BUg fix: Don't use self-reference to the parent Struct vkImage Array and instead just use a passed VkImage paramter so it isn't accidentally Overridden!
  auto SwapChain::createImageViews(std::array<VkImage, Frames> images) -> std::array<VkImageView, Frames>
  {
    std::cout << ( "Creating Image Views" ) << "\n";
    int i = 0;
    std::array<VkImageView, Frames> imageViews;
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

  auto SwapChain::createFramebuffers(VkRenderPass renderpass) -> VkFramebuffer
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
      .usage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, //Nvidia Driver bug with Usages/Varients is now fixed in an eailer 473.** Driver Branch and does/no longer needs an offset tp be corrected manually
    };


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



      return Vks.doPointerAlloc5<VkFramebuffer>(&framebufferCreateInfo, vkCreateFramebuffer);
    
  

}

//COuld Turn this into an Dedicated Object or even amore complex "Scene" Aggregate"
auto SwapChain::createRenderPass(VkImageLayout initial, bool load) -> VkRenderPass
{
    std::cout << ( "Creating RenderPass" ) << "\n";
      static const VkAttachmentDescription colorAttachment{
    .format         = VK_FORMAT_B8G8R8A8_UNORM,  // SwapChainSupportDetails::swapChainImageFormat,
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