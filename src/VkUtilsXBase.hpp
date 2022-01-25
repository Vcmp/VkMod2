#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
// #ifdef __cplusplus
// #define VULKAN_HPP_CPLUSPLUS 201803L
// #endif
#include <vulkan/vulkan.hpp>
// #define VK_USE_64_BIT_PTR_DEFINES 1
//#define VK_NO_PROTOTYPES
// #define VK_ENABLE_BETA_EXTENSIONS
// #include <stdint.h>

#ifdef _MSVC_LANG
#define _MSVC_LANG 201803L
#endif


 #include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// #include <vcruntime.h>

#include <iostream>
#include <vector>


  
    

// VkPhysicalDevicePortabilitySubsetFeaturesKHR ptr = {};
    
   
inline namespace{



static constexpr uint8_t Frames=3;
static constexpr bool checks=true;

    static constexpr bool debug=true;
    
    static constexpr bool ENABLE_VALIDATION_LAYERS=debug; //todo: Posible Bug: ValidationLayersBreak Shader Compilation due to (Presumably) incorerctly marking the cimpiled Spir-V Shaders/Files as having/Containing Invalid Magic Numbers
    
    static const std::vector<const char*>   validationLayers={"VK_LAYER_KHRONOS_validation"};
    static const std::vector<const char*> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    
    static VkDevice device;
    
  
static inline  void checkCall(VkResult callPPPPI)
        {
            if constexpr(checks)
            switch (callPPPPI)
            {
                case VK_SUCCESS :/* std::cout<<("OK!")<< "\n"; */ break;
                case VK_NOT_READY : throw std::runtime_error("Not ready!"); break;
                case VK_TIMEOUT : throw std::runtime_error("Bad TimeOut!"); break;
                case VK_INCOMPLETE : throw std::runtime_error("Incomplete!"); break;
                case VK_ERROR_INITIALIZATION_FAILED :  throw  std::runtime_error("Error: bad Initialisation!");break;
                case VK_ERROR_DEVICE_LOST :  throw  std::runtime_error("Error: Device Failed/Lost!");break;
                case VK_ERROR_FRAGMENTED_POOL :{ throw std::runtime_error("Error: bad Mem Alloc");}break;
                case VK_ERROR_OUT_OF_HOST_MEMORY :{  throw  std::runtime_error("No Host Memory");}break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY :{ throw  std::runtime_error("No Device Memory");}break;
                case VK_ERROR_UNKNOWN :{ throw  std::runtime_error("Unknown Error!|");}break;
                case VK_ERROR_OUT_OF_POOL_MEMORY :{ throw  std::runtime_error("Out of PooL Memory");}break;
                case VK_ERROR_INVALID_EXTERNAL_HANDLE :{ throw  std::runtime_error("VK_ERROR_INVALID_EXTERNAL_HANDLE");}break;
                case VK_ERROR_FRAGMENTATION :{ throw  std::runtime_error("VK_ERROR_INVALID_EXTERNAL_HANDLE");}break;
                case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS :{ throw  std::runtime_error("VK_ERROR_FRAGMENTATION");}break;
                case VK_ERROR_SURFACE_LOST_KHR :{ throw  std::runtime_error("VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS");}break;
                case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR :{ throw  std::runtime_error("VK_ERROR_NATIVE_WINDOW_IN_USE_KHR");}break;
                case VK_ERROR_OUT_OF_DATE_KHR :{throw std::runtime_error("");}break;
                case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR :{throw std::runtime_error("");}break;
                case VK_ERROR_VALIDATION_FAILED_EXT :{throw std::runtime_error("");}break;
                case VK_ERROR_INVALID_SHADER_NV :{throw std::runtime_error("");}break;
                case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT :{throw std::runtime_error("");}break;
                case VK_ERROR_NOT_PERMITTED_EXT :{throw std::runtime_error("");}break;
                case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT :{throw std::runtime_error("");}break;
                case VK_THREAD_IDLE_KHR :{throw std::runtime_error("");}break;
                case VK_THREAD_DONE_KHR :{throw std::runtime_error("");}break;
                case VK_OPERATION_DEFERRED_KHR :{throw std::runtime_error("");}break;
                case VK_OPERATION_NOT_DEFERRED_KHR :{throw std::runtime_error("");}break;
                case VK_PIPELINE_COMPILE_REQUIRED_EXT :{throw std::runtime_error("");}break ;
              
                case VK_SUBOPTIMAL_KHR :{ throw  std::runtime_error("VK_SUBOPTIMAL_KHR");}break;
                
                default :{ std::cout<<callPPPPI<<"\n"; throw  std::runtime_error("Unknown Error!");}break;
            }
        }


        typedef VkResult (__vectorcall *callPPPPI) (VkDevice, const void*, const VkAllocationCallbacks*, const void* , const PFN_vkVoidFunction pHndl);
        
        /*todo: Adiitonal posible Bug: if a typeDef Cast/PointerFunction/Aslias e.g .Misc is used to allow access to .call vkPipelineLayoutCreateInfo, the Validtaion layers incorrertcly warn that VkGraphicsPipelineCreateInfo struct is mising the cprrect sType 
        * the only way to correct this is to manuall/Dierctly exempt the "pipelineCache" and "createInfoCount" Arguments/Parametsr of the call, Which causes Misiing createInfoCount  and VkPipelineCache  issues but allows the pipeline to be created properly/correctly
        * this is possibly a Driver Bug/ NV/nSight layer Bug/issue (as a very old beta driver is being utilised [451.74]) but is unconfirmed currently
        */
        typedef VkResult (__vectorcall *callPPPPJI) (VkDevice,
                                         const void *,
                                         uint32_t*,
                                         const void *,
                                          VkAllocationCallbacks *,
                                        const void *,
                                         PFN_vkVoidFunction pHndl);
        // typedef const VkResult (__vectorcall *callPPI) (VkDevice,
        //                                 //  VkPipelineCache*,
        //                                  const void *,uint32_t*,
                                         
        //                                  const VkAllocationCallbacks *);

static inline void clPPPI(const void* pStrct,  const char* a, const void *object)
{
    //vkGetDeviceProcAddr()
    // auto xx= ;
    const PFN_vkVoidFunction Hndl = vkGetDeviceProcAddr(device, a);
    // const callPPPPI x =reinterpret_cast<callPPPPI>(vkGetDeviceProcAddr(device, a));
    // std::cout << &x << "\n";
    // std::cout << &pStrct << &object<<&a<<"\n";
    std::cout << a<<"\n";
    // std::cout << object<<"\n";
    // const VkResult VkR =x(device, pStrct, nullptr, object);
    checkCall((reinterpret_cast<callPPPPI>(Hndl))(device, pStrct, nullptr, object, Hndl));
    if (object == nullptr)
    {
        throw std::runtime_error("bad Alloctaion!: Null handle!");
    }
    // return VkR;
    //  callPPPPI(device, pStrct, nullptr, a)
}
// static inline int doSized(const void* aabs, const void* abs2x)
// {
//     return sizeof(aabs)/sizeof(abs2x);
// }
static inline void clPPPJI(void * pStrct, uint32_t* ax, const char* a,  void *object)
{
    //vkGetDeviceProcAddr()
    // auto xx=PFN_vkVoidFunction(swapChain);
    
      const PFN_vkVoidFunction Hndl = vkGetDeviceProcAddr(device, a);
    //const callPPPPI ss=reinterpret_cast<callPPPPI>(vkGetDeviceProcAddr(device, a));
    // std::cout << &x << "\n";
    // std::cout << &pStrct << &object<<&a<<"\n";
    // std::cout << a<<"\n";
    // std::cout << object<<"\n";
    // VkPipelineCache axx =nullptr;
    // const VkResult VkR =x(device, pStrct, nullptr, object);
    //ss(device, pStrct, nullptr, object);
    checkCall((reinterpret_cast<callPPPPJI>(Hndl))(device, nullptr, ax, pStrct, nullptr, object, Hndl));

     if (object == nullptr)
    {
        throw std::runtime_error("bad Alloctaion!: Null handle!");
    }
    // return VkR;
    //  callPPPPI(device, pStrct, nullptr, a)
}

};
