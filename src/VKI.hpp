

#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_64_BIT_PTR_DEFINES 1
#define VULKAN_HPP_SUPPORT_SPAN
#define WIN32_LEAN_AND_MEAN
#pragma once
#include <volk.h>
#include <iostream>
#include <minwindef.h>
#include <windef.h>
#include <winuser.h>



constexpr uint16_t width = 854;
constexpr uint16_t height = 480;
constexpr uint8_t Frames = 8;

constexpr bool ENABLE_VALIDATION_LAYERS = false;
constexpr bool checks = true;

constexpr char* validationLayers = "VK_LAYER_KHRONOS_validation";

struct VkInit
{
    HINSTANCE inst;
    HWND window=init(inst);
    VkInstance instance=createInstance();
    VkSurfaceKHR surface = createSurface();
    VkPhysicalDevice physdevice = doPhysicalDevice();
    VkDevice device = doDevice();
    uint32_t graphicsFamily;
    uint32_t transferFamily;
    VkQueue GraphicsQueue;
    // VkQueue PresentQueue;
    VkQueue TransferQueue;
    // SwapChain SW;
    explicit constexpr VkInit(HINSTANCE instance): inst(instance) {};
    VkInit(VkInit const &) = delete;
  VkInit& operator=(const VkInit&) = delete; 
     [[nodiscard]] auto init(HINSTANCE) const -> HWND;
     [[nodiscard]] auto  createInstance() const -> VkInstance;
     [[nodiscard]] auto  doPhysicalDevice() const -> VkPhysicalDevice;
     [[nodiscard]] auto createSurface() const -> VkSurfaceKHR;
     auto doDevice() -> VkDevice;
     template <typename name> auto vkEnumSet(auto a) const;
     template <typename name>  auto  vkEnumSet2(auto a) const -> std::vector<name>;
     [[nodiscard, gnu::pure, gnu::const, clang::vectorcall]] constexpr auto tst() const noexcept -> VkDevice{ return this->device; };

};
// VkInit VkInit::VKI;