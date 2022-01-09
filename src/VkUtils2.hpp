#pragma once

#include <stdint.h>
#include <vulkan/vulkan_core.h>
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <iostream>

#include <GLFW/glfw3.h>
#include <vector>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "SwapChainSupportDetails.hpp"
#include "Queues.hpp"
#include "Pipeline.hpp"


typedef VkResult (VKAPI_PTR *callPPPPI)(VkDevice device, const void* pStrct, const uint64_t* pAllocator/*, const PFN_vkVoidFunction* pHndl*/);


static GLFWwindow* window;
static GLFWmonitor* monitor;
static VkInstance vkInstance;
 const static std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
constexpr bool ENABLE_VALIDATION_LAYERS = true;








const VKAPI_CALL inline void clPPPI(void* pStrct,  const char* a)
{
    //vkGetDeviceProcAddr()
    auto x =(callPPPPI)vkGetDeviceProcAddr(device, a);
    x(device, pStrct, nullptr);
    //  callPPPPI(device, pStrct, nullptr, a)
};

long permuteMat(long, long);

struct VkUtils2
{
	
//    private static final long[] pDebugMessenger = new long[1];
    //    X(),
    //    Y
    //    KEY(1)
	 
    static boolean debug;
    static boolean checks;
	 static void extracted();
	 static void createInstance();
	 static void createSurface();
	static bool checkValidationLayerSupport();
	static void checkCall(VkResult);
    
    static void setupDebugMessenger();

    static void pickPhysicalDevice();
    static void createLogicalDevice();
   
    
private:
    static std::vector<const char*> getRequiredExtensions();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT*, void*);
   
   static VkResult createDebugUtilsMessengerEXT(VkInstance,  const VkDebugUtilsMessengerCreateInfoEXT*);
	 
    static bool isDeviceSuitable(VkPhysicalDevice);
    static bool checkDeviceExtensionSupport(VkPhysicalDevice);
};


const static void setupWindow()
{
		glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR , GLFW_RELEASE_BEHAVIOR_NONE);


        window = glfwCreateWindow(854, 480, "VKMod", monitor, 0);


        if(window == NULL) exit(1);

        glfwSetWindowShouldClose(window, false);
        glfwMakeContextCurrent(window);
}


static void extracted()
{
	 std::cout <<1<< "\n";
	 // VkUtils2::createInstance;
}

inline void VkUtils2::createInstance()
    {
       std::cout <<("Creating Instance") << "\n";
        if (ENABLE_VALIDATION_LAYERS && !VkUtils2::checkValidationLayerSupport())
        {
             std::runtime_error("Validation requested but not supported");
        }
        // IntBuffer a = MemSysm.ints(EXTValidationFeatures.VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT, EXTValidationFeatures.VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT, EXTValidationFeatures.VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT, EXTValidationFeatures.VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_RESERVE_BINDING_SLOT_EXT);
        // VkValidationFeaturesEXT extValidationFeatures = VkValidationFeaturesEXT.create(MemSysm.calloc(VkValidationFeaturesEXT.SIZEOF)).sType$Default()
                // .pEnabledValidationFeatures(a);

        VkApplicationInfo vkApplInfo = {
                //memSet(vkApplInfo, 0,VkApplicationInfo.SIZEOF);
                
                .sType=VK_STRUCTURE_TYPE_APPLICATION_INFO,
				 .pNext=nullptr,
                 .pApplicationName="VKMod",
                 .applicationVersion=VK_MAKE_VERSION(1, 0, 0),
                 .pEngineName="No Engine",
                 .engineVersion=VK_MAKE_VERSION(1, 0, 0),
                 
                 .apiVersion=VK_API_VERSION_1_2,
                 
		};
//        MemSysm.Memsys2.free(a);
        // MemSysm.Memsys2.free(vkApplInfo);
        //nmemFree(vkApplInfo);

		// uint32_t glfwExtensionCount = 0;
		// const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
         
         VkInstanceCreateInfo InstCreateInfo;
        InstCreateInfo.sType =VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        InstCreateInfo.pApplicationInfo=&vkApplInfo;
		//InstCreateInfo.enabledLayerCount = 0;
        // PointerBuffer glfwExtensions = getRequiredExtensions();
       auto extensions=getRequiredExtensions();
        InstCreateInfo.ppEnabledExtensionNames=extensions.data();
        // InstCreateInfo.pNext(extValidationFeatures.address());

        InstCreateInfo.enabledExtensionCount=static_cast<uint32_t>(extensions.size());
        
        if(ENABLE_VALIDATION_LAYERS) {
           InstCreateInfo.ppEnabledLayerNames=validationLayers.data();
           InstCreateInfo.enabledLayerCount=static_cast<uint32_t>(validationLayers.size());
        }
        else InstCreateInfo.enabledLayerCount=0;

        // PointerBuffer instancePtr = memPointerBuffer(MemSysm.address, 1);	
        // vkCreateInstance(InstCreateInfo, MemSysm.pAllocator, instancePtr);


        VkUtils2::checkCall(vkCreateInstance(&InstCreateInfo, nullptr, &vkInstance));
        // getVersion();
    }

