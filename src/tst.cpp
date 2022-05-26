#include "Vks.tpp"
#include <cstdint>
#include <vector>
#include <iostream>
#include <GLFW/glfw3native.h>
#include <vulkan/vulkan_core.h>

inline namespace {
static constexpr char const * deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;
}

VkDevice VkInit::tst()
{
    return this->device;
}

GLFWwindow* VkInit::init()
{

  RegisterClassA(&AHack);

  GLFWwindow* window;
  volkInitialize();
  glfwInit();
  glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
  glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );
  glfwWindowHint( GLFW_API_UNAVAILABLE, GLFW_TRUE );
  glfwWindowHint( GLFW_CONTEXT_RELEASE_BEHAVIOR, GLFW_RELEASE_BEHAVIOR_NONE );
  glfwWindowHint( GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API );
  window = glfwCreateWindow( width, height, "VKMod2", nullptr, nullptr );


  glfwSetWindowShouldClose(  window , false );
  std::cout << "OK!" << "\n";
  return window;
};




inline const std::vector<const char *> getRequiredExtensions()
{
  uint32_t                  glfwExtensionCount = 0;
  const char **             glfwExtensions     = glfwGetRequiredInstanceExtensions( &glfwExtensionCount );
  std::vector<const char *> extensions( glfwExtensions, glfwExtensions + glfwExtensionCount );
  if constexpr ( ENABLE_VALIDATION_LAYERS )
  {
    extensions.push_back( VK_EXT_DEBUG_UTILS_EXTENSION_NAME );
  }
  return extensions;
}


VkInstance VkInit::createInstance()
{
  VkInstance vki;
  std::cout <<  "Creating Instance"  << "\n";

  static constexpr auto valdFeatures       = { VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
                                                                   VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
                                                                   VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT };
  constexpr VkValidationFeaturesEXT             extValidationFeatures = {
                .sType                         = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
                .enabledValidationFeatureCount = valdFeatures.size(),
                .pEnabledValidationFeatures    = valdFeatures.begin(),
  };
 
  constexpr VkApplicationInfo vkApplInfo 
  {
    .sType{VK_STRUCTURE_TYPE_APPLICATION_INFO},
    .pNext{VK_NULL_HANDLE},
    .pApplicationName{"VKMod2"},
    .applicationVersion{VK_MAKE_VERSION( 1, 2, 0 )},
    .pEngineName{"No Engine"},
    .engineVersion{VK_MAKE_VERSION( 1, 2, 0 )},
    .apiVersion{VK_API_VERSION_1_2}
  };
  const auto  extensions                        = getRequiredExtensions();
  const VkInstanceCreateInfo InstCreateInfo 
  {
    .sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pNext               =  ENABLE_VALIDATION_LAYERS ? &extValidationFeatures : nullptr,
    .pApplicationInfo        = &vkApplInfo,
   .enabledLayerCount   =  ENABLE_VALIDATION_LAYERS ? 1 : 0,
      .ppEnabledLayerNames = ENABLE_VALIDATION_LAYERS ? &validationLayers : nullptr,
    .enabledExtensionCount = static_cast<uint32_t>(( extensions.size() )),
    .ppEnabledExtensionNames = extensions.data(),

  };

  
 
  vkCreateInstance(&InstCreateInfo, nullptr, &vki);
  volkLoadInstanceOnly( vki );
  return vki;
 }



 VkPhysicalDevice VkInit::doPhysicalDevice()
 {
    std::cout << ( "Picking Physical Device" ) << "\n";
  uint32_t deviceCount;
  vkEnumeratePhysicalDevices( instance, &deviceCount, nullptr ) ;

  // if constexpr(ENABLE_VALIDATION_LAYERS)
  // {
  //   setupDebugMessenger();
  // }
 
  // if ( deviceCount == 0 )
  //   std::runtime_error( "Failed to find GPUs with Vulkan support" );
   std::vector<VkPhysicalDevice> ppPhysicalDevicesdeviceCount(deviceCount);

  std::cout <<  "Enumerate Physical Device"  << "\n";
  vkEnumeratePhysicalDevices( instance, &deviceCount, ppPhysicalDevicesdeviceCount.data() );
  return ppPhysicalDevicesdeviceCount.at(0);
   //BuffersX::memProperties=vkds.memProperties;
  //  return physdeviceevice;
 }

VkSurfaceKHR VkInit::createSurface()
{
    VkSurfaceKHR surface;
  std::cout << ( "Creating Surface" ) << "\n";
  VkWin32SurfaceCreateInfoKHR createSurfaceInfo = {};
  createSurfaceInfo.sType                       = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  createSurfaceInfo.hwnd                        = glfwGetWin32Window( window  );
  createSurfaceInfo.hinstance                   = GetModuleHandle( nullptr );
  createSurfaceInfo.pNext                       = VK_NULL_HANDLE;

  vkCreateWin32SurfaceKHR( instance, &createSurfaceInfo, nullptr, &surface);
  return surface;
}

