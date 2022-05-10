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

inline const struct VkInit
{
    GLFWwindow* window;
     VkInstance instance;
    VkSurfaceKHR surface;
     VkPhysicalDevice physdevice;
     VkDevice device;
    uint32_t graphicsFamily;
    uint32_t transferFamily;
    VkQueue GraphicsQueue;
    VkQueue TransferQueue;
    // SwapChain SW;
    constexpr VkInit() : window(init()), instance(createInstance()), surface(createSurface()), physdevice(doPhysicalDevice()), device(doDevice())
    {
        
        
    };

      VkInit(const VkInit&);                 // Prevent copy-construction
  VkInit& operator=(const VkInit&); 

     auto  init() -> GLFWwindow*;
     auto  createInstance() -> VkInstance;
     auto  doPhysicalDevice() -> VkPhysicalDevice;
     auto createSurface() -> VkSurfaceKHR;
     auto doDevice() -> VkDevice;
     auto tst() -> VkDevice;
     ~VkInit()
     {
        //  std::cout << "Destructing:..." << "\n";
     }

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