inline void VkUtils2::createSurface()
    {
        std::cout <<("Creating Surface") << "\n";
        VkWin32SurfaceCreateInfoKHR createSurfaceInfo;
        createSurfaceInfo.sType=VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createSurfaceInfo.hwnd= glfwGetWin32Window(window);
        createSurfaceInfo.hinstance = GetModuleHandle(nullptr);
        createSurfaceInfo.pNext=nullptr;

        VkUtils2::checkCall(vkCreateWin32SurfaceKHR(vkInstance, &createSurfaceInfo, nullptr, &surface));
        
        
    }


    inline bool VkUtils2::checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        return false;
    }


inline void VkUtils2::checkCall(VkResult callPPPPI)
        {
            switch (callPPPPI)
            {
                case VK_SUCCESS :std::cout<<("OK!")<< "\n"; break;
                case VK_NOT_READY :  std::runtime_error("Not ready!"); break;
                case VK_TIMEOUT :  std::runtime_error("Bad TimeOut!"); break;
                case VK_INCOMPLETE :  std::runtime_error("Incomplete!"); break;
                case VK_ERROR_INITIALIZATION_FAILED :    std::runtime_error("Error: bad Initialisation!");break;
                case VK_ERROR_FRAGMENTED_POOL :{   std::runtime_error("Error: bad Mem Alloc");}break;
                case VK_ERROR_OUT_OF_HOST_MEMORY :{    std::runtime_error("No Host Memory");}break;
                case VK_ERROR_OUT_OF_DEVICE_MEMORY :{   std::runtime_error("No Device Memory");}break;
                default :{    std::runtime_error("Unknown Error!");}break;
            }
        }

inline std::vector<const char*> VkUtils2::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions+glfwExtensionCount);
     if(ENABLE_VALIDATION_LAYERS)
     {
         extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
     }
     return extensions;
}

VKAPI_ATTR inline VkBool32 VKAPI_CALL VkUtils2::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData)
    {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

inline void VkUtils2::setupDebugMessenger()
    {
        if(!ENABLE_VALIDATION_LAYERS) {
            return;
        }

        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType=VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity=VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
        createInfo.messageType=VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback=VkUtils2::debugCallback;
        createInfo.pUserData=nullptr;

        VkUtils2::checkCall(createDebugUtilsMessengerEXT(vkInstance, &createInfo));
        //debugMessenger = pDebugMessenger[0];
    }
    
inline VkResult VkUtils2::createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo) 
{
    static VkDebugUtilsMessengerEXT debugUtils;
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, nullptr, &debugUtils);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}








