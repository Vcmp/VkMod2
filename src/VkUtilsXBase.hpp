#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_64_BIT_PTR_DEFINES 1
//#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.hpp>


// #include <vcruntime.h>

#include <iostream>
#include <vector>


  
    

//    VkPhysicalDevicePortabilitySubsetFeaturesKHR ptr = {};
    
   
inline namespace{



static constexpr inline bool checks=true;

    static constexpr bool debug=true;
    
    static constexpr bool ENABLE_VALIDATION_LAYERS=debug;
    
    static inline const std::vector<const char*>   validationLayers={"VK_LAYER_KHRONOS_validation"};
    static inline constexpr  char* deviceExtensions[] = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

     
    static inline VkDevice device;
    static inline VkSwapchainKHR swapChain;
    static inline VkImage pSwapchainImages[3];
static inline const void checkCall(VkResult callPPPPI)
        {
            if(checks)
            switch (callPPPPI)
            {
                case VK_SUCCESS :std::cout<<("OK!")<< "\n"; break;
                case VK_NOT_READY : throw std::runtime_error("Not ready!"); break;
                case VK_TIMEOUT : throw std::runtime_error("Bad TimeOut!"); break;
                case VK_INCOMPLETE : throw std::runtime_error("Incomplete!"); break;
                case VK_ERROR_INITIALIZATION_FAILED :  throw  std::runtime_error("Error: bad Initialisation!");break;
                case VK_ERROR_FRAGMENTED_POOL :{ throw std::runtime_error("Error: bad Mem Alloc");}break;
                case VK_ERROR_OUT_OF_HOST_MEMORY :{  throw  std::runtime_error("No Host Memory");}break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY :{ throw  std::runtime_error("No Device Memory");}break;
                default :{    std::runtime_error("Unknown Error!");}break;
            }
        }
};

        typedef const VkResult (__vectorcall *callPPPPI) (VkDevice device, const void* pStrct, const VkAllocationCallbacks* pAllocator, const void* hndl/*, const PFN_vkVoidFunction* pHndl*/);

static inline VkResult clPPPI(const void* pStrct,  const char* a, const void *object)
{
    //vkGetDeviceProcAddr()
    // auto xx=PFN_vkVoidFunction(swapChain);
    
    const callPPPPI x =reinterpret_cast<callPPPPI>(vkGetDeviceProcAddr(device, a));
    std::cout << &x << "\n";
    std::cout << &pStrct << &object<<&a<<"\n";
    std::cout << a<<"\n";
    std::cout << object<<"\n";
    const VkResult VkR =x(device, pStrct, nullptr, object);
    checkCall(VkR);
    return VkR;
    //  callPPPPI(device, pStrct, nullptr, a)
};