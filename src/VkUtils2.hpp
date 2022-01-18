#pragma once

#include "UniformBufferObject.hpp"
#include "ShaderSPIRVUtils.hpp"
#include "SwapChainSupportDetails.hpp"
#include "Texture.hpp"

#include "Pipeline.hpp"

 #include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

   



inline namespace VkUtils2
{
     static GLFWwindow* window;
    static GLFWmonitor* monitor;
    static VkInstance vkInstance;
    static std::vector<const char*> getRequiredExtensions();static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT, VkDebugUtilsMessageTypeFlagsEXT, const VkDebugUtilsMessengerCallbackDataEXT*, void*);
   
   static VkResult createDebugUtilsMessengerEXT(VkInstance,  const VkDebugUtilsMessengerCreateInfoEXT*);
	 
    static bool isDeviceSuitable(VkPhysicalDevice);
    static void checkDeviceExtensionSupport(VkPhysicalDevice);

    static const VkSurfaceFormatKHR querySwapChainSupport(VkPhysicalDevice);
    



	
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
    // static void createSwapChain();
    static void createImageViews();
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
      Pipeline::createRenderPasses();
    //   UniformBufferObject::createDescriptorSetLayout();
      Pipeline::createGraphicsPipelineLayout();
    //   Pipeline::createCommandPool();
    //   Texture::createDepthResources();
    
      // VkUtils2::createInstance;
    }
   

    
    

    

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
				 vkApplInfo.pNext=VK_NULL_HANDLE;
                 vkApplInfo.pApplicationName="VKMod2";
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
           InstCreateInfo.ppEnabledLayerNames=(validationLayers.data());
           InstCreateInfo.enabledLayerCount=static_cast<uint32_t>(validationLayers.size());
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
        std::cerr << "validation layer: " << pCallbackData->pMessage << "\n\n";

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
        createInfo.pUserData=VK_NULL_HANDLE;

        checkCall(createDebugUtilsMessengerEXT(vkInstance, &createInfo));
        //debugMessenger = pDebugMessenger[0];
    }
    
inline VkResult VkUtils2::createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo) 
{
    VkDebugUtilsMessengerEXT debugUtils={};
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
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
        vkEnumerateDeviceExtensionProperties(device, VK_NULL_HANDLE, &extensionCount, VK_NULL_HANDLE);
         VkExtensionProperties availableExtensions[extensionCount]; //todo: May MEMory Leak
        vkEnumerateDeviceExtensionProperties(device, VK_NULL_HANDLE, &extensionCount, availableExtensions);
        std::cout << extensionCount<< "->Extensions"<<"\n";
        // delete[] &availableExtensions;
        // return requiredExtensions.;
    }


    inline void VkUtils2::createLogicalDevice() {
            std::cout <<("Creating Logical Device")<<"\n";
        
         uint32_t pQueueFamilyPropertyCount=0;
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &pQueueFamilyPropertyCount, VK_NULL_HANDLE);


            VkQueueFamilyProperties uniqueQueueFamilies[3] ;
            Queues::enumerateDetermineQueueFamilies(pQueueFamilyPropertyCount, uniqueQueueFamilies);   
           
            VkDeviceQueueCreateInfo queueCreateInfos={};
            constexpr float priority = 1.0f;
             //uint32_t pIx = 0;
            // for(;pIx<queuea;pIx++)*/ {
                queueCreateInfos.sType=VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfos.queueFamilyIndex=graphicsFamily;
                queueCreateInfos.queueCount=uniqueQueueFamilies[0].queueCount;
                queueCreateInfos.pQueuePriorities=&priority;
                queueCreateInfos.flags=0;
                queueCreateInfos.pNext=VK_NULL_HANDLE;
            //}
            
            VkPhysicalDeviceVulkan12Features deviceVulkan12Features={};
                    deviceVulkan12Features.descriptorBindingPartiallyBound=true,
                    deviceVulkan12Features.imagelessFramebuffer=true;
                    deviceVulkan12Features.pNext=VK_NULL_HANDLE;
                    
         

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
                    createInfo.ppEnabledExtensionNames=(deviceExtensions);
                    createInfo.enabledExtensionCount=static_cast<uint32_t>(validationLayers.size());
                    createInfo.ppEnabledLayerNames=(validationLayers.data());


            // PointerBuffer value = asPointerBuffer(DEVICE_EXTENSIONS);
            // memPutLong(createInfo.address() + VkDeviceCreateInfo.PPENABLEDEXTENSIONNAMES, value.address0());
            // memPutInt(createInfo.address() + VkDeviceCreateInfo.ENABLEDEXTENSIONCOUNT, value.remaining());

            // if(ENABLE_VALIDATION_LAYERS) {
            //     createInfo.ppEnabledLayerNames(asPointerBuffer(VALIDATION_LAYERS));
            // }
            checkCall(vkCreateDevice(physicalDevice, &createInfo, VK_NULL_HANDLE, &device ));

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

        checkCall(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, Queues::surface, &SwapChainSupportDetails::capabilities));

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
            checkCall(vkGetPhysicalDeviceSurfacePresentModesKHR(device, Queues::surface, &count, &SwapChainSupportDetails::presentModes));
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
                 attachments.format=SwapChainSupportDetails::swapChainImageFormat.format;
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
                vkRenderPassCreateInfo1.pNext=VK_NULL_HANDLE ;


        clPPPI(&vkRenderPassCreateInfo1, "vkCreateRenderPass", &SwapChainSupportDetails::renderPass);
        
       

    }

    

     inline VkShaderModule createShaderModule(char& spirvCode, VkShaderModuleCreateInfo* pShaderCreateInfo) {

        {
            VkShaderModule a = nullptr;
            vkCreateShaderModule(device, pShaderCreateInfo, nullptr, &a);
            return a;
        }
    }

   