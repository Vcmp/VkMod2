#pragma once
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

#include <iostream>
#include <vector>
#include <immintrin.h>
#include <avx2intrin.h>

#include "SwapChainSupportDetails.hpp"
#include "Queues.hpp"
    
#include "Pipeline.hpp"
#include "Texture.hpp"
#include "ShaderSPIRVUtils.hpp"
#include "Buffers.hpp"
#include "UniformBufferObject.hpp"


 const static std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const static std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

    constexpr bool debug=true;
    constexpr bool checks=true;
    constexpr bool ENABLE_VALIDATION_LAYERS=debug;
    

using Queues::device;
using Queues::physicalDevice;


inline namespace
{
    namespace {
    typedef const VkResult (__vectorcall *callPPPPI) (VkDevice device, const void* pStrct, const VkAllocationCallbacks* pAllocator, const void* hndl/*, const PFN_vkVoidFunction* pHndl*/);

typedef VkResult  (VKAPI_CALL *vkk)(void);

static GLFWwindow* window;
static GLFWmonitor* monitor;
static VkInstance vkInstance;
const static inline VkResult clPPPI(const void* pStrct,  const char* a, const void *object)
{
    //vkGetDeviceProcAddr()
    // auto xx=PFN_vkVoidFunction(swapChain);
    const callPPPPI x =reinterpret_cast<callPPPPI>(vkGetDeviceProcAddr(Queues::device, a));
    std::cout << &x << "\n";
    std::cout << &pStrct << &object<<&a<<"\n";
    std::cout << &a<<"\n";
    std::cout << &object<<"\n";
    const VkResult VkR =x(Queues::device, pStrct, nullptr, object);
    return VkR;
    //  callPPPPI(device, pStrct, nullptr, a)
};
    }
static VkSwapchainKHR swapChain;
static VkImage pSwapchainImages[3];
const static struct VkUtils2
{
	
//    private static final long[] pDebugMessenger = new long[1];
    //    X(),
    //    Y
    //    KEY(1)
	

    
         static void setupWindow();

	 static void createInstance();
	 static void createSurface();
	static bool checkValidationLayerSupport();
	
    
    static void setupDebugMessenger();

    static void pickPhysicalDevice();
    static void createLogicalDevice();
    static void createSwapChain();
    static void createImageViews();
    static void createPipeLine();
    static void extracted() {
      VkUtils2::setupWindow();
      VkUtils2::createInstance();
      VkUtils2::setupDebugMessenger();
      VkUtils2::createSurface();
      VkUtils2::pickPhysicalDevice();
      VkUtils2::createLogicalDevice();
      VkUtils2::createSwapChain();
      VkUtils2::createImageViews();
      Pipeline::createRenderPasses();
      Pipeline::createGraphicsPipelineLayout();
    
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

    
};
};

long permuteMat(long, long);






// namespace VkU2 {
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
// };


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

        VkUtils2::checkCall(vkCreateWin32SurfaceKHR(vkInstance, &createSurfaceInfo, nullptr, const_cast<VkSurfaceKHR*>(&Queues::surface)));
        
        
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
                Queues::physicalDevice = d;
                return;
            }
             std::cout <<("Device Not Suitable:") << d << "\n";
           
        }
        if (Queues::physicalDevice == VK_NULL_HANDLE) {
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
            vkGetPhysicalDeviceQueueFamilyProperties(Queues::physicalDevice, &pQueueFamilyPropertyCount, nullptr);


            VkQueueFamilyProperties uniqueQueueFamilies[3] ;
            Queues::enumerateDetermineQueueFamilies(Queues::physicalDevice, pQueueFamilyPropertyCount, uniqueQueueFamilies);   
           
            VkDeviceQueueCreateInfo queueCreateInfos={};
            constexpr float priority = 1.0f;
             //uint32_t pIx = 0;
            // for(;pIx<queuea;pIx++)*/ {
                queueCreateInfos.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfos.queueFamilyIndex=Queues::graphicsFamily;
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
            vkGetPhysicalDeviceFeatures2(Queues::physicalDevice, &deviceFeatures2);
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
            checkCall(vkCreateDevice(Queues::physicalDevice, &createInfo, nullptr, &Queues::device ));

              vkGetDeviceQueue(Queues::device, createInfo.pQueueCreateInfos->queueFamilyIndex, 0,  &Queues::GraphicsQueue);
       
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

        checkCall(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, Queues::surface, &capabilities));

        uint32_t count;
       
        checkCall(vkGetPhysicalDeviceSurfaceFormatsKHR(device, Queues::surface, &count, NULL));
        std::cout << "Found: " << count << " Formats -------|^>" << "\n";
        //VkSurfaceFormatKHR formats[count];
        VkSurfaceFormatKHR formats[count];
        if (count != 0) {
            //formats = new VkSurfaceFormatKHR[count];
            checkCall(vkGetPhysicalDeviceSurfaceFormatsKHR(device, Queues::surface, &count, formats));
        }

        vkGetPhysicalDeviceSurfacePresentModesKHR(device, Queues::surface, &count, NULL);

        if (count != 0) {
            // presentModes = {};
            checkCall(vkGetPhysicalDeviceSurfacePresentModesKHR(device, Queues::surface, &count, &presentModes));
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
                createInfo.image=*pSwapchainImages;

        createInfo.subresourceRange.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT;
                createInfo.subresourceRange.baseMipLevel=0;
                createInfo.subresourceRange.levelCount=1;
                createInfo.subresourceRange.baseArrayLayer=0;
                createInfo.subresourceRange.layerCount=1;
        
        
        checkCall(clPPPI(&createInfo, "vkCreateImageView", &swapChainImageViews)); //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!

        


    }
