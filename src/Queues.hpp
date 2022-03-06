#pragma once
#include "VkUtilsXBase.hpp"

static constexpr struct Queues
{
  static inline VkCommandPool               commandPool;
  static inline VkCommandPool               commandPool2;
  static inline VkPhysicalDevice            physicalDevice;
  static inline VkDevice                    device;
  static inline bool                        a = false;
  static inline uint32_t                    graphicsFamily;
  static inline uint32_t                    transferFamily;
  static inline VkQueue                     GraphicsQueue;
  static inline VkQueue                     TransferQueue[2];
  static constexpr VkCommandBufferBeginInfo vkCommandBufferBeginInfo = { .sType = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO ),
                                                                         .pNext = VK_NULL_HANDLE,
                                                                         .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT };
  static inline VkSurfaceKHR                surface;
  static inline VkCommandBuffer             commandBuffer;
  constexpr static const VkSubmitInfo       submitInfo1 = {
          .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .pNext = VK_NULL_HANDLE, .commandBufferCount = ( 1 ), .pCommandBuffers = &commandBuffer
  };

  static void createCommandPool();
  static void beginSingleTimeCommands();
  static void endSingleTimeCommands();
  template <typename X, typename T>
  static constexpr auto clPPPI3A( const auto * __restrict__ pStrct, const char * __restrict__ a )
  {
    // const VkDevice aa = volkGetLoadedDevice();
    X object;
    T( vkGetDeviceProcAddr( Queues::device, a ) )( Queues::device, pStrct, nullptr, &object );
    return object;
  }
} inline const queues;

inline void Queues::createCommandPool()
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

    VkUtilsXBase::clPPI3<PFN_vkAllocateCommandBuffers>( &allocateInfo, "vkAllocateCommandBuffers", &commandBuffer );
  }
}

inline void Queues::beginSingleTimeCommands()
{
  VkUtilsXBase::clPI<PFN_vkBeginCommandBuffer>( commandBuffer, "vkBeginCommandBuffer", &vkCommandBufferBeginInfo );
}

inline void Queues::endSingleTimeCommands()
{
  VkUtilsXBase::clP<PFN_vkEndCommandBuffer>( commandBuffer, "vkEndCommandBuffer" );

  a = ( a ^ 1 );
  vkQueueSubmit( TransferQueue[a], 1, &submitInfo1, VK_NULL_HANDLE );
  vkQueueWaitIdle( TransferQueue[a] );
  vkResetCommandPool( device, ( commandPool2 ), VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT );
}
