
#include "tst2.hpp"

#include "imgLud.hpp"
#include <vulkan/vulkan_core.h>


// VmaAllocationCreateInfo VmaAllocationCreateInfo1 //DUPE
//   {
//     .usage=VMA_MEMORY_USAGE_AUTO,
//     .memoryTypeBits=VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    
//   };
//This Method/Function Sucks [Mostly/Primarily In terms of Layout]
VkImage tst2::setupImagetest(memSys& memSysm)
{
    int x, y, cnls;
    auto limg = tstA::loadImg(x, y, cnls);
    std::cout << sizeof(limg) <<"--"<< x <<"--"<< y <<"--"<< cnls << "\n";
 
	VkDeviceSize imageSize = x * y * cnls;

	//Check if correct format as Framebuffer/ViImage.VkImageView is in UNORM and not SRGB
	constexpr VkFormat image_format = VK_FORMAT_R8G8B8A8_UNORM;

    VmaAllocation VmaAllocation;
    stagingBuffer = memSysm.allocBuf(imageSize, VmaAllocation);
	  memSysm.mapMem(limg, VmaAllocation, imageSize);

	tstA::freeImg(limg);

constexpr VkExtent3D extent = {.width=width, .height=height, .depth=1};
   constexpr VkImageCreateInfo imageInfo 
   {
        .sType             = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .imageType         = VK_IMAGE_TYPE_2D,
        .extent            = extent,
        .mipLevels         = 1,
        .arrayLayers       = 1,
        .format            = image_format,
        .tiling            = VK_IMAGE_TILING_OPTIMAL,
        .initialLayout     = VK_IMAGE_LAYOUT_PREINITIALIZED,//VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL,: Check this correct Image Layout
        .usage             = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .samples           = VK_SAMPLE_COUNT_1_BIT,
        .sharingMode       = VK_SHARING_MODE_EXCLUSIVE,
};
	constexpr VmaAllocationCreateInfo dimg_allocinfo = {.usage = VMA_MEMORY_USAGE_GPU_ONLY};
  auto vkImage = Vks::doPointerAlloc5<VkImage>( &imageInfo, vkCreateImage);


    chkTst(vmaCreateImage(memSysm.vmaAllocator, &imageInfo, &dimg_allocinfo, &vkImage, &VmaAllocation, nullptr));
    return vkImage;
}

void tst2::transitionImageLayout( VkQueue transferQueue, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout )
{
    
  commandBufferSets.beginSingleTimeCommands();

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
  commandBufferSets.endSingleTimeCommands(transferQueue);
}


auto tst2::copyImgToBuf(VkExtent3D extent)
{
    constexpr VkBufferImageCopy copyRegion = {
	    .bufferOffset = 0,
	    .bufferRowLength = 0,
	    .bufferImageHeight = 0,

	    .imageSubresource=subresource,
	    .imageExtent = {width, height, 1},
};
	//copy the buffer into the image
    VkImage DstImg;
	vkCmdCopyBufferToImage(commandBufferSets.commandBuffer, stagingBuffer, DstImg, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);
    return DstImg;
}

void tst2::vkRecImg(VkImageLayout srcImageLayout, VkImageLayout dstImageLayout)
{
  VkImage DstImg;
  
  constexpr VkImageBlit imgBlt
  {
    .srcSubresource=subresource,
    .srcOffsets={0,0,0},
    .dstSubresource=subresource,
    .dstOffsets={0,0,0}
  };
  //vkCmdBeginRenderPass(commandBufferSets.commandBuffer, nullptr, nullptr);
  commandBufferSets.beginSingleTimeCommands();
  vkCmdBlitImage(commandBufferSets.commandBuffer, image, srcImageLayout, DstImg, dstImageLayout, 1, &imgBlt, VK_FILTER_NEAREST);
  commandBufferSets.endSingleTimeCommands(GraphicsQueue2);
  
}


//ideally would use Buffalloc in function btu would require static struct.lcas. fucntion for MemSys (Which woudl get annying to initalise very Quickely)
auto tst2::copyBufToImg(VkBuffer buffer, VkImage image, VkExtent3D extent)
{
  	const VkBufferImageCopy copyRegion = {
	    .bufferOffset = 0,
	    .bufferRowLength = 0,
	    .bufferImageHeight = 0,

	    .imageSubresource=subresource,
	    .imageExtent = extent,
    };
    
    vkCmdCopyImageToBuffer(commandBufferSets.commandBuffer, image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, buffer, 1, &copyRegion);
    return buffer;
}