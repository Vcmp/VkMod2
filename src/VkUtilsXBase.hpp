
#pragma once


#define GLFW_EXPOSE_NATIVE_WIN32
#define VK_USE_64_BIT_PTR_DEFINES 1
#define VULKAN_HPP_SUPPORT_SPAN

#undef GLFW_INCLUDE_VULKAN
#include "volk.h"

#include <vector>
#include <iostream>

#ifdef HAVE_CXX_VARIADIC_TEMPLATES
#endif


  static inline constexpr const uint16_t width  = 854;
  static inline constexpr const uint16_t height = 480;

  //  static inline constexpr __int128   aXX    = 0xF;
  static inline constexpr uint8_t    Frames = 3;
  static inline constexpr const bool checks = false;

  // namespace
struct VkUtilsXBase
{
private:
  typedef VkResult ( *callPPPPI )( const VkDevice, const void *, const VkAllocationCallbacks *, const void *, const uint64_t & pHndl );
  const typedef VkResult ( *callPPPPI2 )( const VkDevice, const void *, const VkAllocationCallbacks *, const void *, void * pHndl );
  const typedef VkResult ( *callPPPPI3 )( const VkDevice, const void *, const VkAllocationCallbacks *, const void * );
  // typedef PFN_vkVoidFunction ( *load )( void *, const char * );

public:
  // not sure if auto or exlicitit(ish) templateis better for the return argument
  template <typename T>
  static constexpr auto getAddrFuncPtr( const char * a )
  {
    return reinterpret_cast<T>( vkGetDeviceProcAddr( volkGetLoadedDevice(), a ) );
  }

  // Their may seem to be an anomalous memory leak when the main render Loop/Draw
  // Call is used; howver this is primarily due to the Validation layers
  // being enabled, however if said Validation Layers are disabled, the memeory
  // leak virtually entirely disappears and at least thus far does not seem to be
  // an issue thankfully
  static constexpr bool debug = false;

  static constexpr bool ENABLE_VALIDATION_LAYERS = debug;

  static constexpr char const * validationLayers = "VK_LAYER_KHRONOS_validation";
  static constexpr char const * deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

  static constexpr void checkCall( const VkResult callPPPPI )
  {
    if constexpr ( checks )
    {
      switch ( callPPPPI )
      {
        case VK_SUCCESS: /* std::cout<<("OK!")<< "\n"; */ break;
        case VK_NOT_READY:  std::runtime_error( "Not ready!" );
        case VK_TIMEOUT:  std::runtime_error( "Bad TimeOut!" );
        case VK_INCOMPLETE:  std::runtime_error( "Incomplete!" );
        case VK_ERROR_INITIALIZATION_FAILED:  std::runtime_error( "Error: bad Initialisation!" );
        case VK_ERROR_DEVICE_LOST:  std::runtime_error( "Error: Device Failed/Lost!" );
        case VK_ERROR_FRAGMENTED_POOL:  std::runtime_error( "Error: bad Mem Alloc" );
        case VK_ERROR_OUT_OF_HOST_MEMORY:  std::runtime_error( "No Host Memory" );
        case VK_ERROR_OUT_OF_DEVICE_MEMORY:  std::runtime_error( "No Device Memory" );
        case VK_ERROR_MEMORY_MAP_FAILED:  std::runtime_error( "Bad Memory map!" );
        case VK_ERROR_UNKNOWN:  std::runtime_error( "Unknown Error!|" );
        case VK_ERROR_OUT_OF_POOL_MEMORY:  std::runtime_error( "Out of PooL Memory" );
        case VK_ERROR_INVALID_EXTERNAL_HANDLE:  std::runtime_error( "VK_ERROR_INVALID_EXTERNAL_HANDLE" );
        case VK_ERROR_FRAGMENTATION:  std::runtime_error( "VK_ERROR_INVALID_EXTERNAL_HANDLE" );
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS:  std::runtime_error( "VK_ERROR_FRAGMENTATION" );
        case VK_ERROR_SURFACE_LOST_KHR:  std::runtime_error( "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS" );
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR:  std::runtime_error( "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR" );
        case VK_ERROR_OUT_OF_DATE_KHR:  std::runtime_error( "" );
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR:  std::runtime_error( "" );
        case VK_ERROR_VALIDATION_FAILED_EXT:  std::runtime_error( "" );
        case VK_ERROR_INVALID_SHADER_NV:  std::runtime_error( "" );
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT:  std::runtime_error( "" );
        case VK_ERROR_NOT_PERMITTED_EXT:  std::runtime_error( "" );
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT:  std::runtime_error( "" );
        case VK_THREAD_IDLE_KHR:  std::runtime_error( "" );
        case VK_THREAD_DONE_KHR:  std::runtime_error( "" );
        case VK_OPERATION_DEFERRED_KHR:  std::runtime_error( "" );
        case VK_OPERATION_NOT_DEFERRED_KHR:  std::runtime_error( "" );
        case VK_PIPELINE_COMPILE_REQUIRED_EXT:  std::runtime_error( "" ); break;
        case VK_SUBOPTIMAL_KHR:  std::runtime_error( "VK_SUBOPTIMAL_KHR" );

        default: std::cout << callPPPPI << "\n";  std::runtime_error( "Unknown Error!" );
      }
    }
  }

