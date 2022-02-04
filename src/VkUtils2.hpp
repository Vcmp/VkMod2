#pragma once

#include "UniformBufferObject.hpp"
#include "ShaderSPIRVUtils.hpp"
#include "SwapChainSupportDetails.hpp"
#include "Texture.hpp"

#include "Pipeline.hpp"
#include "Queues.hpp"
#include "src/Queues.hpp"
#include <vulkan/vulkan_core.h>




// #include <stdint.h>

   



inline namespace VkUtils2
{
     static GLFWwindow* window;
    static GLFWmonitor* monitor;
    static VkInstance vkInstance;
    static const std::vector<const char*> getRequiredExtensions();static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT*, void*);
   
   static constexpr VkResult createDebugUtilsMessengerEXT(const VkInstance,  const VkDebugUtilsMessengerCreateInfoEXT*);
	 
    static constexpr bool isDeviceSuitable(VkPhysicalDevice);
    static void checkDeviceExtensionSupport(VkPhysicalDevice);

    static const VkSurfaceFormatKHR querySwapChainSupport(VkPhysicalDevice);
    inline namespace{
    typedef VkResult (VKAPI_PTR *PFN_vkCreateDebugUtilsMessengerEXT2)(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, const VkDebugUtilsMessengerEXT* pMessenger);
    }



	
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
    static void cleanup();
    // static void createSwapChain();
    //static void createImageViews();
    // static void createPipeLine();
    static void extracted() {
      VkUtils2::setupWindow();
      VkUtils2::createInstance();
      VkUtils2::setupDebugMessenger();
      VkUtils2::createSurface();
      VkUtils2::pickPhysicalDevice();
      VkUtils2::createLogicalDevice();
      SwapChainSupportDetails::createSwapChain();
      SwapChainSupportDetails::createImageViews();    
      createRenderPasses();
      UniformBufferObject::createDescriptorSetLayout();
      PipelineX::createGraphicsPipelineLayout();
      createCommandPool();
    //   Texture::createDepthResources();
      BuffersX::setupBuffers();
    //   BuffersX::createVertexBuffer();
    //   BuffersX::createStagingBuffer();
    //   BuffersX::createIndexBuffer();
      SwapChainSupportDetails::createFramebuffers();
      
    //   Texture::createDepthResources();
      UniformBufferObject::createUniformBuffers();
      
      UniformBufferObject::createDescriptorPool();
        UniformBufferObject::createDescriptorSets();
      PipelineX::createCommandBuffers();

    //    BuffersX::createVkEvents();
    
      // VkUtils2::createInstance;
    }
   

    
    

    

};

long permuteMat(long, long);








inline void VkUtils2::setupWindow()
{
		glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        // glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);
        // glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
        // glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR , GLFW_RELEASE_BEHAVIOR_NONE);


        window = glfwCreateWindow(width, height, "VKMod2", nullptr, nullptr);


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

        static constexpr VkValidationFeatureEnableEXT valdFeatures[] = {VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT, VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT, VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT};
        constexpr VkValidationFeaturesEXT extValidationFeatures = {
        .sType=VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
        // .enabledValidationFeatureCount= 3,
        // .pEnabledValidationFeatures=valdFeatures,
                // extValidationFeatures.pEnabledValidationFeatures=&a;
        };

        constexpr VkApplicationInfo vkApplInfo = {
                //memSet(vkApplInfo, 0,VkApplicationInfo.SIZEOF);
                
                .sType=VK_STRUCTURE_TYPE_APPLICATION_INFO,
				 .pNext=VK_NULL_HANDLE,
                 .pApplicationName="VKMod2",
                 .applicationVersion=VK_MAKE_VERSION(1, 2, 0),
                 .pEngineName="No Engine",
                 .engineVersion=VK_MAKE_VERSION(1, 2, 0),
                 
                 .apiVersion=VK_API_VERSION_1_2
        };
         VkInstanceCreateInfo InstCreateInfo={};
        InstCreateInfo.sType =VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        InstCreateInfo.pApplicationInfo=&vkApplInfo;
       auto extensions=getRequiredExtensions();
        InstCreateInfo.ppEnabledExtensionNames=extensions.data();
      

        InstCreateInfo.enabledExtensionCount=static_cast<uint32_t>(extensions.size());
        
        if constexpr(ENABLE_VALIDATION_LAYERS) {
           InstCreateInfo.ppEnabledLayerNames=(validationLayers.data());
           InstCreateInfo.enabledLayerCount=static_cast<uint32_t>(validationLayers.size());  
           InstCreateInfo.pNext=&extValidationFeatures;
        }
        else InstCreateInfo.enabledLayerCount=0;
        
        // PointerBuffer instancePtr = memPointerBuffer(MemSysm.address, 1);	
        // vkCreateInstance(InstCreateInfo, MemSysm.pAllocator, instancePtr);


        checkCall(vkCreateInstance(&InstCreateInfo, VK_NULL_HANDLE, &vkInstance));
        // getVersion();
    }

