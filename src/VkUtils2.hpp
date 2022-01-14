#include <stdexcept>
// #include <vcruntime.h>
#include <string>
#include <vulkan/vulkan_core.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_64_BIT_PTR_DEFINES 1
#define __AVX2__ 1
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <stdint.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>
#include <immintrin.h>
#include <avx2intrin.h>
#include "SwapChainSupportDetails.hpp"
//#include "Queues.hpp"
uint32_t xa[32];
__m256i x = _mm256_load_si256((__m256i*)(&xa));


typedef VkResult (VKAPI_CALL *callPPPPI) (VkDevice device, const void* pStrct, const VkAllocationCallbacks* pAllocator, PFN_vkVoidFunction* hndl/*, const PFN_vkVoidFunction* pHndl*/);


static GLFWwindow* window;
static GLFWmonitor* monitor;
static VkInstance vkInstance;
 const static std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const static std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

    constexpr bool debug=true;
    constexpr bool checks=true;
    constexpr bool ENABLE_VALIDATION_LAYERS=debug;
    







const VKAPI_CALL inline void clPPPI(void* pStrct,  const char* a, PFN_vkVoidFunction *object)
{
    //vkGetDeviceProcAddr()
    // auto xx=PFN_vkVoidFunction(swapChain);
    auto x =(callPPPPI)vkGetDeviceProcAddr(device, a);
    std::cout << &x << "\n";
    VkResult VkR =x(device, pStrct, nullptr, object);
    //  callPPPPI(device, pStrct, nullptr, a)
};

long permuteMat(long, long);


class VkUtils2
{
	
//    private static final long[] pDebugMessenger = new long[1];
    //    X(),
    //    Y
    //    KEY(1)
	public:

    
         static void setupWindow();

	 static void createInstance();
	 static void createSurface();
	static bool checkValidationLayerSupport();
	
    
    static void setupDebugMessenger();

    static void pickPhysicalDevice();
    static void createLogicalDevice();
    void createSwapChain();
    static void createImageViews();
    void extracted() {
      VkUtils2::setupWindow();
      VkUtils2::createInstance();
      VkUtils2::setupDebugMessenger();
      VkUtils2::createSurface();
      VkUtils2::pickPhysicalDevice();
      VkUtils2::createLogicalDevice();
      VkUtils2::createSwapChain();
    //   VkUtils2::createImageViews();
      // VkUtils2::createInstance;
    }
   
private:
    static void checkCall(VkResult);
    static std::vector<const char*> getRequiredExtensions();
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT*, void*);
   
   static VkResult createDebugUtilsMessengerEXT(VkInstance,  const VkDebugUtilsMessengerCreateInfoEXT*);
	 
    static bool isDeviceSuitable(VkPhysicalDevice);
    static void checkDeviceExtensionSupport(VkPhysicalDevice);

    static const VkSurfaceFormatKHR querySwapChainSupport(VkPhysicalDevice);

    VkSwapchainKHR swapChain;
};


namespace VkU2 {
    // void extracted() {
    //   VkUtils2::setupWindow();
    //   VkUtils2::createInstance();
    //   VkUtils2::setupDebugMessenger();
    //   VkUtils2::createSurface();
    //   VkUtils2::pickPhysicalDevice();
    //   VkUtils2::createLogicalDevice();
    //   VkUtils2::createSwapChain();
    // //   VkUtils2::createImageViews();
    //   // VkUtils2::createInstance;
    // }
};


inline void VkUtils2::setupWindow()
{
		glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
        glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR , GLFW_RELEASE_BEHAVIOR_NONE);


        window = glfwCreateWindow(854, 480, "VKMod", nullptr, 0);


        if(window == NULL) exit(1);

        glfwSetWindowShouldClose((window), false);
        glfwMakeContextCurrent((window));
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

        VkApplicationInfo vkApplInfo = {};
                //memSet(vkApplInfo, 0,VkApplicationInfo.SIZEOF);
                
                vkApplInfo.sType=VK_STRUCTURE_TYPE_APPLICATION_INFO;
				 vkApplInfo.pNext=nullptr;
                 vkApplInfo.pApplicationName="VKMod";
                 vkApplInfo.applicationVersion=VK_MAKE_VERSION(1, 0, 0);
                 vkApplInfo.pEngineName="No Engine";
                vkApplInfo .engineVersion=VK_MAKE_VERSION(1, 0, 0);
                 
                 vkApplInfo.apiVersion=VK_API_VERSION_1_2;
                 
		
