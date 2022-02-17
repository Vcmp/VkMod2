#pragma once
#include "VkUtilsXBase.hpp"

static constexpr struct Queues
{
  static inline VkCommandPool               commandPool;
  static inline VkCommandPool               commandPool2;
  static inline VkPhysicalDevice            physicalDevice;
  static inline boolean                     a = false;
  static inline uint32_t                    graphicsFamily;
  static inline uint32_t                    transferFamily;
  static inline VkQueue                     GraphicsQueue;
  static inline VkQueue                     TransferQueue[2];
  static constexpr VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {
    .sType = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO ),
    .pNext = VK_NULL_HANDLE,
    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT
  };
  static inline VkSurfaceKHR          surface;
  static inline VkCommandBuffer       commandBuffer;
  constexpr static const VkSubmitInfo submitInfo1 = { .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                                                      .pNext              = VK_NULL_HANDLE,
                                                      .commandBufferCount = ( 1 ),
                                                      .pCommandBuffers    = &commandBuffer };

  static void createCommandPool();
  static void beginSingleTimeCommands();
  static void endSingleTimeCommands();
} inline queues;

inline void Queues::createCommandPool()
{
  const VkCommandPoolCreateInfo poolInfo = {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .queueFamilyIndex = 0,
  };
  // poolInfo.flags=0;
  // Memsys2.free(poolInfo);
  commandPool = VkUtilsXBase::clPPPI2<VkCommandPool_T *>( &poolInfo, "vkCreateCommandPool" );
  const VkCommandPoolCreateInfo poolInfo2 = {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .queueFamilyIndex = 1,
  };
  // poolInfo.flags=0;
  // Memsys2.free(poolInfo);RRRR
  commandPool2 = VkUtilsXBase::clPPPI2<VkCommandPool>( &poolInfo2, "vkCreateCommandPool" );
  if ( commandBuffer == nullptr )
  {
    const VkCommandBufferAllocateInfo allocateInfo{
      .sType              = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
      .pNext              = VK_NULL_HANDLE,
      .commandPool        = (VkCommandPool)( Queues::commandPool2 ),
      .level              = ( VK_COMMAND_BUFFER_LEVEL_PRIMARY ),
      .commandBufferCount = ( 1 ),
    };

    vkAllocateCommandBuffers( VkUtilsXBase::device, &allocateInfo, &commandBuffer );
  }
}

inline void Queues::beginSingleTimeCommands()
{
  vkBeginCommandBuffer( commandBuffer, &vkCommandBufferBeginInfo );
  // return commandBuffer;
}

inline void Queues::endSingleTimeCommands()
{
  vkEndCommandBuffer( commandBuffer );

  //            VkSubmitInfo.ncommandBufferCount(submitInfo1, 1);
  a = ( a ^ 1 );
  vkQueueSubmit( TransferQueue[a], 1, &submitInfo1, VK_NULL_HANDLE );
  vkQueueWaitIdle( TransferQueue[a] );
  vkResetCommandPool( VkUtilsXBase::device,
                      reinterpret_cast<VkCommandPool>( commandPool2 ),
                      VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT );
  // vkFreeCommandBuffers(device, (VkCommandPool)Queues::commandPool2, 1,
  // &commandBuffer);
}
// namespace Queues