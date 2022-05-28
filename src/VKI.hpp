

#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_64_BIT_PTR_DEFINES 1
#define VULKAN_HPP_SUPPORT_SPAN
#pragma once
#include <volk.h>
#include <iostream>




constexpr uint16_t width = 854;
constexpr uint16_t height = 480;
constexpr uint8_t Frames = 3;

constexpr bool ENABLE_VALIDATION_LAYERS = true;

constexpr char* validationLayers = "VK_LAYER_KHRONOS_validation";

inline struct VkInit
{
    const HWND window=init();
     const VkInstance instance=createInstance();
    const VkSurfaceKHR surface = createSurface();
     const VkPhysicalDevice physdevice = doPhysicalDevice();
     const VkDevice device = doDevice();
    uint32_t graphicsFamily;
    uint32_t transferFamily;
    VkQueue GraphicsQueue;
    // VkQueue PresentQueue;
    VkQueue TransferQueue;
    // SwapChain SW;
    constexpr VkInit() = default;;
    VkInit(VkInit const &) = delete;
  VkInit& operator=(const VkInit&) = delete; 

     [[nodiscard]] auto init() const -> HWND;
     [[nodiscard]] auto  createInstance() const -> VkInstance;
     [[nodiscard]] auto  doPhysicalDevice() const -> VkPhysicalDevice;
     [[nodiscard]] auto createSurface() const -> VkSurfaceKHR;
     auto doDevice() -> VkDevice;
     auto tst() -> VkDevice;
     ~VkInit() = default;

} VKI;