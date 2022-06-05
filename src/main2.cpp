
#include "Buffers.hpp"

#include "Queues.hpp"
#include "SwapChain.hpp"


void vkMappedCopy(VkDeviceMemory &Staging, size_t size, const auto* srcVectBuffs, __m256 *data, VkBuffer& Temp)
{
  // void* autoMemAllocs;
    memcpy(data, srcVectBuffs, size );
  
    BuffersX::copyBuffer(Temp, size);
}
void BuffersX::setupBuffers()
{
  auto x1 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  auto p1 = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( p1, vertexBuffer, x1, sizedsf, vertexBufferMemory );
  // createSetBuffer( p1, vertexBufferTemp, x1, sizeof(Temp), vertexBufferMemorytemp );

  VkBufferUsageFlagBits x2 = { VK_BUFFER_USAGE_TRANSFER_SRC_BIT };
  constexpr auto        p  = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( p, Bufferstaging, x2, sizedsf, stagingBufferMemory );

  auto x3 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, x3, sizedsfIdx, indexBufferMemory );
  vkMapMemory( VKI.tst(), stagingBufferMemory, 0, 1024, 0, (void**)&data );
  {

  vkMappedCopy(stagingBufferMemory, sizedsf, vectBuf, data, vertexBuffer);
  vkMappedCopy(stagingBufferMemory, sizedsfIdx, idxBuf, data, indexBuffer);
  }  
  vkUnmapMemory( VKI.tst(), stagingBufferMemory );

  // BuffersX::copyBuffer( vertexBufferTemp, sizeof(Temp) );

 
}

inline void BuffersX::createSetBuffer(
  VkMemoryPropertyFlagBits properties, VkBuffer & currentBuffer, VkBufferUsageFlagBits usage, size_t sized, VkDeviceMemory & vertexBufferMemory )
{
  const VkBufferCreateInfo allocateInfo = {
    .sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .pNext       = nullptr,
    .size        = sized,
    .usage       = usage,
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
  };

 vkCreateBuffer(VKI.tst(), &allocateInfo, nullptr, &currentBuffer );

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements( VKI.tst(), currentBuffer, &memRequirements );

  VkMemoryAllocateInfo allocateInfo1 = {
    .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext           = nullptr,
    .allocationSize  = memRequirements.size,
    .memoryTypeIndex = findMemoryType( memRequirements.memoryTypeBits, properties ),
  };
  //
  vkAllocateMemory(VKI.tst(), &allocateInfo1, nullptr, &vertexBufferMemory );

  vkBindBufferMemory( VKI.tst(), currentBuffer, vertexBufferMemory, 0 ) ;
}

inline uint32_t BuffersX::findMemoryType( uint32_t typeFilter, VkMemoryPropertyFlagBits properties )
{
  // VkPhysicalDeviceMemoryProperties memProperties = {};
  vkGetPhysicalDeviceMemoryProperties( VKI.physdevice, &memProperties );
  for ( uint32_t i = 0; i < memProperties.memoryTypeCount; i++ )
  {
    if ( /* ( typeFilter & ( 1U << i ) ) != 0 &&  */( memProperties.memoryTypes[i].propertyFlags & properties ) == properties )
    {
      return i;
    }
  }

  printf( "Failed to find suitable memory type" );
  return 1;
}


inline void BuffersX::copyBuffer( VkBuffer & dst, const size_t sized )
{
  Queues::beginSingleTimeCommands();
  const VkBufferCopy vkBufferCopy{
    .srcOffset = 0,
    .dstOffset = 0,
    .size      = sized,
  };
  vkCmdCopyBuffer( Queues::commandBuffer, Bufferstaging, dst, 1, &vkBufferCopy );
  Queues::endSingleTimeCommands();
}



void Queues::createCommandPool()
{
  constexpr VkCommandPoolCreateInfo poolInfo = {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .queueFamilyIndex = 0,
  };
  commandPool = Vks::doPointerAlloc5<VkCommandPool>( &poolInfo, vkCreateCommandPool );
  constexpr VkCommandPoolCreateInfo poolInfo2{
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .queueFamilyIndex = 1,
  };
  commandPool2 = Vks::doPointerAlloc5<VkCommandPool>( &poolInfo2, vkCreateCommandPool );
  if ( commandBuffer == nullptr )
  {
    const VkCommandBufferAllocateInfo allocateInfo{
      .sType              = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
      .pNext              = VK_NULL_HANDLE,
      .commandPool        = ( Queues::commandPool2 ),
      .level              = ( VK_COMMAND_BUFFER_LEVEL_PRIMARY ),
      .commandBufferCount = ( 1 ),
    };

    vkAllocateCommandBuffers(VKI.tst(),  &allocateInfo,  &commandBuffer );
  }
}

