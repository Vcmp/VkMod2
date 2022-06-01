#include "Buffer.hpp"
#include "Vks.tpp"

VkCommandBuffer Buffer::genCommandBuffer()
{
     const VkCommandBufferAllocateInfo allocateInfo{
      .sType              = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
      .pNext              = VK_NULL_HANDLE,
      .commandPool        = ( commandPool ),
      .level              = ( VK_COMMAND_BUFFER_LEVEL_PRIMARY ),
      .commandBufferCount = ( 1 ),
    };
    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(device, &allocateInfo, &commandBuffer);
    return commandBuffer;


}

VkCommandPool Buffer::createCommandPool()
{
  constexpr VkCommandPoolCreateInfo poolInfo = {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .queueFamilyIndex = 1,
  };
  return Vks::doPointerAlloc5<VkCommandPool>( &poolInfo, vkCreateCommandPool);
//   constexpr VkCommandPoolCreateInfo poolInfo2{
//     .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
//     .pNext            = nullptr,
//     .queueFamilyIndex = 1,
//   };
//   commandPool2 = clPPPI3A<VkCommandPool, PFN_vkCreateCommandPool>( &poolInfo2, "vkCreateCommandPool" );
//   if ( commandBuffer == nullptr )
//   {
   
//     VkUtilsXBase::clPPI3<PFN_vkAllocateCommandBuffers>( &allocateInfo, "vkAllocateCommandBuffers", &commandBuffer );
//   }
}

void Buffer::beginSingleTimeCommands()
{
     constexpr  VkCommandBufferBeginInfo vkCommandBufferBeginInfo = { .sType = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO ),
                                                                         .pNext = VK_NULL_HANDLE,
                                                                         .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT };
  
  vkBeginCommandBuffer(commandBuffer, &vkCommandBufferBeginInfo);
 
}

void Buffer::endSingleTimeCommands()
{
  vkEndCommandBuffer( commandBuffer);

  const VkSubmitInfo       submitInfo1 = {
          .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .pNext = VK_NULL_HANDLE, .commandBufferCount = ( 1 ), .pCommandBuffers = &commandBuffer
  };
 
  vkQueueSubmit( VKI.TransferQueue, 1, &submitInfo1, VK_NULL_HANDLE );
  vkQueueWaitIdle( VKI.TransferQueue );
  vkResetCommandPool( device, ( commandPool ), VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT );
}

void Buffer::copyBuffer( VkBuffer & dst, const size_t sized )
{
  beginSingleTimeCommands();
  const VkBufferCopy vkBufferCopy{
    .srcOffset = 0,
    .dstOffset = 0,
    .size      = sized,
  };
  vkCmdCopyBuffer( commandBuffer, Bufferstaging, dst, 1, &vkBufferCopy );
  endSingleTimeCommands();
}
void Buffer::vkMappedCopy(VkDeviceMemory &Staging, size_t size, const auto* srcVectBuffs, __m256 *data, VkBuffer& Temp)
{
  // void* autoMemAllocs;
    memcpy(data, srcVectBuffs, size );
  
    copyBuffer(Temp, size);
}

void Buffer::setupBuffers()
{
  auto x1 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  auto p1 = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( p1, buffer, x1, sizedsf, BufMemory );
  // createSetBuffer( p1, vertexBufferTemp, x1, sizeof(Temp), vertexBufferMemorytemp );

  VkBufferUsageFlagBits x2 = { VK_BUFFER_USAGE_TRANSFER_SRC_BIT };
  constexpr auto        p  = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( p, Bufferstaging, x2, sizedsf, stagingBufferMemory );

  vkMapMemory( device, stagingBufferMemory, 0, sizedsf, 0, (void**)&data );
  {

  vkMappedCopy(stagingBufferMemory, sizedsf, buffAbs, data, buffer);
  }  
  vkUnmapMemory( device, stagingBufferMemory );

  // BuffersX::copyBuffer( vertexBufferTemp, sizeof(Temp) );

 
}

uint32_t Buffer::findMemoryType( uint32_t typeFilter, VkMemoryPropertyFlagBits properties )
{
//   VkPhysicalDeviceMemoryProperties memProperties = {};
  vkGetPhysicalDeviceMemoryProperties( VKI.physdevice, &memProperties );
  for ( uint32_t i = 0; i < memProperties.memoryTypeCount; i++ )
  {
    if ( ( typeFilter & ( 1U << i ) ) != 0 && ( memProperties.memoryTypes[i].propertyFlags & properties ) == properties )
    {
      return i;
    }
  }

  printf( "Failed to find suitable memory type" );
}

void Buffer::createSetBuffer(
  VkMemoryPropertyFlagBits properties, VkBuffer & currentBuffer, VkBufferUsageFlagBits usage, size_t sized, VkDeviceMemory & vertexBufferMemory )
{
  const VkBufferCreateInfo allocateInfo = {
    .sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .pNext       = nullptr,
    .size        = sized,
    .usage       = usage,
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
  };

  currentBuffer = Vks::doPointerAlloc5<VkBuffer>( &allocateInfo, vkCreateBuffer );

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements( device, currentBuffer, &memRequirements );

  VkMemoryAllocateInfo allocateInfo1 = {
    .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext           = nullptr,
    .allocationSize  = memRequirements.size,
    .memoryTypeIndex = findMemoryType( memRequirements.memoryTypeBits, properties ),
  };
  //
  BufMemory= Vks::doPointerAlloc5<VkDeviceMemory>( &allocateInfo1, vkAllocateMemory);

  vkBindBufferMemory( device, currentBuffer, vertexBufferMemory, 0 );
}