#pragma once

// #include "Buffers.hpp"
#include "Buffers.hpp"

#include <cstdint>

inline namespace Texture
{
  static constinit VkImage        vkImage;
  static constinit VkDeviceMemory vkAllocMemory;
  static VkFormat                 findDepthFormat();
  static void                     createImage( VkExtent2D, VkFormat, VkImageUsageFlagBits );
  static void                     transitionImageLayout( VkFormat, VkImageLayout, VkImageLayout );
  static void                     createImageView( VkFormat, VkImageAspectFlagBits, VkImageLayout );
};  // namespace Texture

inline void Texture::createImage( VkExtent2D extent, VkFormat format, VkImageUsageFlagBits usage )
{
  VkImageCreateInfo imageInfo = {};
  imageInfo.sType             = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType         = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width      = extent.width;
  imageInfo.extent.height     = extent.height;
  imageInfo.extent.depth      = 1;
  imageInfo.mipLevels         = 1;
  imageInfo.arrayLayers       = 1;
  imageInfo.format            = format;
  imageInfo.tiling            = VK_IMAGE_TILING_OPTIMAL;
  imageInfo.initialLayout     = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage             = usage;
  imageInfo.samples           = VK_SAMPLE_COUNT_1_BIT;
  imageInfo.sharingMode       = VK_SHARING_MODE_EXCLUSIVE;

  VkUtilsXBase::clPPPI3<PFN_vkCreateImage>( &imageInfo, "vkCreateImage", &Texture::vkImage );
  constexpr VkMemoryDedicatedRequirementsKHR img2 = { VK_STRUCTURE_TYPE_MEMORY_DEDICATED_REQUIREMENTS_KHR, nullptr };

  VkMemoryRequirements2 memRequirements = {};
  vkGetImageMemoryRequirements( Queues::device, Texture::vkImage, &memRequirements.memoryRequirements );

  VkMemoryAllocateInfo allocInfo = {};
  allocInfo.sType                = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize       = memRequirements.memoryRequirements.size;
  allocInfo.memoryTypeIndex =
    BuffersX::findMemoryType( Queues::physicalDevice, memRequirements.memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  allocInfo.pNext = VK_NULL_HANDLE;

  if constexpr ( img2.prefersDedicatedAllocation | img2.requiresDedicatedAllocation )
  {
    std::cout << ( "Using Dedicated Memory Allocation" ) << "\n";
    VkMemoryDedicatedAllocateInfo dedicatedAllocateInfoKHR = {};
    dedicatedAllocateInfoKHR.sType                         = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
    dedicatedAllocateInfoKHR.image                         = Texture::vkImage;

    allocInfo.pNext = &dedicatedAllocateInfoKHR;
  }

  vkBindImageMemory( Queues::device, Texture::vkImage, Texture::vkAllocMemory, 0 );
}

static void Texture::transitionImageLayout( VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout )
{
  Queues::beginSingleTimeCommands();

  VkImageMemoryBarrier barrier = {
    .sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
    .pNext               = VK_NULL_HANDLE,
    .oldLayout           = oldLayout,
    .newLayout           = ( newLayout ),
    .srcQueueFamilyIndex = ( VK_IMAGE_LAYOUT_UNDEFINED ),
    .dstQueueFamilyIndex = ( VK_IMAGE_LAYOUT_UNDEFINED ),
    .image               = ( Texture::vkImage ),
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
    default:  std::runtime_error( "Unsupported layout transition" );
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
    default:  std::runtime_error( "Unsupported layout transition" );
  }

  vkCmdPipelineBarrier( queues.commandBuffer, sourceStage /* TODO */, destinationStage /* TODO */, 0, 0, VK_NULL_HANDLE, 0, VK_NULL_HANDLE, 1, &barrier );
  Queues::endSingleTimeCommands();
}

inline void Texture::createImageView( VkFormat swapChainImageFormat, VkImageAspectFlagBits vkImageAspect, VkImageLayout a )
{
  const VkImageViewCreateInfo createInfo = { .sType    = ( VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO ),
                                             .image    = ( vkImage ),
                                             .viewType = ( VK_IMAGE_VIEW_TYPE_2D ),
                                             .format   = ( swapChainImageFormat ),

                                             .subresourceRange{
                                               .aspectMask     = vkImageAspect,
                                               .baseMipLevel   = ( 0 ),
                                               .levelCount     = ( 1 ),
                                               .baseArrayLayer = ( 0 ),
                                               .layerCount     = ( 1 ),
                                             } };
  VkUtilsXBase::clPPPI( &createInfo, "vkCreateImageView", &a );
}

inline VkFormat Texture::findDepthFormat()
{
  constexpr VkFormat formatCandidates[3] = { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
  VkFormatProperties props;

  for ( const VkFormat & format : formatCandidates )
  {
    vkGetPhysicalDeviceFormatProperties( Queues::physicalDevice, format, &props );

    const uint32_t i2 = props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;
    if ( i2 == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT /* && VK10.VK_IMAGE_TILING_OPTIMAL == VK_IMAGE_TILING_OPTIMAL*/ )
    {
      return format;
    }
  }

  std::runtime_error( "failed to find supported format!" );
}