VkDevice VkInit::doDevice()
{
   std::cout << "Creating Logical Device"  << "\n";
uint32_t graphicsFamily;
uint32_t transferFamily;
  uint32_t pQueueFamilyPropertyCount;
  vkGetPhysicalDeviceQueueFamilyProperties( physdevice, &pQueueFamilyPropertyCount, VK_NULL_HANDLE );

  VkQueueFamilyProperties uniqueQueueFamilies[pQueueFamilyPropertyCount];
  vkGetPhysicalDeviceQueueFamilyProperties( physdevice, &pQueueFamilyPropertyCount, uniqueQueueFamilies );

  uint32_t i = 0;
  // todo: Likley/Prop won't work with AMD properly and/or specific GPUs with differing Queue Family layouts
  for ( VkQueueFamilyProperties const & uniqueQueue : uniqueQueueFamilies )
  {
    std::cout << ( uniqueQueue.queueCount ) << "\n";
    if ( ( uniqueQueue.queueFlags & VK_QUEUE_GRAPHICS_BIT ) )
    {
      graphicsFamily = i;
      continue;
    }
    // Check that Video Tranfer Queues are not Accidentally selected if the Vulkan beta Drivers from Nvidia are used
    // VkBool32 presentSupport = vkGetPhysicalDeviceWin32PresentationSupportKHR(physdevice, i);
    
    if ( uniqueQueue.queueFlags & VK_QUEUE_TRANSFER_BIT && !vkGetPhysicalDeviceWin32PresentationSupportKHR(physdevice, i) )
    {
      transferFamily = i;
      break;
    }

    i++;
  }
  std::cout << "Using: " << graphicsFamily << "-->" << transferFamily << "\n";

  constexpr float priority = 1.0f;
  uint32_t        pIx      = 0;

  VkDeviceQueueCreateInfo GQ{};

  GQ.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  GQ.queueFamilyIndex = graphicsFamily;
  GQ.queueCount       = 1;
  GQ.pQueuePriorities = &priority;
  GQ.flags            = 0;
  GQ.pNext            = VK_NULL_HANDLE;

  VkDeviceQueueCreateInfo PQ{};

  PQ.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  PQ.queueFamilyIndex = transferFamily;
  PQ.queueCount       = 1;
  PQ.pQueuePriorities = &priority;
  PQ.flags            = 0;
  PQ.pNext            = VK_NULL_HANDLE;
  
  // VkDeviceQueueCreateInfo PRQ{};

  // PQ.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  // PQ.queueFamilyIndex = 0;
  // PQ.queueCount       = 1;
  // PQ.pQueuePriorities = &priority;
  // PQ.flags            = 0;
  // PQ.pNext            = VK_NULL_HANDLE;

  const auto queueCreateInfos = { GQ, PQ };

  static VkPhysicalDeviceVulkan13Features vk13F
  {
    .sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
    .pNext=VK_NULL_HANDLE
  };


  static VkPhysicalDeviceVulkan12Features deviceVulkan12Features = {
    .sType                           = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
    .pNext                           = &vk13F,
    .descriptorBindingPartiallyBound = true,
    .imagelessFramebuffer            = true,

  };

  static constexpr VkPhysicalDeviceFeatures deviceFeatures = {};

  VkPhysicalDeviceFeatures2 deviceFeatures2 = { .sType    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
                                                .pNext    = &deviceVulkan12Features,
                                                /* .features = deviceFeatures */ };


  vkGetPhysicalDeviceFeatures2( physdevice, &deviceFeatures2 );


  const VkDeviceCreateInfo createInfo      = {
  .sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
  .pNext                   = &deviceFeatures2,
  .queueCreateInfoCount    = 2,
  .pQueueCreateInfos       = queueCreateInfos.begin(),
  .ppEnabledLayerNames =   ENABLE_VALIDATION_LAYERS  ? &validationLayers : nullptr,
  .enabledExtensionCount   = 1,
  .ppEnabledExtensionNames = ( &deviceExtensions ),
  .pEnabledFeatures = nullptr,
  };
  VkDevice device;
  if ( !deviceVulkan12Features.imagelessFramebuffer )
  {
     std::runtime_error( "Failed Enumeration!" );
  }
  
  
  vkCreateDevice( physdevice, &createInfo, VK_NULL_HANDLE, &device ) ;
  volkLoadDevice( device );

  vkGetDeviceQueue(device, 0, 0, &GraphicsQueue );
  // vkGetDeviceQueue(device, 0, 0, &PresentQueue );
  vkGetDeviceQueue(device, 1, 0, &TransferQueue );
  // Queues::device=device;
  return device;
}