inline void Queues::beginSingleTimeCommands()
{
  vkBeginCommandBuffer( commandBuffer,  &vkCommandBufferBeginInfo );
}

inline void Queues::endSingleTimeCommands()
{
  vkEndCommandBuffer( commandBuffer);

  vkQueueSubmit( VKI.TransferQueue, 1, &submitInfo1, VK_NULL_HANDLE );
  vkQueueWaitIdle( VKI.TransferQueue );
  vkResetCommandPool( VKI.tst(), ( commandPool2 ), VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT );
}



auto SwapChain::getCurrentSwapChainSurfaceCapabilities() const -> VkExtent2D
{
   VkSurfaceCapabilitiesKHR capabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VKI.physdevice, VKI.surface, &capabilities );
  return capabilities.currentExtent;
}

auto SwapChain::setupImageFormats() -> VkSurfaceFormatKHR
{
    std::cout <<"SetupImageFormats"<<"\n";
    uint32_t count=0;
    

    vkGetPhysicalDeviceSurfaceFormatsKHR(VKI.physdevice, VKI.surface, &count, nullptr );
    std::vector<VkSurfaceFormatKHR> surfaceFormats(count);
    
    if ( count != 0 )
    {
      vkGetPhysicalDeviceSurfaceFormatsKHR(VKI.physdevice, VKI.surface, &count, surfaceFormats.data() );
    }
    vkGetPhysicalDeviceSurfacePresentModesKHR(VKI.physdevice, VKI.surface, &count, nullptr );
    std::vector<VkPresentModeKHR> presentModes(count);

    if ( count != 0 )
    {
      vkGetPhysicalDeviceSurfacePresentModesKHR(VKI.physdevice, VKI.surface, &count, presentModes.data() );
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

    // return VK_PRESENT_MODE_FIFO_KHR;

    // swapChainExtent = SwapChainSupportDetails::chooseSwapExtent();
    // imageCount = ( Frames );

    // if ( capabilities.maxImageCount > 0 && Frames > capabilities.maxImageCount )
    // {
    //   // imageCount = capabilities.maxImageCount;
    // }

    // std::cout << capabilities.minImageCount << "\n";
    // std::cout << capabilities.maxImageCount << "\n";
    // std::cout << capabilities.currentExtent.height << "\n";
    // std::cout << capabilities.currentExtent.width << "\n";

    // SwapChainSupportDetails::swapChainImageFormat = surfaceFormat;
    // SwapChainSupportDetails::swapChainExtent      = extent;

    return swapChainImageFormat;
}


auto SwapChain::getSwapChainImages(uint32_t size) -> std::array<VkImage, Frames>
{
  std::array<VkImage, Frames> image;
  vkGetSwapchainImagesKHR( VKI.tst(), swapChain, &size, image.data());
  return image;
}

auto SwapChain::createSwapChain(const VkSurfaceFormatKHR swapChainImageFormat) -> VkSwapchainKHR
  {
    std::cout << "ImageCount: " << Frames << "\n";

    const auto aa = { VKI.graphicsFamily, VKI.transferFamily };
    

    const VkSwapchainCreateInfoKHR createInfo{

      .sType   = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
      .pNext   = nullptr,
      .surface = VKI.surface,

      // Image settings
      .minImageCount    = Frames,
      .imageFormat      = swapChainImageFormat.format,
      .imageColorSpace  = swapChainImageFormat.colorSpace,
      .imageExtent      = swapChainExtent,
      .imageArrayLayers = 1,
      .imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,

      // if (graphicsFamily != presentFamily) {
      .imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE,
      .queueFamilyIndexCount = 0,
      .pQueueFamilyIndices   = &VKI.graphicsFamily,
      // } else {
      // .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
      // .queueFamilyIndexCount = 0; // Optiona,
      // .pQueueFamilyIndices = nullptr; // Optiona,
      // }

      .preTransform   = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
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
    
      // framebufferCreateInfo.pAttachments = &swapChainImageViews[i];

      return Vks::doPointerAlloc5<VkFramebuffer>(&framebufferCreateInfo, vkCreateFramebuffer);
    
  

}  // namespace SwapChainSupportDetails

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