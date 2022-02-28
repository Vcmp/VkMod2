#pragma once
#define GLFW_EXPOSE_NATIVE_WIN32
// #define VK_USE_PLATFORM_WIN32_KHR
#define VK_USE_64_BIT_PTR_DEFINES 1
#define VULKAN_HPP_SUPPORT_SPAN
// #undef VK_KHR_acceleration_structure
// #undef VK_INTEL_performance_query
// #undef VK_EXT_extended_dynamic_state
// #undef VK_VERSION_1_3
// #undef VK_GOOGLE_display_timing
// #undef VK_AMD_buffer_marker
// #undef VK_NV_ray_tracing
// #undef VK_KHR_device_group
#undef GLFW_INCLUDE_VULKAN
// #ifdef __cplusplus
// #define VULKAN_HPP_CPLUSPLUS 201803L
// #endif

// #define VOLK_IMPLEMENTATION
// #define VK_NO_PROTOTYPES
#include "volk.h"
// #define VK_USE_64_BIT_PTR_DEFINES 1
// #define VK_ENABLE_BETA_EXTENSIONS
// #include <stdint.h>

#ifdef _MSVC_LANG
#  define _MSVC_LANG 201803L
#endif
// #define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// #include <vcruntime.h>

#include <iostream>
#include <vector>

// VkPhysicalDevicePortabilitySubsetFeaturesKHR ptr = {};

inline namespace
{
  static constexpr const uint16_t width  = 854;
  static constexpr const uint16_t height = 480;

  static constinit __int128   aXX    = 0xF;
  static constexpr uint8_t    Frames = 3;
  static constinit const bool checks = true;
  // static constinit inline PFN_vkAcquireNextImageKHR vkAcquireNextImageKHR2;
  // static constinit inline PFN_vkQueueSubmit         vkQueueSubmit2;
  // static constinit inline PFN_vkQueuePresentKHR     vkQueuePresentKHR2;
  // static constinit inline PFN_vkCreateSemaphore     vkCreateSemaphore2;

  // static inline constexpr void VtTable2x( auto aa )
  // {
  //   vkAcquireNextImageKHR2 =
  //     reinterpret_cast<PFN_vkAcquireNextImageKHR>( vkGetDeviceProcAddr( aa, "vkAcquireNextImageKHR" ) );
  //   vkQueueSubmit2     = reinterpret_cast<PFN_vkQueueSubmit>( vkGetDeviceProcAddr( aa, "vkQueueSubmit" ) );
  //   vkQueuePresentKHR2 = reinterpret_cast<PFN_vkQueuePresentKHR>( vkGetDeviceProcAddr( aa, "vkQueuePresentKHR" ) );
  //   vkCreateSemaphore2 = reinterpret_cast<PFN_vkCreateSemaphore>( vkGetDeviceProcAddr( aa, "vkCreateSemaphore" ) );
  // }
}  // namespace

struct VkUtilsXBase
{
private:
  typedef VkResult( __vectorcall * callPPPPI )(
    const VkDevice, const void *, const VkAllocationCallbacks *, const void *, const uint64_t & pHndl );
  const typedef VkResult( __vectorcall * callPPPPI2 )(
    const VkDevice, const void *, const VkAllocationCallbacks *, const void *, void * pHndl );
  const typedef VkResult( __vectorcall * callPPPPI3 )( const VkDevice,
                                                       const void *,
                                                       const VkAllocationCallbacks *,
                                                       const void * );
  // typedef PFN_vkVoidFunction ( *load )( void *, const char * );

public:
  // not sure if auto or exlicitit(ish) templateis better for the return argument
  template <typename T>
  static constexpr auto getAddrFuncPtr( const char * a )
  {
    return reinterpret_cast<T>( vkGetDeviceProcAddr( volkGetLoadedDevice(), a ) );
  }

  // Their may seem to be an anomalous memory leak when the main render Loop/Draw
  // Call is used; howver this is mearly/primaro;y due to the Validation layers
  // being enabled, however if said Validation Layers are disabled, the memeory
  // leak virtually entirely disappears and at least thus far does not seem to be
  // an issue thankfully
  static constexpr bool debug = false;

