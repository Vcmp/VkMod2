#pragma arguments

#include <volk.h>

struct VkDev// : VkPhysicalDeviceProperties
{
  //  uint32_t deviceCount;
  const VkPhysicalDevice pd;
  const VkDevice pds;
  const VkPhysicalDeviceProperties deviceProperties;
  const VkPhysicalDeviceMemoryProperties memProperties;
  const bool is=deviceProperties.deviceType==VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
    // const VkPhysicalDeviceLimits aa;
    explicit constexpr VkDev() : pd(pickPhysicalDevice()), /* deviceCount(devs()),  */deviceProperties(isDeviceSuitable()), pds(createLogicalDevice()), memProperties(findMemoryType())
    {
    //  Queues::physicalDevice=pd; 
     ;
    }
    // ~VkDev()= default;
    
    private:
     uint32_t devs();
     VkPhysicalDevice pickPhysicalDevice();
     VkPhysicalDeviceProperties isDeviceSuitable();
     VkDevice createLogicalDevice();
     VkPhysicalDeviceMemoryProperties findMemoryType();
} __attribute__((aligned(128)));

inline uint32_t VkDev::devs()
{
  std::cout << ( "Picking Physical Device" ) << "\n";
  uint32_t deviceCount;
  VkUtilsXBase::checkCall( vkEnumeratePhysicalDevices( VkUtils2::vkInstance, &deviceCount, nullptr ) );
  return deviceCount;
}
inline VkPhysicalDevice VkDev::pickPhysicalDevice()
{
  auto deviceCount=VkDev::devs();
  if ( deviceCount == 0 )
    std::runtime_error( "Failed to find GPUs with Vulkan support" );
   std::vector<VkPhysicalDevice> ppPhysicalDevicesdeviceCount(deviceCount);

  std::cout << ( "Enumerate Physical Device" ) << "\n";
  VkUtilsXBase::checkCall( vkEnumeratePhysicalDevices( VkUtils2::vkInstance, &deviceCount, ppPhysicalDevicesdeviceCount.data() ) );
  return ppPhysicalDevicesdeviceCount.at(0);
}
//   for ( auto i=0U; i< ppPhysicalDevicesdeviceCount.size(); i++ )
//   {
//     const auto d =ppPhysicalDevicesdeviceCount.at(i);
//     std::cout << ( "Check Device:" ) << d << "\n";
//     VkDev const ab= VkDev(d);
//     // auto const aaq= Queues(ab);
//     if ( VkDev(d).is )
//     {
//       std::cout << ( "Device Suitable:" ) << d << "\n";
//      Queues::physicalDevice=d;
//       return;
//     }
//     std::cout << ( "Device Not Suitable:" ) << d << "\n";
//   }
//   if ( Queues::physicalDevice == VK_NULL_HANDLE )
//   {
//     std::runtime_error( "Failed to find a suitable GPU" );
//   }
// }
inline VkPhysicalDeviceProperties VkDev::isDeviceSuitable()
{
  VkPhysicalDeviceProperties deviceProperties;
  // VkPhysicalDeviceFeatures   deviceFeatures;
  /*   VkUtilsXBase::getAddrFuncPtr<PFN_vkGetPhysicalDeviceProperties>( "vkGetPhysicalDeviceProperties" )(
      device, &deviceProperties );
    auto b = VkUtilsXBase::getAddrFuncPtr<PFN_vkGetPhysicalDeviceFeatures>( "vkGetPhysicalDeviceFeatures" );
    b( device, &deviceFeatures );*/
  vkGetPhysicalDeviceProperties( pd, &deviceProperties );
  // vkGetPhysicalDeviceFeatures( device, &deviceFeatures );
  // VkUtils2::checkDeviceExtensionSupport( device );
  std::cout << deviceProperties.deviceName << "\n";
  std::cout << deviceProperties.pipelineCacheUUID<< "\n";
  std::cout << deviceProperties.driverVersion<< "\n";
  return deviceProperties;/*&&
                               deviceFeatures.geometryShader;*/
}

