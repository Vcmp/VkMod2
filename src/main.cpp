#include "Interface.hpp"
// #define ASAN_OPTIONS = debug=true

inline namespace
{

  static constinit inline bool      a = true;
  static constinit inline uint16_t  aa;
  static constinit inline pthread_t sys;
  // static inline pthread_t rThrd;

}  // namespace
// Apparently Threads other than the  main thread have much smaller stacl alloctaion Sizes... (Can't/Unable to confirm this however (thus far/Currently))
inline void * Sysm( void * pv_unused )
{
  // _mm256_zeroall();
  while ( a )
  {
    std::cout << aa /* <<"--->"<< duration  */ << "\n";
    std::cout << cc /* <<"--->"<< duration  */ << "\n";
    // m4.loadAligned( BuffersX::data );
    // m4.show();
    aa = 0;
    sleep( 1 );
  }
  return NULL;
}
int __cdecl main( int argc, char * argv[] )  // __attribute__( ( __aligned__( 32 ) ) )
{
  #if TRACY_ENABLE!=1 // TRACY_IMPORTS
    exit(0)
  #endif
  std::iostream::sync_with_stdio( false );
  std::cout << argv << "-->"
            << "\n";
  for ( int a = 0; a < argc; a++ )
  {
    std::cout << argv[a] << "\n";
  }
  int r;

  r = pthread_create( &sys, nullptr, Sysm, nullptr );
  // renderer2::setupRenderDraw();
  while ( !glfwWindowShouldClose( ( VkUtils2::window ) ) )
  {
    glfwPollEvents();
    // glfwWaitEventsTimeout(1);

    renderer2::drawFrame();
    aa++;
  }
  a = false;
  glfwPostEmptyEvent();
  pthread_join( sys, nullptr );

  glfwDestroyWindow( VkUtils2::window );
  glfwTerminate();
}

inline constexpr void renderer2::setupRenderDraw()
{
}

inline static void memPutLong( void * a, void const * b )
{
  a = &b;
}

// Lazy way to avoid having to deal with fences via use of SIMULTANEOUS USE BIT
// which depsote the apparent ineffciency of redundant submision is drastically
// more performant than a considrrable degree of more contventional
// fence/Synchronisation setups
inline void renderer2::drawFrame()
{
  // m4.loadAligned( &m5 );
  vkAcquireNextImageKHR( Queues::device, swapChain, -1, R2.AvailableSemaphore, nullptr, &currentFrame );
  // __builtin_prefetch( BuffersX::data );
  // __builtin_prefetch( &viewproj2x );
  updateUniformBuffer();
  R2.info.pCommandBuffers = &PipelineX::commandBuffers[currentFrame];

  vkQueueSubmit( Queues::GraphicsQueue, 1, &R2.info, nullptr );

  //  info.pWaitSemaphores = &AvailableSemaphore;

  vkQueuePresentKHR( Queues::GraphicsQueue, &VkPresentInfoKHR1 );

  currentFrame = currentFrame + __builtin_parity( Frames );
}

constexpr inline void renderer2::memcpy2( __int256 * __restrict__ _Dst, __int256 const * __restrict__ _Src, size_t _MaxCount )
{
  *_Dst = *_Src;
}
static inline void * __movsb( void * d, const void * s, size_t n )
{
  asm volatile( "rep movsb" : "=D"( d ), "=S"( s ), "=c"( n ) : "0"( d ), "1"( s ), "2"( 32 ) : "memory" );
  return d;
}
inline void renderer2::updateUniformBuffer()
{
  // const float time = static_cast<float>( glfwGetTime() ) * ah;
  static float c;
  static float s;
  static constexpr float xs = 1;
  sincosf( glfwGetTime() * ah, &c, &s );
  __builtin_prefetch( BuffersX::data, 1, 3 );
  // const float ax = glfwGetTime() * ah;

  // rot = viewproj * glm::rotate( glm::identity<glm::mat4>(), ax, glm::vec3( 1, 0, 0 ) );

  // const __m128 ones = _mm_broadcast_ss( &xs );
  // _mm256_storeu2_m128i();

  // const __m256 aa = viewproj2x;
  // const __m256 osx2    = _mm256_set_ps( c, c, c, c, 0, 0, 0, 0 );
  // const __m128 osx2    = _mm_set1_ps( c );
  // const __m256 osx     = _mm256_set1_ps( c );
  // const __m256 osxyzsZ = _mm256_set1_ps( s );
  // const __m256 XORS    = _mm256_sub_ps( _mm256_xor_ps( osx, osx2 ), osx2 );
  // const __m128 XORS = _mm_sub_ps( _mm_sub_ps( osx2, osx2 ), osx2 );

  // const __m256 a = viewproj2x * _mm256_insertf128_ps( osx, XORS, 1 );
  // _mm256_xor_ps( osx, axvZXLI );
  // _mm256_storeu2_m128( &c, &c2, a );

  // const auto x = _mm256_fmaddsub_ps( viewproj2x, osxyzsZ, a );

   const auto x=_mm256_fmaddsub_ps( viewproj2x, _mm256_set1_ps( s ), viewproj2x * _mm256_insertf128_ps( _mm256_set1_ps( c ), -_mm_set1_ps( c ) , 1 ) );
   *BuffersX::data=x;
  // _mm256_zeroupper();

  // memcpy( BuffersX::data, &x, sizeof( x ) );
}

