#include <windows.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_64_BIT_PTR_DEFINES 1
#define VULKAN_HPP_SUPPORT_SPAN
#pragma once
#include <volk.h>
#include <iostream>

#include <GLFW/glfw3.h>

constexpr uint16_t width = 854;
constexpr uint16_t height = 480;
constexpr uint8_t Frames = 3;

constexpr bool ENABLE_VALIDATION_LAYERS = true;

constexpr char* validationLayers = "VK_LAYER_KHRONOS_validation";

const WNDCLASSA  AHack{
  .style=0,
  .lpfnWndProc=nullptr,
  .cbClsExtra=NULL,
  .cbWndExtra=NULL,
  .hInstance=nullptr,
  .hIcon=nullptr,
  .hCursor=nullptr,
  .hbrBackground=nullptr,
  .lpszMenuName=nullptr,
  .lpszClassName=nullptr,
};



inline struct VkInit
{
    GLFWwindow* window=init();
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

     [[nodiscard]] auto  init() const-> GLFWwindow*;
     [[nodiscard]] auto  createInstance() const -> VkInstance;
     [[nodiscard]] auto  doPhysicalDevice() const -> VkPhysicalDevice;
     [[nodiscard]] auto createSurface() const -> VkSurfaceKHR;
     auto doDevice() -> VkDevice;
     auto tst() -> VkDevice;
     ~VkInit() = default;

} VKI;

inline namespace Vks 
{
    //   typedef VkResult ( *callPPPPI )( const void* device, const void * strct, const void *VkAllocationCallbacks, const void *hndle);
    template<typename type, typename handle>
    constexpr auto doPointerAlloc(VkDevice device, auto* strct, type* hndle, handle pHndl) -> type
    {
        (handle(pHndl))(device, strct ,nullptr, hndle);
        return *hndle;
    }
    template<typename type>
    constexpr type doPointerAlloc2(auto* strct, type* hndle, auto pHndl)
    {
        (pHndl)(VKI.device, strct ,nullptr, hndle);
        return *hndle;
    }
    template<typename type>
    constexpr type doPointerAlloc3(auto* strct, auto* hndle)
    {
        type pHndl = nullptr; 
        (hndle)(VKI.device, strct ,nullptr, &pHndl);
        return pHndl;
    }
    template<typename type, typename type2f>
    constexpr type doPointerAlloc3Alt(auto* strct)
    {
        type pHndl = nullptr; 
        (type2f)(VKI.device, strct, &pHndl);
        return pHndl;
    }
    
    template<typename type>
    [[nodiscard]] constexpr auto doPointerAlloc5(auto* __restrict__ strct, auto* hndle) noexcept -> type
    {
        type pHndl; 
        (hndle)(VKI.device, strct, nullptr, &pHndl);
        return pHndl;
    }
    template<typename type>
    constexpr type doPointerAllocSml(auto* strct, /* type* hndle,  */auto pHndl)
    {
        type hndle = nullptr;
        (pHndl)(VKI.device, strct ,nullptr, &hndle);
        return hndle;
    }

    template<typename type>
    constexpr type doPointerAllocX(auto* strct, auto* hndle)
    {
        type pHndl = nullptr; 
        vkCreateGraphicsPipelines(VKI.device, nullptr, 1, strct, nullptr, &pHndl);
        return pHndl;
    }
    
    
}