inline void VkUtils2::pickPhysicalDevice()
{
    std::cout <<("Picking Physical Device")<<"\n";
    uint32_t deviceCount;
    checkCall(vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr));
    if(deviceCount == 0) std::runtime_error("Failed to find GPUs with Vulkan support");
    std::vector<VkPhysicalDevice> ppPhysicalDevices(deviceCount);

    VkPhysicalDevice device;
    std::cout <<("Enumerate Physical Device") << "\n";
   checkCall(vkEnumeratePhysicalDevices(vkInstance, &deviceCount, ppPhysicalDevices.data()));
     for(const VkPhysicalDevice& d : ppPhysicalDevices)
        {  
            std::cout <<("Check Device:") << d << "\n";
            if(isDeviceSuitable(d)) {
                std::cout <<("Device Suitable:") << d << "\n";
                physicalDevice = d;
                break;
            }
             std::cout <<("Device Not Suitable:") << d << "\n";
           
        }
        if (physicalDevice == VK_NULL_HANDLE) {
            std::runtime_error("Failed to find a suitable GPU");
        }


}
//Use VK Tutorial refernce as that sems to be far m re replable that the prior java approach used
inline bool VkUtils2::isDeviceSuitable(const VkPhysicalDevice device)
 {

      VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    Queues::enumerateDetermineQueueFamilies(device);    
    

    return  Queues::isComplete();/*deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
           deviceFeatures.geometryShader;*/

        // bool extensionsSupported = checkDeviceExtensionSupport(device);
        // bool swapChainAdequate = false;
        // std::cout << extensionsSupported << "\n";
        // if(extensionsSupported) {
		// 	std::cout << "Verifying querySwapChainSupport" << "\n";
        //     SwapChainSupportDetails::querySwapChainSupport(device);
        //     swapChainAdequate = formats.format && presentModes;
        // }
		
		// std::cout << "Enumerating Queuefamilies" << "\n";
        // Queues::enumerateDetermineQueueFamilies(device);
		// return /* Queues.isComplete() && */ extensionsSupported && swapChainAdequate;
}

//  inline bool  VkUtils2::checkDeviceExtensionSupport(VkPhysicalDevice device) {
//      std::cout << "Verifying checkDeviceExtensionSupport" << "\n";
//         uint32_t extensionCount;
//         vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);
//         VkExtensionProperties availableExtensions;
//         vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, &availableExtensions);
        
        
        
//         return sizeof(availableExtensions.extensionName)!=NULL;
//     }


    inline void VkUtils2::createLogicalDevice() {

        
            uint32_t uniqueQueueFamilies[] = {graphicsFamily};


//                Queues.findQueueFamilies(Queues.physicalDevice);
            //TODO: Fix bug with NULL/Missing.Invalid Queues
            VkDeviceQueueCreateInfo queueCreateInfos;
            const float priority = 1.0f;
            // for(int i = 0; i < 1; i++) {
                queueCreateInfos.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfos.queueFamilyIndex=uniqueQueueFamilies[0];
                queueCreateInfos.pQueuePriorities=&priority;
            
            VkPhysicalDeviceVulkan12Features deviceVulkan12Features;
                    deviceVulkan12Features.descriptorBindingPartiallyBound=true,
                    deviceVulkan12Features.imagelessFramebuffer=true;
                    
         

            VkPhysicalDeviceFeatures deviceFeatures;

            VkPhysicalDeviceFeatures2 deviceFeatures2;
                    deviceFeatures2.sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
                    deviceFeatures2.pNext=&deviceVulkan12Features;
                    deviceFeatures2.features=deviceFeatures;



            //.fillModeNonSolid(true) //dneeded to adres valditaion errors when using VK_POLIGYON_MODE_LINE or POINT
            //.robustBufferAccess(true);
//                        .geometryShader(true);
//                        .pipelineStatisticsQuery(true)
//                        .alphaToOne(false);
            vkGetPhysicalDeviceFeatures2(physicalDevice, &deviceFeatures2);
            VkDeviceCreateInfo createInfo;
                    createInfo.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                    createInfo.pNext=&deviceFeatures2;
                    createInfo.pQueueCreateInfos=&queueCreateInfos;


            // PointerBuffer value = asPointerBuffer(DEVICE_EXTENSIONS);
            // memPutLong(createInfo.address() + VkDeviceCreateInfo.PPENABLEDEXTENSIONNAMES, value.address0());
            // memPutInt(createInfo.address() + VkDeviceCreateInfo.ENABLEDEXTENSIONCOUNT, value.remaining());

            // if(ENABLE_VALIDATION_LAYERS) {
            //     createInfo.ppEnabledLayerNames(asPointerBuffer(VALIDATION_LAYERS));
            // }
            vkCreateDevice(physicalDevice, &createInfo, nullptr, &device );


              vkGetDeviceQueue(device, graphicsFamily, 0, &GraphicsQueue);
       
    }

    //  static void setupQueues()
    // {

    //     nvkGetDeviceQueue(device, Queues.graphicsFamily, 0,MemSysm.address);
    //     Queues.graphicsQueue = new VkQueue(memGetLong(MemSysm.address), device);

    //     nvkGetDeviceQueue(device, Queues.presentFamily, 0,MemSysm.address);
    //     Queues.presentQueue = new VkQueue(memGetLong(MemSysm.address), device);

    // }