// todo: Wake from callBack...

inline void VkUtils2::extracted()
{
  VkUtils2::setupWindow();
  VkUtils2::createInstance();
  VkUtils2::setupDebugMessenger();
  VkUtils2::createSurface();
  VkUtils2::pickPhysicalDevice();
  VkUtils2::createLogicalDevice();
  SwapChainSupportDetails::setupImageFormats();
  SwapChainSupportDetails::createSwapChain();
  SwapChainSupportDetails::createImageViews();
  PX.createRenderPasses();
  UniformBufferObject::createDescriptorSetLayout();
  PX.createGraphicsPipelineLayout();
  Queues::createCommandPool();
  BuffersX::setupBuffers();
  SwapChainSupportDetails::createFramebuffers();

  UniformBufferObject::createUniformBuffers();

  UniformBufferObject::createDescriptorPool();
  UniformBufferObject::createDescriptorSets();
  PipelineX::createCommandBuffers();
}
long permuteMat( long, long );

inline void VkUtils2::setupWindow()
{
  volkInitialize();
  glfwInit();
  glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
  glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );
  // glfwWindowHint(GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS);
  // glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
  // glfwWindowHint(GLFW_CONTEXT_RELEASE_BEHAVIOR , GLFW_RELEASE_BEHAVIOR_NONE);

  window = glfwCreateWindow( width, height, "VKMod2", nullptr, nullptr );

  assert( window );

  glfwSetWindowShouldClose( ( window ), false );
}

inline void VkUtils2::createInstance()
{
  std::cout << ( "Creating Instance" ) << "\n";
  if ( VkUtilsXBase::ENABLE_VALIDATION_LAYERS && !VkUtils2::checkValidationLayerSupport() )
  {
    std::runtime_error( "Validation requested but not supported" );
  }

  static constexpr VkValidationFeatureEnableEXT valdFeatures[]        = { VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,
                                                                   VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
                                                                   VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT };
  constexpr VkValidationFeaturesEXT             extValidationFeatures = {
                .sType                         = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
                .enabledValidationFeatureCount = 3,
                .pEnabledValidationFeatures    = valdFeatures,
  };

  constexpr VkApplicationInfo vkApplInfo = {

    .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pNext              = VK_NULL_HANDLE,
    .pApplicationName   = "VKMod2",
    .applicationVersion = VK_MAKE_VERSION( 1, 2, 0 ),
    .pEngineName        = "No Engine",
    .engineVersion      = VK_MAKE_VERSION( 1, 2, 0 ),

    .apiVersion = VK_API_VERSION_1_2
  };
  VkInstanceCreateInfo InstCreateInfo    = {};
  InstCreateInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  InstCreateInfo.pApplicationInfo        = &vkApplInfo;
  auto extensions                        = getRequiredExtensions();
  InstCreateInfo.ppEnabledExtensionNames = extensions.data();

  InstCreateInfo.enabledExtensionCount = static_cast<uint32_t>( extensions.size() );

  if constexpr ( VkUtilsXBase::ENABLE_VALIDATION_LAYERS )
  {
    InstCreateInfo.ppEnabledLayerNames = ( &VkUtilsXBase::validationLayers );
    InstCreateInfo.enabledLayerCount   = 1;
    InstCreateInfo.pNext               = &extValidationFeatures;
  }
  else
    InstCreateInfo.enabledLayerCount = 0;

  auto cl = reinterpret_cast<PFN_vkCreateInstance>( vkGetInstanceProcAddr( vkInstance, "vkCreateInstance" ) );

  VkUtilsXBase::checkCall( cl( &InstCreateInfo, VK_NULL_HANDLE, &vkInstance ) );
  volkLoadInstanceOnly( vkInstance );
}