  static constexpr bool ENABLE_VALIDATION_LAYERS =
    debug;  // todo: Posible Bug: ValidationLayersBreak Shader Compilation due to
            // (Presumably) incorerctly marking the cimpiled Spir-V Shaders/Files
            // as having/Containing Invalid Magic Numbers

  static constexpr char const * validationLayers = "VK_LAYER_KHRONOS_validation";
  static constexpr char const * deviceExtensions = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

  static constexpr void checkCall( const VkResult callPPPPI )
  {
    if constexpr ( checks )
    {
      switch ( callPPPPI )
      {
        case VK_SUCCESS: /* std::cout<<("OK!")<< "\n"; */ break;
        case VK_NOT_READY: throw std::runtime_error( "Not ready!" );
        case VK_TIMEOUT: throw std::runtime_error( "Bad TimeOut!" );
        case VK_INCOMPLETE: throw std::runtime_error( "Incomplete!" );
        case VK_ERROR_INITIALIZATION_FAILED: throw std::runtime_error( "Error: bad Initialisation!" );
        case VK_ERROR_DEVICE_LOST: throw std::runtime_error( "Error: Device Failed/Lost!" );
        case VK_ERROR_FRAGMENTED_POOL: throw std::runtime_error( "Error: bad Mem Alloc" );
        case VK_ERROR_OUT_OF_HOST_MEMORY: throw std::runtime_error( "No Host Memory" );
        case VK_ERROR_OUT_OF_DEVICE_MEMORY: throw std::runtime_error( "No Device Memory" );
        case VK_ERROR_MEMORY_MAP_FAILED: throw std::runtime_error( "Bad Memory map!" );
        case VK_ERROR_UNKNOWN: throw std::runtime_error( "Unknown Error!|" );
        case VK_ERROR_OUT_OF_POOL_MEMORY: throw std::runtime_error( "Out of PooL Memory" );
        case VK_ERROR_INVALID_EXTERNAL_HANDLE: throw std::runtime_error( "VK_ERROR_INVALID_EXTERNAL_HANDLE" );
        case VK_ERROR_FRAGMENTATION: throw std::runtime_error( "VK_ERROR_INVALID_EXTERNAL_HANDLE" );
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: throw std::runtime_error( "VK_ERROR_FRAGMENTATION" );
        case VK_ERROR_SURFACE_LOST_KHR: throw std::runtime_error( "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS" );
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: throw std::runtime_error( "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR" );
        case VK_ERROR_OUT_OF_DATE_KHR: throw std::runtime_error( "" );
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: throw std::runtime_error( "" );
        case VK_ERROR_VALIDATION_FAILED_EXT: throw std::runtime_error( "" );
        case VK_ERROR_INVALID_SHADER_NV: throw std::runtime_error( "" );
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: throw std::runtime_error( "" );
        case VK_ERROR_NOT_PERMITTED_EXT: throw std::runtime_error( "" );
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: throw std::runtime_error( "" );
        case VK_THREAD_IDLE_KHR: throw std::runtime_error( "" );
        case VK_THREAD_DONE_KHR: throw std::runtime_error( "" );
        case VK_OPERATION_DEFERRED_KHR: throw std::runtime_error( "" );
        case VK_OPERATION_NOT_DEFERRED_KHR: throw std::runtime_error( "" );
        case VK_PIPELINE_COMPILE_REQUIRED_EXT: throw std::runtime_error( "" ); break;
        case VK_SUBOPTIMAL_KHR: throw std::runtime_error( "VK_SUBOPTIMAL_KHR" );

        default: std::cout << callPPPPI << "\n"; throw std::runtime_error( "Unknown Error!" );
      }
    }
  }

  /*todo: Adiitonal posible Bug: if a typeDef Cast/PointerFunction/Aslias e.g
   * .Misc is used to allow access to .call vkPipelineLayoutCreateInfo, the
   * Validtaion layers incorrertcly warn that VkGraphicsPipelineCreateInfo struct
   * is mising the cprrect sType the only way to correct this is to
   * manuall/Dierctly exempt the "pipelineCache" and "createInfoCount"
   * Arguments/Parametsr of the call, Which causes Misiing createInfoCount  and
   * VkPipelineCache  issues but allows the pipeline to be created
   * properly/correctly this is possibly a Driver Bug/ NV/nSight layer Bug/issue
   * (as a very old beta driver is being utilised [451.74]) but is unconfirmed
   * currently
   */
  typedef VkResult( __vectorcall * callPPPPJI )(
    VkDevice, const void *, uint32_t *, const void *, VkAllocationCallbacks *, const void *, PFN_vkVoidFunction pHndl );
  // typedef const VkResult (__vectorcall *callPPI) (VkDevice,
  //                                 //  VkPipelineCache*,
  //                                  const void *,uint32_t*,

