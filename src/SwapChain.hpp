
#include "Vks.tpp"

#pragma once
static struct SwapChain
{
    VkSurfaceCapabilitiesKHR capabilities{};
    uint32_t       imageCount;
    VkSwapchainKHR swapChain;
    VkImage image[3];
    VkImageView imageViews[3];
    VkRenderPass renderpass;
    VkSurfaceFormatKHR         swapChainImageFormat;
    VkPresentModeKHR presentMode;
    VkExtent2D swapChainExtent{854, 480};
    const VkFramebuffer frameBuffer;
    SwapChain(/* VkPhysicalDevice physdevice, VkSurfaceKHR surface */) : frameBuffer(createFramebuffers())
    {
        setupImageFormats();
        createSwapChain();
        createImageViews();
        // createFramebuffers();
        createRenderPass();
      
    };
    void setupImageFormats();
    void createSwapChain();
    void createImageViews();
    VkFramebuffer createFramebuffers();
    void createRenderPass();

} SW;



void SwapChain::setupImageFormats()
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
}

void SwapChain::createSwapChain()
  {
    std::cout << "ImageCount: " << imageCount << "\n";

    const uint32_t aa[] = { VKI.graphicsFamily, VKI.transferFamily };
    ;

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
      .pQueueFamilyIndices   = &aa[0],
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
    std::cout << VKI.device << "\n";

    vkCreateSwapchainKHR(VKI.device, &createInfo, nullptr, &swapChain );
    vkGetSwapchainImagesKHR( VKI.device, swapChain, &imageCount, image);
  }

  



  void SwapChain::createImageViews()
  {
    std::cout << ( "Creating Image Views" ) << "\n";
    int i = 0;
    for ( const VkImage & swapchainImage : image )
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

      Vks::doPointerAlloc<VkImageView, PFN_vkCreateImageView>(VKI.device, &createInfo, &imageViews[i++], vkCreateImageView);
    }
  }

  VkFramebuffer SwapChain::createFramebuffers()
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
    framebufferCreateInfo.renderPass              = renderpass;
    framebufferCreateInfo.width                   = swapChainExtent.width;
    framebufferCreateInfo.height                  = swapChainExtent.height;
    framebufferCreateInfo.layers                  = 1;
    framebufferCreateInfo.attachmentCount         = 1;
    framebufferCreateInfo.pAttachments            = nullptr;


    // for ( size_t i = 0; i < Frames; i++ )
    {
      // framebufferCreateInfo.pAttachments = &swapChainImageViews[i];

      return Vks::doPointerAlloc3<VkFramebuffer>(&framebufferCreateInfo, vkCreateFramebuffer);
    }
  

}  // namespace SwapChainSupportDetails


void SwapChain::createRenderPass()
{
    std::cout << ( "Creating RenderPass" ) << "\n";
      static const VkAttachmentDescription colorAttachment{
    .format         = VK_FORMAT_B8G8R8A8_SRGB,  // SwapChainSupportDetails::swapChainImageFormat,
    .samples        = VK_SAMPLE_COUNT_1_BIT,
    .loadOp         = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .storeOp        = VK_ATTACHMENT_STORE_OP_STORE,
    .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
    .initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED,
    .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  };
  static constexpr VkAttachmentReference colorAttachmentRef{ .attachment = 0, .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
  static constexpr VkSubpassDescription  subpass{ .pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS,
                                                  .colorAttachmentCount = 1,
                                                  .pColorAttachments    = &colorAttachmentRef };

                                                  
  static constexpr VkSubpassDependency  VkSubpassDependency
  {
    .srcSubpass=VK_SUBPASS_EXTERNAL,
    .dstSubpass=0,
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
    .dependencyCount=1,
    .pDependencies=&VkSubpassDependency
  };

  Vks::doPointerAlloc(VKI.device, &vkRenderPassCreateInfo1, &renderpass, vkCreateRenderPass );

}