inline void VkUtils2::createSurface()
    {
        std::cout <<("Creating Surface") << "\n";
        VkWin32SurfaceCreateInfoKHR createSurfaceInfo={};
        createSurfaceInfo.sType=VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        createSurfaceInfo.hwnd= glfwGetWin32Window(const_cast<GLFWwindow*>(window));
        createSurfaceInfo.hinstance = GetModuleHandle(nullptr);
        createSurfaceInfo.pNext=VK_NULL_HANDLE;

        checkCall(vkCreateWin32SurfaceKHR(vkInstance, &createSurfaceInfo, nullptr, const_cast<VkSurfaceKHR*>(&Queues::surface)));
        
        
    }


    inline bool VkUtils2::checkValidationLayerSupport()
    {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        VkLayerProperties availableLayers[layerCount];
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);

        return false;
    }




inline const std::vector<const char*> VkUtils2::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions+glfwExtensionCount);
     if constexpr(ENABLE_VALIDATION_LAYERS)
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
        std::cerr << "validation layer: " << pCallbackData->pMessage << "\n\n";

        return VK_FALSE;
    }

inline void VkUtils2::setupDebugMessenger()
    {
        if constexpr(!ENABLE_VALIDATION_LAYERS) {
            return;
        }

        constexpr VkDebugUtilsMessengerCreateInfoEXT createInfo{
        .sType=VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
        .messageSeverity=VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
        .messageType= VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
        .pfnUserCallback=VkUtils2::debugCallback,
        .pUserData=VK_NULL_HANDLE,
};
        checkCall(createDebugUtilsMessengerEXT(vkInstance, &createInfo));
        //debugMessenger = pDebugMessenger[0];
    }
    
