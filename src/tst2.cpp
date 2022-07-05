#include "tst2.hpp"
#include "vk_mem_alloc.h"
#include <cwchar>
#include <vulkan/vulkan_core.h>
#include "Vks.tpp"

// VmaAllocationCreateInfo VmaAllocationCreateInfo1 //DUPE
//   {
//     .usage=VMA_MEMORY_USAGE_AUTO,
//     .memoryTypeBits=VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    
//   };
//This Method/Function Sucks [Mostly/Primarily In terms of Layout]
VkImage tst2::setupImagetest(memSys& memSysm)
{
    int x;
    int y;
    int cnls;
    auto limg = stbi_load("tst.png", &x, &y, &cnls, STBI_rgb);

 
 
    void* pixel_ptr = limg;
	VkDeviceSize imageSize = x * y * 3;

	//Check if correct format as Framebuffer/ViImage.VkImageView is in UNORM and not SRGB
	constexpr VkFormat image_format = VK_FORMAT_R8G8B8A8_SRGB;

	//allocate temporary buffer for holding texture data to upload
    VmaAllocation VmaAllocation;
    stagingBuffer = memSysm.allocBuf(stagingBuffer, sizeof(limg), VmaAllocation);

	//copy data to buffer
    // beginSingleTimeCommands(commandBufferSets.commandBuffer);

    // vkCmdFillBuffer(commandBufferSets.commandBuffer, nullptr, 0, sizeof(limg), limg);
	void* data;
	vmaMapMemory(memSysm.vmaAllocator, VmaAllocation, &data);
    {

	    memcpy(data, pixel_ptr, imageSize);

    }
    vmaUnmapMemory(memSysm.vmaAllocator, VmaAllocation);
	//we no longer need the loaded data, so we can free the pixels as they are now in the staging buffer
	stbi_image_free(limg);

constexpr VkExtent3D extent = {.width=width, .height=height, .depth=1};
   constexpr VkImageCreateInfo imageInfo = {
        .sType             = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType         = VK_IMAGE_TYPE_2D,
        .extent            = extent,
        .mipLevels         = 1,
        .arrayLayers       = 1,
        .format            = image_format,
        .tiling            = VK_IMAGE_TILING_LINEAR,
        .initialLayout     = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL,
        .usage             = VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV,
        .samples           = VK_SAMPLE_COUNT_1_BIT,
        .sharingMode       = VK_SHARING_MODE_EXCLUSIVE,
};
	constexpr VmaAllocationCreateInfo dimg_allocinfo = {.usage = VMA_MEMORY_USAGE_GPU_ONLY};
auto vkImage = Vks::doPointerAlloc5<VkImage>( &imageInfo, vkCreateImage);
//   constexpr VkMemoryDedicatedRequirementsKHR img2 = { VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS_KHR, nullptr };

//   VkMemoryRequirements2 memRequirements = {};
//   vkGetImageMemoryRequirements( Vks::Device, vkImage, &memRequirements.memoryRequirements );

//   VkMemoryAllocateInfo allocInfo = {};
//   allocInfo.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
//   allocInfo.allocationSize       = memRequirements.memoryRequirements.size;
// //   allocInfo.memoryTypeIndex =
//     // BuffersX::findMemoryType( memRequirements.memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
//   allocInfo.pNext = VK_NULL_HANDLE;

//   if constexpr ( img2.prefersDedicatedAllocation | img2.requiresDedicatedAllocation )
//   {
//     std::cout << ( "Using Dedicated Memory Allocation" ) << "\n";
//     VkMemoryDedicatedAllocateInfo dedicatedAllocateInfoKHR = {};
//     dedicatedAllocateInfoKHR.sType                         = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
//     dedicatedAllocateInfoKHR.image                         = vkImage;

//     allocInfo.pNext = &dedicatedAllocateInfoKHR;
//   }

    vmaCreateImage(memSysm.vmaAllocator, &imageInfo, &dimg_allocinfo, &vkImage, &VmaAllocation, nullptr);
    return vkImage;
}

void tst2::transitionImageLayout( VkInit &VKI, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout )
{
    
  beginSingleTimeCommands(commandBufferSets.commandBuffer);

  VkImageMemoryBarrier barrier = {
    .sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
    .pNext               = VK_NULL_HANDLE,
    .oldLayout           = oldLayout,
    .newLayout           = ( newLayout ),
    .srcQueueFamilyIndex = ( VK_IMAGE_LAYOUT_UNDEFINED ),
    .dstQueueFamilyIndex = ( VK_IMAGE_LAYOUT_UNDEFINED ),
    .image               = ( image ),
    .subresourceRange    = { .aspectMask     = static_cast<VkImageAspectFlags>( ( format ) ),
                             .baseMipLevel   = ( 0 ),
                             .levelCount     = ( 1 ),
                             .baseArrayLayer = ( 0 ),
                             .layerCount     = ( 1 ) },
  };

  if ( newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL )
  {
    if ( format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT )
    {
      barrier.subresourceRange.aspectMask = ( barrier.subresourceRange.aspectMask | VK_IMAGE_ASPECT_STENCIL_BIT );
    }
  }

  VkPipelineStageFlags sourceStage      = 0;
  VkPipelineStageFlags destinationStage = 0;
  switch ( oldLayout )
  {
    case VK_IMAGE_LAYOUT_UNDEFINED:
      {
        barrier.srcAccessMask = ( VK_ACCESS_NONE_KHR );
        break;
      };
    case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
      {
        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        break;
      };
    default:  printf( "Unsupported layout transition" );
  }
  switch ( newLayout )
  {
    case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
      {
        barrier.subresourceRange.aspectMask = ( VK_IMAGE_ASPECT_DEPTH_BIT );

        barrier.dstAccessMask = ( VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT );
        sourceStage           = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        destinationStage      = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
        break;
      }
    case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
      {
        barrier.subresourceRange.aspectMask = ( VK_IMAGE_ASPECT_COLOR_BIT );

        barrier.dstAccessMask = ( VK_ACCESS_SHADER_READ_BIT );
        sourceStage           = VK_PIPELINE_STAGE_TRANSFER_BIT;
        destinationStage      = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        break;
      }
    default:  printf( "Unsupported layout transition" );
  }

  vkCmdPipelineBarrier( commandBufferSets.commandBuffer, sourceStage /* TODO */, destinationStage /* TODO */, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, &barrier );
  endSingleTimeCommands(VKI.GraphicsQueue, commandBufferSets.commandBuffer);
}


auto tst2::copyImage(VkInit &VKI, VkExtent3D extent)
{
    constexpr VkBufferImageCopy copyRegion = {
	    .bufferOffset = 0,
	    .bufferRowLength = 0,
	    .bufferImageHeight = 0,

	    .imageSubresource={.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
	    .mipLevel = 0,
	    .baseArrayLayer = 0,
	    .layerCount = 1,
        },
	    .imageExtent = {width, height, 1},
};
	//copy the buffer into the image
    VkImage DstImg;
	vkCmdCopyBufferToImage(commandBufferSets.commandBuffer, stagingBuffer, DstImg, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);
    return DstImg;
}

void tst2::vkRecImg(VkCommandBuffer commandBuffer)
{
  //  vkCmdBeginRenderPass(commandBufferSets.commandBuffer, nullptr, nullptr);
  //  vkCmdBlitImage(commandBufferSets.commandBuffer);
}