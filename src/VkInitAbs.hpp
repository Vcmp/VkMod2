#pragma once

#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_64_BIT_PTR_DEFINES 1
#define VULKAN_HPP_SUPPORT_SPAN

#undef GLFW_INCLUDE_VULKAN
#include "volk.h"

#include <iostream>
#include <vector>

struct VkUtilsX
{
    //main Devcies/-Buffer Addresses
    static inline VkPhysicalDevice            physicalDevice;
  static inline VkDevice                    device;
  static inline bool                        a = false;
  static inline uint32_t                    graphicsFamily;
  static inline uint32_t                    transferFamily;
  static inline VkQueue                     GraphicsQueue;
  static inline VkQueue                     TransferQueue[2];

//Tranfer-/Queue handling..
    static inline VkCommandPool               TransferBufferUpload;

}