inline VkFormat Texture::findDepthFormat()
    {
        VkFormat formatCandidates[3]={VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT};
        VkFormatProperties props;

        for (VkFormat format : formatCandidates) {

           
            vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

            const int i2 = props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;
            if (i2 == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT/* && VK10.VK_IMAGE_TILING_OPTIMAL == VK_IMAGE_TILING_OPTIMAL*/) {
                return format;
            }
        }

        std::runtime_error("failed to find supported format!");
    }

    inline void Pipeline::createRenderPasses()
    {
         int capacity = 2;
        int abs;

        // VkAttachmentReference VkRenderPasses[capacity];
        // VkRenderPassCreateInfo VkRenderPassesAttach[capacity];
//            if (!depthEnabled)
//            {
//                abs=VK_SUBPASS_EXTERNAL;
//            }
        //else
        abs = VK_SUBPASS_CONTENTS_INLINE;
VkAttachmentReference attachmentsRefs = {};
                attachmentsRefs.attachment=0,
                attachmentsRefs.layout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

       VkAttachmentDescription attachments = {};
                 attachments.format=swapChainImageFormat.format;
                 attachments.samples=VK_SAMPLE_COUNT_1_BIT;
                 attachments.loadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                 attachments.storeOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
                 attachments.stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                 attachments.stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
                 attachments.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
                 attachments.finalLayout=VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
     


        VkAttachmentDescription depthAttachment ={};
                attachments.format=Texture::findDepthFormat();
                attachments.samples=VK_SAMPLE_COUNT_1_BIT;
                attachments.loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR;
                attachments.storeOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
                attachments.stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                attachments.stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
                attachments.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
                attachments.finalLayout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


        VkAttachmentReference depthAttachmentRef ={};
                attachmentsRefs.attachment=1;
                attachmentsRefs.layout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;   
        
        VkSubpassDescription vkSubpassDescriptions{};
                vkSubpassDescriptions.pipelineBindPoint=VK_PIPELINE_BIND_POINT_GRAPHICS;
                vkSubpassDescriptions.colorAttachmentCount=0;
                vkSubpassDescriptions.pColorAttachments=&attachmentsRefs;
                vkSubpassDescriptions.pDepthStencilAttachment=&depthAttachmentRef;

const VkAttachmentDescription attDesc[]={attachments, depthAttachment};

        VkSubpassDependency dependency = {};
                dependency.srcSubpass=abs;
                dependency.dstSubpass=0;
                dependency.srcStageMask=VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
                dependency.srcAccessMask=VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
                dependency.dstStageMask=VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
                dependency.dstAccessMask=VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
                dependency.dependencyFlags=VK_DEPENDENCY_BY_REGION_BIT;


        VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {};
                vkRenderPassCreateInfo1.sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
                vkRenderPassCreateInfo1.pAttachments=attDesc;
                vkRenderPassCreateInfo1.attachmentCount=2;
                vkRenderPassCreateInfo1.pSubpasses=&vkSubpassDescriptions;
                vkRenderPassCreateInfo1.subpassCount=1;
                vkRenderPassCreateInfo1.pDependencies=&dependency;
                vkRenderPassCreateInfo1.dependencyCount=2;
                vkRenderPassCreateInfo1.pNext=nullptr;


        clPPPI(&vkRenderPassCreateInfo1, "vkCreateRenderPass", &renderPass);
        
       

    }

    inline void Pipeline::createGraphicsPipelineLayout()
    {
        //Thankfully Dont; need to worry about compiling the Shader Files AnyMore due to
        std::cout<<("Setting up PipeLine")<< "\n";

        const VkShaderModule vertShaderModule = ShaderSPIRVUtils::compileShaderFile(device, "shaders/21_shader_ubo.vert.spv");
        const VkShaderModule fragShaderModule = ShaderSPIRVUtils::compileShaderFile(device, "shaders/21_shader_ubo.frag.spv");

        // constexpr char entryPoint[]={"main"};

        VkPipelineShaderStageCreateInfo vertexStage={
            .sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, 
            .pNext=nullptr,
//                    .sType(VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO)
                .stage=VK_SHADER_STAGE_VERTEX_BIT,
                .module=vertShaderModule,
                .pName="main"
                
        };

        VkPipelineShaderStageCreateInfo fragStage={
                .sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                .pNext=nullptr,
                .stage=VK_SHADER_STAGE_FRAGMENT_BIT,
                .module=fragShaderModule,
                .pName="main"
        };

        VkPipelineShaderStageCreateInfo shaderStages[] = {vertexStage, fragStage};

        VkVertexInputBindingDescription a {
                        .binding=0,
        //                    .stride(vertices.length/2)
        //                    .stride(vertices.length/VERT_SIZE+1)
                        .stride=32,
                        .inputRate=VK_VERTEX_INPUT_RATE_VERTEX
                };

        VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo={};
                   vkPipelineVertexInputStateCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
                vkPipelineVertexInputStateCreateInfo.pVertexBindingDescriptions=&a;
        // vkPipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions= getAttributeDescriptions();
        // VkPipelineVertexInputStateCreateInfo.nvertexAttributeDescriptionCount=3;


        VkPipelineInputAssemblyStateCreateInfo inputAssembly={};
                   inputAssembly.sType=VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
                inputAssembly.topology=VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
                inputAssembly.primitiveRestartEnable=VK_FALSE;
        /*todo: Fixed Viewport COnstruction/Initilaistaion?Configration: ([Had use wrong Function?method Veowpprt/Stagong function Calls/cfongurations e.g.])
         *(had also used vkViewport instead of VkViewport of Type Buffer which is the atcual correct Obejct/Stage/Steup.veiwport conponnat.consituent
         *
         * (CorretcioN: had actually also used viewportBuffer and not vkViewport(Of type VkViewport.Bufferand not VkViewPort....) in VkPipelineViewportStateCreateInfo as well)
         */
        VkViewport vkViewport{
                .x=0.0F,
                .y=0.0F,
                .width=static_cast<float>(swapChainExtent.width),
                .height=static_cast<float>(swapChainExtent.height),
                .minDepth=0.0F,
                .maxDepth=1.0F
        };

        VkRect2D scissor{
//                    .offset(vkOffset2D ->vkViewport.y()) //todo: not sure if correct Offset
                .offset={0, 0},
                .extent=swapChainExtent
        };

        VkPipelineViewportStateCreateInfo vkViewPortState={};
                   vkViewPortState.sType=VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
                vkViewPortState.viewportCount=1;
                vkViewPortState.pViewports=&vkViewport;
//                    .pScissors(vkrect2DBuffer);
                vkViewPortState.scissorCount=1;
                vkViewPortState.pScissors=&scissor;


        VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization={};
                   VkPipeLineRasterization.sType=VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
                VkPipeLineRasterization.depthClampEnable=VK_FALSE;
                VkPipeLineRasterization.rasterizerDiscardEnable=VK_FALSE;
                VkPipeLineRasterization.polygonMode=VK_POLYGON_MODE_FILL;
                VkPipeLineRasterization.lineWidth=1.0f;
//                   .cullMode(VK_CULL_MODE_BACK_BIT)
//                   .frontFace(VK_FRONT_FACE_COUNTER_CLOCKWISE)
                VkPipeLineRasterization.depthBiasEnable=VK_FALSE;

        //todo: actuall need multismapling to Compleet.Initialsie.Construct.Substanciate the renderPipeline corretcly even if Antialsing /AF/MMs are not neeeded......
        VkPipelineMultisampleStateCreateInfo multisampling={};
                   multisampling.sType=VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
                multisampling.sampleShadingEnable=VK_FALSE;
                multisampling.rasterizationSamples=VK_SAMPLE_COUNT_1_BIT;
//                    .alphaToOneEnable(false)
//                    .alphaToCoverageEnable(false);


        VkPipelineDepthStencilStateCreateInfo depthStencil={};
                   depthStencil.sType=VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
                depthStencil.depthTestEnable=VK_TRUE;
                depthStencil.depthWriteEnable=VK_TRUE;
                depthStencil.depthCompareOp=VK_COMPARE_OP_LESS;
                depthStencil.depthBoundsTestEnable=VK_FALSE;
//                    .minDepthBounds(0) //Optional
//                    .maxDepthBounds(1) //Optional
                depthStencil.stencilTestEnable=VK_FALSE;


        VkPipelineColorBlendAttachmentState colorBlendAttachment={};
                colorBlendAttachment.colorWriteMask=VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
                //(Actually)Add blending?transparency to be suproted
                colorBlendAttachment.blendEnable=VK_TRUE;
                colorBlendAttachment.srcColorBlendFactor=VK_BLEND_FACTOR_SRC_ALPHA;
//                    .dstColorBlendFactor(VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA);
                colorBlendAttachment.dstColorBlendFactor=VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
//                    .colorBlendOp(VK_BLEND_OP_MAX)

//                    .srcAlphaBlendFactor(VK_BLEND_FACTOR_ONE)
//                    .dstAlphaBlendFactor(VK_BLEND_FACTOR_ZERO)
//                    .alphaBlendOp(VK_BLEND_OP_ADD);

        // float blendConstants[]={0.0f, 0.0f, 0.0f, 0.0f};
        VkPipelineColorBlendStateCreateInfo colorBlending={};
                   colorBlending.sType=VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
                colorBlending.logicOpEnable=VK_FALSE;
                colorBlending.logicOp=VK_LOGIC_OP_COPY;
                colorBlending.pAttachments=&colorBlendAttachment;
                colorBlending.blendConstants[0]=0.0f;
                colorBlending.blendConstants[1]=0.0f;
                colorBlending.blendConstants[2]=0.0f;
                colorBlending.blendConstants[3]=0.0f;
//            memFree(colorBlendAttachment);

        VkPushConstantRange vkPushConstantRange={};
                vkPushConstantRange.offset=0;
                vkPushConstantRange.size=16 * sizeof(float);
                vkPushConstantRange.stageFlags=VK_SHADER_STAGE_VERTEX_BIT;
        VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo;
                   vkPipelineLayoutCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                vkPipelineLayoutCreateInfo.pPushConstantRanges=&vkPushConstantRange;
                vkPipelineLayoutCreateInfo.pSetLayouts=&UniformBufferObject::descriptorSetLayout;
        //                    .sType(VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO)
       


        std::cout << ("using pipeLine with Length: ") << sizeof(swapChainImageViews);
        //nmemFree(vkPipelineLayoutCreateInfo1.address());
        vkCreatePipelineLayout(device, &vkPipelineLayoutCreateInfo, nullptr, &vkLayout);
        //MemSysm.Memsys2.doPointerAllocSafeX(vkPipelineLayoutCreateInfo, Buffers.capabilities.vkCreatePipelineLayout, Buffers.vkLayout);


        VkGraphicsPipelineCreateInfo pipelineInfo{
                .sType=VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                .pStages=shaderStages,
                .stageCount=2,
                .pVertexInputState=&vkPipelineVertexInputStateCreateInfo,
                .pInputAssemblyState=&inputAssembly,
                .pViewportState=&vkViewPortState,
                .pRasterizationState=&VkPipeLineRasterization,
                .pMultisampleState=&multisampling,
                .pDepthStencilState=&depthStencil,
                .pColorBlendState=&colorBlending,
//                    .pDynamicState(null)
                .layout=vkLayout,
                .renderPass=renderPass,
                .subpass=0,
//                    .basePipelineHandle(VK_NULL_HANDLE)
                .basePipelineIndex=-1
        };
       

        //Memsys2.free(entryPoint);

        vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline);
        // Buffers.graphicsPipeline = MemSysm.doPointerAlloc5L(device, pipelineInfo);

        vkDestroyShaderModule(device, vertShaderModule, nullptr);
        vkDestroyShaderModule(device, fragShaderModule, nullptr);

    }

     inline VkShaderModule createShaderModule(char& spirvCode, VkShaderModuleCreateInfo* pShaderCreateInfo) {

        {
            VkShaderModule a = nullptr;
            vkCreateShaderModule(device, pShaderCreateInfo, nullptr, &a);
            return a;
        }
    }

    inline void Pipeline::createCommandPool()
    {
        VkCommandPoolCreateInfo poolInfo={};
                poolInfo.queueFamilyIndex=graphicsFamily;
                poolInfo.flags=0;
        //Memsys2.free(poolInfo);
        vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
    }