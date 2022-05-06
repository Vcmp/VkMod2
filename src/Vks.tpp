#pragma once
#include <volk.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

constexpr uint8_t width = 854;
constexpr uint8_t height = 480;
constexpr uint8_t Frames = 3;

struct VkInit
{
    GLFWwindow* window;
    const VkInstance instance;
    VkDevice device;
    VkPhysicalDevice physdevice;
    VkSurfaceKHR surface;
    uint32_t graphicsFamily;
    uint32_t transferFamily;
    VkQueue GraphicsQueue;
    VkQueue TransferQueue;
    // SwapChain SW;
    VkInit() : window(init()), instance(createInstance()), surface(createSurface())
    {
        physdevice = doPhysicalDevice();
        device = doDevice();
    };

     GLFWwindow*  init();
     VkInstance  createInstance();
     VkPhysicalDevice  doPhysicalDevice();
     VkSurfaceKHR createSurface();
     VkDevice doDevice();

} VKI;

inline namespace Vks
{
    //   typedef VkResult ( *callPPPPI )( const void* device, const void * strct, const void *VkAllocationCallbacks, const void *hndle);
    template<typename type, typename handle>
    constexpr type doPointerAlloc(VkDevice device, auto* strct, type* hndle, handle pHndl)
    {
        (handle(pHndl))(device, strct ,nullptr, hndle);
        return *hndle;
    }
    
}