//        MemSysm.Memsys2.free(a);
        // MemSysm.Memsys2.free(vkApplInfo);
        //nmemFree(vkApplInfo);

		// uint32_t glfwExtensionCount = 0;
		// const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
         
         VkInstanceCreateInfo InstCreateInfo={};
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
        VkWin32SurfaceCreateInfoKHR createSurfaceInfo={};
        createSurfaceInfo.sType=VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createSurfaceInfo.hwnd= glfwGetWin32Window(const_cast<GLFWwindow*>(window));
        createSurfaceInfo.hinstance = GetModuleHandle(nullptr);
        createSurfaceInfo.pNext=nullptr;

        VkUtils2::checkCall(vkCreateWin32SurfaceKHR(vkInstance, &createSurfaceInfo, nullptr, const_cast<VkSurfaceKHR*>(&surface)));
        
        
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
    VkDebugUtilsMessengerEXT debugUtils={};
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
    VkPhysicalDevice ppPhysicalDevices[deviceCount];

    VkPhysicalDevice device;
    std::cout <<("Enumerate Physical Device") << "\n";
   checkCall(vkEnumeratePhysicalDevices(vkInstance, &deviceCount, ppPhysicalDevices));
     for(const VkPhysicalDevice& d : ppPhysicalDevices)
        {  
            std::cout <<("Check Device:") << d << "\n";
            if(isDeviceSuitable(d)) {
                std::cout <<("Device Suitable:") << d << "\n";
                physicalDevice = d;
                return;
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
    checkDeviceExtensionSupport(device);
    
    

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU; /*&&
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

 inline void  VkUtils2::checkDeviceExtensionSupport(VkPhysicalDevice device) {
     std::cout << "Verifying checkDeviceExtensionSupport" << "\n";
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);
         VkExtensionProperties availableExtensions[extensionCount]; //todo: May MEMory Leak
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions);
        std::cout << extensionCount<< "->Extensions"<<"\n";
        // delete[] &availableExtensions;
        // return requiredExtensions.;
    }


    inline void VkUtils2::createLogicalDevice() {
            std::cout <<("Creating Logical Device")<<"\n";
        
         uint32_t pQueueFamilyPropertyCount=0;
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &pQueueFamilyPropertyCount, nullptr);


            VkQueueFamilyProperties uniqueQueueFamilies[3] ;
            Queues::enumerateDetermineQueueFamilies(physicalDevice, pQueueFamilyPropertyCount, uniqueQueueFamilies);   
           
            VkDeviceQueueCreateInfo queueCreateInfos={};
            constexpr float priority = 1.0f;
             //uint32_t pIx = 0;
            // for(;pIx<queuea;pIx++)*/ {
                queueCreateInfos.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfos.queueFamilyIndex=graphicsFamily;
                queueCreateInfos.queueCount=uniqueQueueFamilies[0].queueCount;
                queueCreateInfos.pQueuePriorities=&priority;
                queueCreateInfos.flags=0;
                queueCreateInfos.pNext=nullptr;
            //}
            
            VkPhysicalDeviceVulkan12Features deviceVulkan12Features={};
                    deviceVulkan12Features.descriptorBindingPartiallyBound=true,
                    deviceVulkan12Features.imagelessFramebuffer=true;
                    deviceVulkan12Features.pNext=nullptr;
                    
         

            VkPhysicalDeviceFeatures deviceFeatures={};

            VkPhysicalDeviceFeatures2 deviceFeatures2={};
                    deviceFeatures2.sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
                    deviceFeatures2.pNext=&deviceVulkan12Features;
                    deviceFeatures2.features=deviceFeatures;



            //.fillModeNonSolid(true) //dneeded to adres valditaion errors when using VK_POLIGYON_MODE_LINE or POINT
            //.robustBufferAccess(true);
//                        .geometryShader(true);
//                        .pipelineStatisticsQuery(true)
//                        .alphaToOne(false);
            vkGetPhysicalDeviceFeatures2(physicalDevice, &deviceFeatures2);
            VkDeviceCreateInfo createInfo={};
                    createInfo.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                    createInfo.pNext=&deviceFeatures2;
                    createInfo.queueCreateInfoCount=1;
                    createInfo.pQueueCreateInfos=&queueCreateInfos;
                    createInfo.ppEnabledExtensionNames=(deviceExtensions.data());
                    createInfo.enabledExtensionCount=static_cast<uint32_t>(validationLayers.size());
                    createInfo.ppEnabledLayerNames=(validationLayers.data());


            // PointerBuffer value = asPointerBuffer(DEVICE_EXTENSIONS);
            // memPutLong(createInfo.address() + VkDeviceCreateInfo.PPENABLEDEXTENSIONNAMES, value.address0());
            // memPutInt(createInfo.address() + VkDeviceCreateInfo.ENABLEDEXTENSIONCOUNT, value.remaining());

            // if(ENABLE_VALIDATION_LAYERS) {
            //     createInfo.ppEnabledLayerNames(asPointerBuffer(VALIDATION_LAYERS));
            // }
            checkCall(vkCreateDevice(physicalDevice, &createInfo, nullptr, &device ));

              vkGetDeviceQueue(device, createInfo.pQueueCreateInfos->queueFamilyIndex, 0,  &GraphicsQueue);
       
    }

    //  static void setupQueues()
    // {

    //     nvkGetDeviceQueue(device, Queues.graphicsFamily, 0,MemSysm.address);
    //     Queues.graphicsQueue = new VkQueue(memGetLong(MemSysm.address), device);

    //     nvkGetDeviceQueue(device, Queues.presentFamily, 0,MemSysm.address);
    //     Queues.presentQueue = new VkQueue(memGetLong(MemSysm.address), device);

    // }

    inline const VkSurfaceFormatKHR VkUtils2::querySwapChainSupport(const VkPhysicalDevice device)
{

        checkCall(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &capabilities));

        uint32_t count;
       
        checkCall(vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &count, NULL));
        std::cout << "Found: " << count << " Formats -------|^>" << "\n";
        //VkSurfaceFormatKHR formats[count];
        VkSurfaceFormatKHR formats[count];
        if (count != 0) {
            //formats = new VkSurfaceFormatKHR[count];
            checkCall(vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &count, formats));
        }

        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &count, NULL);

        if (count != 0) {
            // presentModes = {};
            checkCall(vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &count, &presentModes));
        }
         for(const VkSurfaceFormatKHR &format: formats)
         {
              std::cout << format.format <<"->"<<format.colorSpace <<"\n";
         }
        for(const VkSurfaceFormatKHR &format: formats)
                {
                     std::cout <<"Trying: -->"<< format.format <<"->"<<format.colorSpace <<"\n";
                    if(format.format==VK_FORMAT_B8G8R8A8_UNORM  && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
                    {
                            return format;
                    }
                    
                }
                 throw std::runtime_error("No Valid SwapChain Format Found");
} 


//This is horribly Ported from Java so May Suffer.Incur Considerable Breakage




    inline void VkUtils2::createImageViews()
    {
        std::cout<< ("Creating Image Views") << "\n";

        
          VkImageViewCreateInfo createInfo={};
          createInfo.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

                createInfo.viewType=VK_IMAGE_VIEW_TYPE_2D;
                createInfo.format=swapChainImageFormat.format;

        createInfo.subresourceRange.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT;
                createInfo.subresourceRange.baseMipLevel=0;
                createInfo.subresourceRange.levelCount=1;
                createInfo.subresourceRange.baseArrayLayer=0;
                createInfo.subresourceRange.layerCount=1;
        
        
        checkCall(vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews)); //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!

        


    }
    