inline VkDevice VkDev::createLogicalDevice()
{
  std::cout << ( "Creating Logical Device" ) << "\n";

  uint32_t pQueueFamilyPropertyCount;
  vkGetPhysicalDeviceQueueFamilyProperties( pd, &pQueueFamilyPropertyCount, VK_NULL_HANDLE );

  VkQueueFamilyProperties uniqueQueueFamilies[pQueueFamilyPropertyCount];
  vkGetPhysicalDeviceQueueFamilyProperties( pd, &pQueueFamilyPropertyCount, uniqueQueueFamilies );

  uint32_t i = 0;
  // todo: Likley/Prop won't work with AMD properly and/or specific GPUs with differing Queue Family layouts
  for ( VkQueueFamilyProperties & uniqueQueue : uniqueQueueFamilies )
  {
    std::cout << ( uniqueQueue.queueCount ) << "\n";
    if ( ( uniqueQueue.queueFlags & VK_QUEUE_GRAPHICS_BIT ) )
    {
      Queues::graphicsFamily = i;
      continue;
    }
    // Check that Video Tranfer Queues are not Accidentally selected if the Vulkan beta Drivers from Nvidia are used
    VkBool32 presentSupport = false;
    vkGetPhysicalDeviceSurfaceSupportKHR( pd, i, Queues::surface, &presentSupport );
    if ( uniqueQueue.queueFlags & VK_QUEUE_TRANSFER_BIT && !presentSupport )
    {
      Queues::transferFamily = i;
      break;
    }

    i++;
  }
  std::cout << "Using: " << Queues::graphicsFamily << "-->" << Queues::transferFamily << "\n";

  constexpr float priority = 1.0f;
  uint32_t        pIx      = 0;

  VkDeviceQueueCreateInfo GQ{};

  GQ.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  GQ.queueFamilyIndex = Queues::graphicsFamily;
  GQ.queueCount       = 1;
  GQ.pQueuePriorities = &priority;
  GQ.flags            = 0;
  GQ.pNext            = VK_NULL_HANDLE;

  VkDeviceQueueCreateInfo PQ{};

  PQ.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  PQ.queueFamilyIndex = Queues::transferFamily;
  PQ.queueCount       = 2;
  PQ.pQueuePriorities = &priority;
  PQ.flags            = 0;
  PQ.pNext            = VK_NULL_HANDLE;

  VkDeviceQueueCreateInfo queueCreateInfos[2] = { GQ, PQ };

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


  //.fillModeNonSolid(true) //dneeded to adres valditaion errors when using
  // VK_POLIGYON_MODE_LINE or POINT .robustBufferAccess(true);
  //                        .geometryShader(true);
  //                        .pipelineStatisticsQuery(true)
  //                        .alphaToOne(false);
  vkGetPhysicalDeviceFeatures2( pd, &deviceFeatures2 );

  // vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
  VkDeviceCreateInfo createInfo      = {};
  createInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  createInfo.pNext                   = &deviceFeatures2;
  createInfo.queueCreateInfoCount    = 2;
  createInfo.pQueueCreateInfos       = queueCreateInfos;
  createInfo.ppEnabledExtensionNames = ( &VkUtilsXBase::deviceExtensions );
  createInfo.enabledExtensionCount   = 1;
  // createInfo.ppEnabledLayerNames=(validationLayers.data());
  createInfo.pEnabledFeatures = nullptr;
VkDevice device;
  if ( !deviceVulkan12Features.imagelessFramebuffer )
  {
     std::runtime_error( "Failed Enumeration!" );
  }
  if constexpr ( VkUtilsXBase::ENABLE_VALIDATION_LAYERS )
  {
    createInfo.ppEnabledLayerNames = &VkUtilsXBase::validationLayers;
  }
  VkUtilsXBase::checkCall( vkCreateDevice( pd, &createInfo, VK_NULL_HANDLE, &device ) );
  volkLoadDevice( device );

  VkUtilsXBase::clPPJI3<PFN_vkGetDeviceQueue>( createInfo.pQueueCreateInfos[0].queueFamilyIndex, "vkGetDeviceQueue", 0, &Queues::GraphicsQueue );
  VkUtilsXBase::clPPJI3<PFN_vkGetDeviceQueue>( createInfo.pQueueCreateInfos[1].queueFamilyIndex, "vkGetDeviceQueue", 0, &Queues::TransferQueue[0] );
  VkUtilsXBase::clPPJI3<PFN_vkGetDeviceQueue>( createInfo.pQueueCreateInfos[1].queueFamilyIndex, "vkGetDeviceQueue", 1, &Queues::TransferQueue[1] );
  // Queues::device=device;
  return device;
}


inline VkPhysicalDeviceMemoryProperties VkDev::findMemoryType()
{
  VkPhysicalDeviceMemoryProperties memProperties;
  vkGetPhysicalDeviceMemoryProperties( pd, &memProperties );
  return memProperties;
  // for ( uint32_t i = 0; i < memProperties.memoryTypeCount; i++ )
  // {
  //   if ( ( typeFilter & ( 1U << i ) ) != 0 && ( memProperties.memoryTypes[i].propertyFlags & properties ) == properties )
  //   {
  //     return i;
  //   }
  // }

  std::runtime_error( "Failed to find suitable memory type" );
}