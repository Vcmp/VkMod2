
#include "Buffers.hpp"

#include "Queues.hpp"


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
  commandPool = clPPPI3A<VkCommandPool, PFN_vkCreateCommandPool>( &poolInfo, "vkCreateCommandPool" );
  constexpr VkCommandPoolCreateInfo poolInfo2{
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .queueFamilyIndex = 1,
  };
  commandPool2 = clPPPI3A<VkCommandPool, PFN_vkCreateCommandPool>( &poolInfo2, "vkCreateCommandPool" );
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