inline constexpr VkResult VkUtils2::createDebugUtilsMessengerEXT(const VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo) 
{
    constexpr VkDebugUtilsMessengerEXT debugUtils={};
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT2) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != VK_NULL_HANDLE) {
        return func(instance, pCreateInfo, VK_NULL_HANDLE, &debugUtils);
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

    // VkPhysicalDevice device;
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
inline constexpr bool VkUtils2::isDeviceSuitable(const VkPhysicalDevice device)
 {

      VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
    checkDeviceExtensionSupport(device);
    
    

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU; /*&&
           deviceFeatures.geometryShader;*/

}

 inline void  VkUtils2::checkDeviceExtensionSupport(VkPhysicalDevice device) {
     std::cout << "Verifying checkDeviceExtensionSupport" << "\n";
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, VK_NULL_HANDLE, &extensionCount, VK_NULL_HANDLE);
         VkExtensionProperties availableExtensions[extensionCount]; //todo: May MEMory Leak
        vkEnumerateDeviceExtensionProperties(device, VK_NULL_HANDLE, &extensionCount, availableExtensions);
        std::cout << extensionCount<< "->Extensions"<<"\n";
        // delete[] &availableExtensions;
        // return requiredExtensions.;
    }


    inline void VkUtils2::createLogicalDevice() {
            std::cout <<("Creating Logical Device")<<"\n";
        
         uint32_t pQueueFamilyPropertyCount=5;
            // vkGetPhysicalDeviceQueueFamilyProperties(Queues::physicalDevice, &pQueueFamilyPropertyCount, VK_NULL_HANDLE);


            VkQueueFamilyProperties uniqueQueueFamilies[pQueueFamilyPropertyCount] ;
            vkGetPhysicalDeviceQueueFamilyProperties(Queues::physicalDevice, &pQueueFamilyPropertyCount, uniqueQueueFamilies);

            uint32_t i = 0;
           //todo: Likley/Prop won;t work with AMD properly 
            for (VkQueueFamilyProperties& uniqueQueue:uniqueQueueFamilies) {
                std::cout <<(uniqueQueue.queueCount)<< "\n";
                if ((uniqueQueue.queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
                    Queues::graphicsFamily = i;
                }
                VkBool32 presentSupport = false;
                vkGetPhysicalDeviceSurfaceSupportKHR(Queues::physicalDevice, i, Queues::surface, &presentSupport);
                 if (uniqueQueue.queueFlags & VK_QUEUE_TRANSFER_BIT && !presentSupport && uniqueQueue.queueFlags & 0x00000020) {
                    Queues::presentFamily = i;
                }
                if (Queues::presentFamily != NULL&& Queues::graphicsFamily!= NULL)
                    break;
            
                i++;
            }
           std::cout <<"Using: "<< graphicsFamily <<"-->"<< presentFamily << "\n";
            
            constexpr float priority = 1.0f;
             uint32_t pIx = 0;
         
         VkDeviceQueueCreateInfo GQ{};
            
               GQ.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
               GQ.queueFamilyIndex=Queues::graphicsFamily;
               GQ.queueCount=1;
               GQ.pQueuePriorities=&priority;
               GQ.flags=0;
               GQ.pNext=VK_NULL_HANDLE;
               
        VkDeviceQueueCreateInfo PQ{};
            
               PQ.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
               PQ.queueFamilyIndex=Queues::presentFamily;
               PQ.queueCount=1;
               PQ.pQueuePriorities=&priority;
               PQ.flags=0;
               PQ.pNext=VK_NULL_HANDLE;
              
            VkDeviceQueueCreateInfo queueCreateInfos[2]={GQ, PQ};
            
            static   VkPhysicalDeviceVulkan12Features deviceVulkan12Features={
                    .sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
                    .pNext=VK_NULL_HANDLE,
                    .descriptorBindingPartiallyBound=true,
                    .imagelessFramebuffer=true,
                    
         };

           static constexpr VkPhysicalDeviceFeatures deviceFeatures={};

            VkPhysicalDeviceFeatures2 deviceFeatures2={
                    .sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
                    .pNext=&deviceVulkan12Features,
                    .features=deviceFeatures
            };


            //.fillModeNonSolid(true) //dneeded to adres valditaion errors when using VK_POLIGYON_MODE_LINE or POINT
            //.robustBufferAccess(true);
//                        .geometryShader(true);
//                        .pipelineStatisticsQuery(true)
//                        .alphaToOne(false);
           vkGetPhysicalDeviceFeatures2(Queues::physicalDevice, &deviceFeatures2);
            // vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
            VkDeviceCreateInfo createInfo={};
                    createInfo.sType=VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                    createInfo.pNext=&deviceFeatures2;
                    createInfo.queueCreateInfoCount=2;
                    createInfo.pQueueCreateInfos=queueCreateInfos;
                    createInfo.ppEnabledExtensionNames=(deviceExtensions);
                    createInfo.enabledExtensionCount=static_cast<uint32_t>(validationLayers.size());
                    // createInfo.ppEnabledLayerNames=(validationLayers.data());
                    createInfo.pEnabledFeatures=nullptr;


            if constexpr(ENABLE_VALIDATION_LAYERS) {
                createInfo.ppEnabledLayerNames=validationLayers.data();
            }
            checkCall(vkCreateDevice(Queues::physicalDevice, &createInfo, VK_NULL_HANDLE, &device ));

              vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[0].queueFamilyIndex, 0,  &Queues::GraphicsQueue);
              vkGetDeviceQueue(device, createInfo.pQueueCreateInfos[1].queueFamilyIndex, 0,  &Queues::PresentQueue);
       
    }


 void VkUtils2::cleanup()
    {
        vkDeviceWaitIdle(device);
        vkDestroyCommandPool(device, (VkCommandPool)Queues::commandPool, nullptr);
         for (auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }
        // vkDestroyPipeline(device, PipelineX::graphicsPipeline, nullptr);
        // vkDestroyPipelineLayout(device, PipelineX::vkLayout, nullptr);

        vkDestroyBuffer(device, vertexBuffer, nullptr);
        vkFreeMemory(device, vertexBufferMemory, nullptr);
    }