inline void VkUtils2::createSurface()
{
  std::cout << ( "Creating Surface" ) << "\n";
  VkWin32SurfaceCreateInfoKHR createSurfaceInfo = {};
  createSurfaceInfo.sType                       = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
  createSurfaceInfo.hwnd                        = glfwGetWin32Window( const_cast<GLFWwindow *>( window ) );
  createSurfaceInfo.hinstance                   = GetModuleHandle( nullptr );
  createSurfaceInfo.pNext                       = VK_NULL_HANDLE;

  VkUtilsXBase::checkCall( vkCreateWin32SurfaceKHR( vkInstance, &createSurfaceInfo, nullptr, const_cast<VkSurfaceKHR *>( &Queues::surface ) ) );
}

inline bool VkUtils2::checkValidationLayerSupport()
{
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties( &layerCount, nullptr );

  VkLayerProperties availableLayers[layerCount];
  vkEnumerateInstanceLayerProperties( &layerCount, availableLayers );

  return false;
}

inline const std::vector<const char *> VkUtils2::getRequiredExtensions()
{
  uint32_t                  glfwExtensionCount = 0;
  const char **             glfwExtensions     = glfwGetRequiredInstanceExtensions( &glfwExtensionCount );
  std::vector<const char *> extensions( glfwExtensions, glfwExtensions + glfwExtensionCount );
  if constexpr ( VkUtilsXBase::ENABLE_VALIDATION_LAYERS )
  {
    extensions.push_back( VK_EXT_DEBUG_UTILS_EXTENSION_NAME );
  }
  return extensions;
}

VKAPI_ATTR inline VkBool32 VKAPI_CALL VkUtils2::debugCallback( VkDebugUtilsMessageSeverityFlagBitsEXT       messageSeverity,
                                                               VkDebugUtilsMessageTypeFlagsEXT              messageType,
                                                               const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
                                                               void *                                       pUserData )
{
  std::cerr << "validation layer: " << pCallbackData->pMessage << "\n\n";

  return VK_FALSE;
}

inline void VkUtils2::setupDebugMessenger()
{
  if constexpr ( !VkUtilsXBase::ENABLE_VALIDATION_LAYERS )
  {
    return;
  }

  constexpr VkDebugUtilsMessengerCreateInfoEXT createInfo{
    .sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
    .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                       VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
    .messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
    .pfnUserCallback = VkUtils2::debugCallback,
    .pUserData       = VK_NULL_HANDLE,
  };
  VkUtilsXBase::checkCall( createDebugUtilsMessengerEXT( vkInstance, &createInfo ) );
}

inline VkResult VkUtils2::createDebugUtilsMessengerEXT( const VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT * pCreateInfo )
{
  VkDebugUtilsMessengerEXT debugUtils = {};
  // auto func = VkUtilsXBase::getAddrFuncPtr<PFN_vkCreateDebugUtilsMessengerEXT2>( "vkCreateDebugUtilsMessengerEXT" );
  if ( vkCreateDebugUtilsMessengerEXT != VK_NULL_HANDLE )
  {
    return vkCreateDebugUtilsMessengerEXT( instance, pCreateInfo, VK_NULL_HANDLE, &debugUtils );
  }
  else
  {
    return VK_ERROR_EXTENSION_NOT_PRESENT;
  }
}

inline void VkUtils2::pickPhysicalDevice()
{
  std::cout << ( "Picking Physical Device" ) << "\n";
  uint32_t deviceCount;
  VkUtilsXBase::checkCall( vkEnumeratePhysicalDevices( vkInstance, &deviceCount, nullptr ) );
  if ( deviceCount == 0 )
    std::runtime_error( "Failed to find GPUs with Vulkan support" );
  VkPhysicalDevice ppPhysicalDevices[deviceCount];

  std::cout << ( "Enumerate Physical Device" ) << "\n";
  VkUtilsXBase::checkCall( vkEnumeratePhysicalDevices( vkInstance, &deviceCount, ppPhysicalDevices ) );
  for ( const VkPhysicalDevice & d : ppPhysicalDevices )
  {
    std::cout << ( "Check Device:" ) << d << "\n";
    if ( isDeviceSuitable( d ) )
    {
      std::cout << ( "Device Suitable:" ) << d << "\n";
      Queues::physicalDevice = d;
      return;
    }
    std::cout << ( "Device Not Suitable:" ) << d << "\n";
  }
  if ( Queues::physicalDevice == VK_NULL_HANDLE )
  {
    std::runtime_error( "Failed to find a suitable GPU" );
  }
}
// Use VK Tutorial refernce as that sems to be far more reliable that the prior
// java approach used
inline bool VkUtils2::isDeviceSuitable( const VkPhysicalDevice device )
{
  VkPhysicalDeviceProperties deviceProperties;
  VkPhysicalDeviceFeatures   deviceFeatures;
  /*   VkUtilsXBase::getAddrFuncPtr<PFN_vkGetPhysicalDeviceProperties>( "vkGetPhysicalDeviceProperties" )(
      device, &deviceProperties );
    auto b = VkUtilsXBase::getAddrFuncPtr<PFN_vkGetPhysicalDeviceFeatures>( "vkGetPhysicalDeviceFeatures" );
    b( device, &deviceFeatures );*/
  vkGetPhysicalDeviceProperties( device, &deviceProperties );
  vkGetPhysicalDeviceFeatures( device, &deviceFeatures );
  checkDeviceExtensionSupport( device );

  return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU; /*&&
                               deviceFeatures.geometryShader;*/
}