  typedef VkResult ( *callPPPPJI )( VkDevice, const void *, uint32_t *, const void *, VkAllocationCallbacks *, const void *, PFN_vkVoidFunction pHndl );
  template <typename T>
  inline static constexpr auto getDevProd( const char * a )
  {
    return reinterpret_cast<T>( vkGetDeviceProcAddr( volkGetLoadedDevice(), a ) );
  }
  static inline void doPointerAlloc3( const void * a, const void * c, void * pHndl )
  {
    ( reinterpret_cast<callPPPPI3>( pHndl )( volkGetLoadedDevice(), a, nullptr, c ) );
  }
  template <typename T>
  static inline void constexpr doPointerAlloc2( const void * a, const void * c, T pHndl )
  {
    ( reinterpret_cast<callPPPPI2>( pHndl )( volkGetLoadedDevice(), a, nullptr, c, pHndl ) );
  }
  static inline VkResult doPointerAlloc( const void * a, const void * c, const uint64_t & pHndl )
  {
    return ( reinterpret_cast<callPPPPI>( pHndl )( volkGetLoadedDevice(), a, nullptr, c, pHndl ) );
  }
  template <typename T>
  static inline constexpr void clP( auto * __restrict__ pStrct, const char * __restrict__ a )
  {
    const VkDevice aa = volkGetLoadedDevice();
    T( vkGetDeviceProcAddr( aa, a ) )( pStrct );
  }
  template <typename T>
  static inline constexpr void clPII( VkDevice __restrict__ & aa, auto * __restrict__ pStrct, const char * __restrict__ a, auto * __restrict__ object )
  {
    T( vkGetDeviceProcAddr( aa, a ) )( pStrct, 1, object, nullptr );
  }
  template <typename T>
  static inline constexpr void clPI( auto * __restrict__ pStrct, const char * __restrict__ a, auto * __restrict__ object )
  {
    const VkDevice aa = volkGetLoadedDevice();
    T( vkGetDeviceProcAddr( aa, a ) )( pStrct, object );
  }
  template <typename T>
  static inline constexpr void clPPJI3( uint32_t y, const char * __restrict__ a, uint32_t x, auto * __restrict__ object )
  {
    const VkDevice aa = volkGetLoadedDevice();
    T( vkGetDeviceProcAddr( aa, a ) )( aa, y, x, object );
  }
  template <typename T>
  static inline constexpr void clPPI3( auto * __restrict__ pStrct, const char * __restrict__ a, auto * __restrict__ object )
  {
    const VkDevice aa = volkGetLoadedDevice();
    T( vkGetDeviceProcAddr( aa, a ) )( aa, pStrct, object );
  }
  template <typename T>
  static inline constexpr void clPPPI3( auto * __restrict__ pStrct, const char * __restrict__ a, auto * __restrict__ object )
  {
    const VkDevice aa = volkGetLoadedDevice();
    T( vkGetDeviceProcAddr( aa, a ) )( aa, pStrct, nullptr, object );
  }

  template <typename T>
  static inline constexpr T clPPPI2( const void * pStrct, const char * a )
  {
    T Hndl = getDevProd<T>( a );
    if constexpr ( checks )
    {
      std::cout << a << "-->" << Hndl << "\n";
    }
    T object = 0;
    ( doPointerAlloc2( pStrct, &object, Hndl ) );
    if constexpr ( checks )
    {
      if ( object == 0 )
      {
         std::runtime_error( "bad Alloctaion!: Null handle!" );
      }
      std::cout << &object << "\n";
    }
    return ( object );
  }
  static inline void clPPPI( const void * pStrct, const char * a, const void * object )
  {
    const auto Hndl = reinterpret_cast<uint64_t>( vkGetDeviceProcAddr( volkGetLoadedDevice(), a ) );
    if constexpr ( checks )
    {
      std::cout << a << "-->" << Hndl << "\n";
    }
    checkCall( doPointerAlloc( pStrct, object, Hndl ) );
    if constexpr ( checks )
    {
      if ( object == nullptr )
      {
         std::runtime_error( "bad Alloctaion!: Null handle!" );
      }
    }
  }

  template <typename T>
  static inline constexpr void
    clPPPPJ( VkDevice __restrict__ aa, auto * __restrict__ pStrct, uint32_t z, auto * __restrict__ zy, const char * a, uint32_t * __restrict__ object )
  {
    T( vkGetDeviceProcAddr( aa, a ) )( aa, pStrct, z, zy, nullptr, object );
  }
  template <typename T>
  static inline constexpr void clPPPJI( auto * pStrct, int ax, const char * a, auto * object )
  {
    VkDevice aa = volkGetLoadedDevice();
    T( vkGetDeviceProcAddr( aa, a ) )( aa, nullptr, 1, pStrct, nullptr, object );
  }
};  // namespace

// namespace