  //                                  const VkAllocationCallbacks *);
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
    // auto           Hndl = reinterpret_cast<T>( vkGetDeviceProcAddr( aa, a ) );
    // auto Hndl = reinterpret_cast<T /* uint64_t */>( vkGetDeviceProcAddr( aa, a ) );
    // doPointerAlloc( pStrct, object, Hndl );
    T( vkGetDeviceProcAddr( aa, a ) )( pStrct );
  }
  template <typename T>
  static inline constexpr void clPII( VkDevice __restrict__ & aa,
                                      auto * __restrict__ pStrct,
                                      const char * __restrict__ a,
                                      auto * __restrict__ object )
  {
    // const VkDevice aa = volkGetLoadedDevice();
    // auto           Hndl = reinterpret_cast<T>( vkGetDeviceProcAddr( aa, a ) );
    // auto Hndl = reinterpret_cast<T /* uint64_t */>( vkGetDeviceProcAddr( aa, a ) );
    // doPointerAlloc( pStrct, object, Hndl );
    T( vkGetDeviceProcAddr( aa, a ) )( pStrct, 1, object, nullptr );
  }
  template <typename T>
  static inline constexpr void
    clPI( auto * __restrict__ pStrct, const char * __restrict__ a, auto * __restrict__ object )
  {
    const VkDevice aa = volkGetLoadedDevice();
    // auto           Hndl = reinterpret_cast<T>( vkGetDeviceProcAddr( aa, a ) );
    // auto Hndl = reinterpret_cast<T /* uint64_t */>( vkGetDeviceProcAddr( aa, a ) );
    // doPointerAlloc( pStrct, object, Hndl );
    T( vkGetDeviceProcAddr( aa, a ) )( pStrct, object );
  }
  template <typename T>
  static inline constexpr void
    clPPJI3( uint32_t y, const char * __restrict__ a, uint32_t x, auto * __restrict__ object )
  {
    const VkDevice aa = volkGetLoadedDevice();
    // auto           Hndl = reinterpret_cast<T>( vkGetDeviceProcAddr( aa, a ) );
    // auto Hndl = reinterpret_cast<T /* uint64_t */>( vkGetDeviceProcAddr( aa, a ) );
    // doPointerAlloc( pStrct, object, Hndl );
    T( vkGetDeviceProcAddr( aa, a ) )( aa, y, x, object );
  }
  template <typename T>
  static inline constexpr void
    clPPI3( auto * __restrict__ pStrct, const char * __restrict__ a, auto * __restrict__ object )
  {
    const VkDevice aa = volkGetLoadedDevice();
    // auto           Hndl = reinterpret_cast<T>( vkGetDeviceProcAddr( aa, a ) );
    // auto Hndl = reinterpret_cast<T /* uint64_t */>( vkGetDeviceProcAddr( aa, a ) );
    // doPointerAlloc( pStrct, object, Hndl );
    T( vkGetDeviceProcAddr( aa, a ) )( aa, pStrct, object );
  }
  template <typename T>
  static inline constexpr void
    clPPPI3( auto * __restrict__ pStrct, const char * __restrict__ a, auto * __restrict__ object )
  {
    const VkDevice aa = volkGetLoadedDevice();
    // auto           Hndl = reinterpret_cast<T>( vkGetDeviceProcAddr( aa, a ) );
    // auto Hndl = reinterpret_cast<T /* uint64_t */>( vkGetDeviceProcAddr( aa, a ) );
    // doPointerAlloc( pStrct, object, Hndl );
    T( vkGetDeviceProcAddr( aa, a ) )( aa, pStrct, nullptr, object );
  }

  template <typename T>
  static inline constexpr T clPPPI2( const void * pStrct, const char * a )
  {
    // vkGetDeviceProcAddr()
    //  auto xx= ;
    T Hndl = getDevProd<T>( a );
    // const callPPPPI x =reinterpret_cast<callPPPPI>(vkGetDeviceProcAddr(device,
    // a)); std::cout << &x << "\n"; std::cout << &pStrct << &object<<&a<<"\n";
    if constexpr ( checks )
    {
      std::cout << a << "-->" << Hndl << "\n";
    }
    // std::cout << object<<"\n";
    // const VkResult VkR =x(device, pStrct, nullptr, object);
    T object = 0;
    ( doPointerAlloc2( pStrct, &object, Hndl ) );
    if constexpr ( checks )
    {
      if ( object == 0 )
      {
        throw std::runtime_error( "bad Alloctaion!: Null handle!" );
      }
      std::cout << &object << "\n";
    }
    return ( object );
    // return VkR;
    //  callPPPPI(device, pStrct, nullptr, a)
  }
  static inline void clPPPI( const void * pStrct, const char * a, const void * object )
  {
    // vkGetDeviceProcAddr()
    //  auto xx= ;
    const auto Hndl = reinterpret_cast<uint64_t>( vkGetDeviceProcAddr( volkGetLoadedDevice(), a ) );
    // const callPPPPI x =reinterpret_cast<callPPPPI>(vkGetDeviceProcAddr(device,
    // a)); std::cout << &x << "\n"; std::cout << &pStrct << &object<<&a<<"\n";
    if constexpr ( checks )
    {
      std::cout << a << "-->" << Hndl << "\n";
    }
    // std::cout << object<<"\n";
    // const VkResult VkR =x(device, pStrct, nullptr, object);
    checkCall( doPointerAlloc( pStrct, object, Hndl ) );
    if constexpr ( checks )
    {
      if ( object == nullptr )
      {
        throw std::runtime_error( "bad Alloctaion!: Null handle!" );
      }
    }

    //  callPPPPI(device, pStrct, nullptr, a)
  }
  // static inline int doSized(const void* aabs, const void* abs2x)
  // {
  //     return sizeof(aabs)/sizeof(abs2x);
  // }

  template <typename T>
  static inline constexpr void clPPPPJ( VkDevice __restrict__ aa,
                                        auto * __restrict__ pStrct,
                                        uint32_t z,
                                        auto * __restrict__ zy,
                                        const char * a,
                                        uint32_t * __restrict__ object )
  {
    // VkDevice aa = volkGetLoadedDevice();
    // vkGetDeviceProcAddr()
    //  auto xx=PFN_vkVoidFunction(swapChain);

    // const T Hndl = (T)vkGetDeviceProcAddr( volkGetLoadedDevice(), a );
    // const callPPPPI ss=reinterpret_cast<callPPPPI>(vkGetDeviceProcAddr(device,
    // a));
    //  std::cout << &x << "\n";
    //  std::cout << &pStrct << &object<<&a<<"\n";
    //  std::cout << a<<"\n";
    //  std::cout << object<<"\n";
    //  VkPipelineCache axx =nullptr;
    //  const VkResult VkR =x(device, pStrct, nullptr, object);
    // ss(device, pStrct, nullptr, object);
    T( vkGetDeviceProcAddr( aa, a ) )( aa, pStrct, z, zy, nullptr, object );

    // return VkR;
    //  callPPPPI(device, pStrct, nullptr, a)
  }
  template <typename T>
  static inline constexpr void clPPPJI( auto * pStrct, int ax, const char * a, auto * object )
  {
    VkDevice aa = volkGetLoadedDevice();
    // vkGetDeviceProcAddr()
    //  auto xx=PFN_vkVoidFunction(swapChain);

    // const T Hndl = (T)vkGetDeviceProcAddr( volkGetLoadedDevice(), a );
    // const callPPPPI ss=reinterpret_cast<callPPPPI>(vkGetDeviceProcAddr(device,
    // a));
    //  std::cout << &x << "\n";
    //  std::cout << &pStrct << &object<<&a<<"\n";
    //  std::cout << a<<"\n";
    //  std::cout << object<<"\n";
    //  VkPipelineCache axx =nullptr;
    //  const VkResult VkR =x(device, pStrct, nullptr, object);
    // ss(device, pStrct, nullptr, object);
    T( vkGetDeviceProcAddr( aa, a ) )( aa, nullptr, 1, pStrct, nullptr, object );

    // return VkR;
    //  callPPPPI(device, pStrct, nullptr, a)
  }
};  // namespace

// namespace