inline void VkUtils2::checkDeviceExtensionSupport( VkPhysicalDevice device )
{
  std::cout << "Verifying checkDeviceExtensionSupport"
            << "\n";
  uint32_t extensionCount;
  vkEnumerateDeviceExtensionProperties( device, VK_NULL_HANDLE, &extensionCount, VK_NULL_HANDLE );
  VkExtensionProperties availableExtensions[extensionCount];  // todo: May MEMory Leak
  vkEnumerateDeviceExtensionProperties( device, VK_NULL_HANDLE, &extensionCount, availableExtensions );
  std::cout << extensionCount << "->Extensions"
            << "\n";
}

inline void VkUtils2::createLogicalDevice()
{
  std::cout << ( "Creating Logical Device" ) << "\n";

  uint32_t pQueueFamilyPropertyCount;
  vkGetPhysicalDeviceQueueFamilyProperties( Queues::physicalDevice, &pQueueFamilyPropertyCount, VK_NULL_HANDLE );

  VkQueueFamilyProperties uniqueQueueFamilies[pQueueFamilyPropertyCount];
  vkGetPhysicalDeviceQueueFamilyProperties( Queues::physicalDevice, &pQueueFamilyPropertyCount, uniqueQueueFamilies );

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
    vkGetPhysicalDeviceSurfaceSupportKHR( Queues::physicalDevice, i, Queues::surface, &presentSupport );
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

  static VkPhysicalDeviceVulkan12Features deviceVulkan12Features = {
    .sType                           = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
    .pNext                           = VK_NULL_HANDLE,
    .descriptorBindingPartiallyBound = true,
    .imagelessFramebuffer            = true,

  };

  static constexpr VkPhysicalDeviceFeatures deviceFeatures = {};

  VkPhysicalDeviceFeatures2 deviceFeatures2 = { .sType    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
                                                .pNext    = &deviceVulkan12Features,
                                                .features = deviceFeatures };

  //.fillModeNonSolid(true) //dneeded to adres valditaion errors when using
  // VK_POLIGYON_MODE_LINE or POINT .robustBufferAccess(true);
  //                        .geometryShader(true);
  //                        .pipelineStatisticsQuery(true)
  //                        .alphaToOne(false);
  vkGetPhysicalDeviceFeatures2( Queues::physicalDevice, &deviceFeatures2 );

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

  if ( !deviceVulkan12Features.imagelessFramebuffer )
  {
     std::runtime_error( "Failed Enumeration!" );
  }
  if constexpr ( VkUtilsXBase::ENABLE_VALIDATION_LAYERS )
  {
    createInfo.ppEnabledLayerNames = &VkUtilsXBase::validationLayers;
  }
  VkUtilsXBase::checkCall( vkCreateDevice( Queues::physicalDevice, &createInfo, VK_NULL_HANDLE, &Queues::device ) );
  volkLoadDevice( Queues::device );

  VkUtilsXBase::clPPJI3<PFN_vkGetDeviceQueue>( createInfo.pQueueCreateInfos[0].queueFamilyIndex, "vkGetDeviceQueue", 0, &Queues::GraphicsQueue );
  VkUtilsXBase::clPPJI3<PFN_vkGetDeviceQueue>( createInfo.pQueueCreateInfos[1].queueFamilyIndex, "vkGetDeviceQueue", 0, &Queues::TransferQueue[0] );
  VkUtilsXBase::clPPJI3<PFN_vkGetDeviceQueue>( createInfo.pQueueCreateInfos[1].queueFamilyIndex, "vkGetDeviceQueue", 1, &Queues::TransferQueue[1] );
}

void VkUtils2::cleanup()
{
  vkDeviceWaitIdle( Queues::device );
  vkUnmapMemory( Queues::device, UniformBufferObject::uniformBuffersMemory );
  vkDestroyCommandPool( Queues::device, (VkCommandPool)Queues::commandPool, nullptr );
  for ( auto framebuffer : swapChainFramebuffers )
  {
    vkDestroyFramebuffer( Queues::device, framebuffer, nullptr );
  }

  vkDestroyBuffer( Queues::device, BuffersX::vertexBuffer, nullptr );
  vkFreeMemory( Queues::device, BuffersX::vertexBufferMemory, nullptr );
}