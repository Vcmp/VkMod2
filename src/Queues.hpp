#pragma once
#include "VkUtilsXBase.hpp"
static constexpr struct Queues {
static inline VkPhysicalDevice physicalDevice;
static inline boolean a = false;
static inline uint32_t graphicsFamily;
static inline uint32_t transferFamily;
static inline VkQueue GraphicsQueue;
static inline VkQueue TransferQueue[2];
static inline uint64_t commandPool;
static inline uint64_t commandPool2;
static constexpr VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {
      .sType = (VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO),
      .pNext = VK_NULL_HANDLE,
      .flags = (VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT)};
static inline VkSurfaceKHR surface;
static inline VkCommandBuffer commandBuffer;

static void createCommandPool();
static VkCommandBuffer beginSingleTimeCommands();
static void endSingleTimeCommands(VkCommandBuffer &commandBuffer);

} inline queues;

inline void Queues::createCommandPool() {
  const VkCommandPoolCreateInfo poolInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .pNext=nullptr,
      .queueFamilyIndex = graphicsFamily,
  };
  // poolInfo.flags=0;
  // Memsys2.free(poolInfo);
  commandPool = pstrct.clPPPI2(&poolInfo, "vkCreateCommandPool"); 
  const VkCommandPoolCreateInfo poolInfo2 = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .queueFamilyIndex = transferFamily,
  };
  // poolInfo.flags=0;
  // Memsys2.free(poolInfo);
  commandPool2 = pstrct.clPPPI2(&poolInfo2, "vkCreateCommandPool");
}

inline VkCommandBuffer Queues::beginSingleTimeCommands() 
{

  const VkCommandBufferAllocateInfo allocateInfo
  {
    .sType = (VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO),
    .pNext = VK_NULL_HANDLE,
    .commandPool = (VkCommandPool)(Queues::commandPool2),
    .level = (VK_COMMAND_BUFFER_LEVEL_PRIMARY),
    .commandBufferCount = (1),
  };
  
  vkAllocateCommandBuffers(pstrct.device, &allocateInfo, &commandBuffer);
 
  vkBeginCommandBuffer(commandBuffer, &vkCommandBufferBeginInfo);
  return commandBuffer;
}

inline void Queues::endSingleTimeCommands(VkCommandBuffer &commandBuffer) {
  vkEndCommandBuffer(commandBuffer);
  const VkSubmitInfo submitInfo1 = {.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                                    .pNext = VK_NULL_HANDLE,
                                    .commandBufferCount = (1),
                                    .pCommandBuffers = &commandBuffer};
  //            VkSubmitInfo.ncommandBufferCount(submitInfo1, 1);
  a|= a;
  vkQueueSubmit(TransferQueue[a], 1, &submitInfo1, VK_NULL_HANDLE);
  vkQueueWaitIdle(TransferQueue[a|a]);
  vkFreeCommandBuffers(pstrct.device, (VkCommandPool)Queues::commandPool2, 1, &commandBuffer);
}
 // namespace Queues