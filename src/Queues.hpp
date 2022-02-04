#pragma once
#include "VkUtilsXBase.hpp"
#include <vulkan/vulkan_core.h>

inline namespace Queues {
static VkPhysicalDevice physicalDevice;

static uint32_t graphicsFamily;
static uint32_t presentFamily;
static VkQueue GraphicsQueue;
static VkQueue PresentQueue;
static uint64_t commandPool;
static uint64_t commandPool2;

static VkSurfaceKHR surface;

static inline void createCommandPool();
static inline VkCommandBuffer beginSingleTimeCommands();
static void endSingleTimeCommands(VkCommandBuffer &commandBuffer);

};

static inline void Queues::createCommandPool() {
  const VkCommandPoolCreateInfo poolInfo = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .queueFamilyIndex = Queues::graphicsFamily,
  };
  // poolInfo.flags=0;
  // Memsys2.free(poolInfo);
  Queues::commandPool = clPPPI2(&poolInfo, "vkCreateCommandPool"); 
  const VkCommandPoolCreateInfo poolInfo2 = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
      .queueFamilyIndex = Queues::presentFamily,
  };
  // poolInfo.flags=0;
  // Memsys2.free(poolInfo);
  Queues::commandPool2 = clPPPI2(&poolInfo2, "vkCreateCommandPool");
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
  VkCommandBuffer commandBuffer;
  vkAllocateCommandBuffers(device, &allocateInfo, &commandBuffer);
  constexpr VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {
      .sType = (VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO),
      .pNext = VK_NULL_HANDLE,
      .flags = (VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT)};
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

  vkQueueSubmit(Queues::PresentQueue, 1, &submitInfo1, VK_NULL_HANDLE);
  vkQueueWaitIdle(PresentQueue);
  vkFreeCommandBuffers(device, (VkCommandPool)Queues::commandPool2, 1, &commandBuffer);
}
 // namespace Queues