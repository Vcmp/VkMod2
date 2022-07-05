#pragma once




#include "Vks.tpp"
static [[clang::trivial_abi]] struct Queues
{
  // static inline VkPhysicalDevice            physicalDevice;
  static inline VkCommandPool               commandPool;
  static inline VkCommandPool               commandPool2;
  // static inline VkDevice                    device;
  static inline bool                        a = false;
  // static inline uint32_t                    graphicsFamily;
  // static inline uint32_t                    transferFamily;
  // static inline VkQueue                     GraphicsQueue;
  // static inline VkQueue                     TransferQueue;
  static constexpr VkCommandBufferBeginInfo vkCommandBufferBeginInfo = { .sType = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO ),
                                                                         .pNext = VK_NULL_HANDLE,
                                                                         .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT };
  // static inline VkSurfaceKHR                surface;
  static inline VkCommandBuffer             commandBuffer;
  constexpr static const VkSubmitInfo       submitInfo1 = {
          .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .pNext = VK_NULL_HANDLE, .commandBufferCount = ( 1 ), .pCommandBuffers = &commandBuffer
  };

  static void createCommandPool();
  static void beginSingleTimeCommands();
  static void endSingleTimeCommands();

};
