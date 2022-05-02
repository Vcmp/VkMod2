#include "GLFW/glfw3.h"
#include "VkUtils2.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/gtc/constants.hpp"
#include "renderer2.hpp"
#include "VkTemp.hpp"
#include "VkDev.hpp"


#include <cstddef>
#include <cstdint>
#include <emmintrin.h>
#include <immintrin.h>
#include <pthread.h>
#include <unistd.h>
#include <vulkan/vulkan_core.h>
#include "textTemp.cpp"



/*
  Unfortuately the Linking Structure in this project/Repo is absolutely terrible/Sucks/is Hot Garbage:
    and their was a signficant issue with undefined references with both variables and functions but priamirly the Latter; 
  ideally implemtaions would be compartmentalised and structured more cleanly, but as a result functiom implementations will ahve to be dumped ehere for now to avoid the linker having a fit


Unlesss their is a reliable method of "cross-Linking" or tieing seperate/Disparate translation Units Together their does not seem to be an immedately apparent solution/Quick Fix available to help mitigate/Address the garbage CodeGen/Compile Times and the Abysmall Code Gen Layout
*/
//All Credit "theagentd" : //https://jvm-gaming.org/t/extremely-fast-sine-cosine/55153/80
inline namespace
{
  constexpr double PI = glm::pi<double>();
  constexpr auto SIN_BITS = 9;
	constexpr auto SIN_MASK = ~(-1U << SIN_BITS);
	constexpr auto SIN_COUNT = SIN_MASK + 1;
		
	constexpr	auto radFull = glm::two_pi<float>();
	const __m128	radToIndex = _mm_set1_ps(SIN_COUNT / radFull);
	const __m256	radToIndexA = _mm256_set1_ps(SIN_COUNT / radFull);
		
	constexpr __m128	cosOffset = __extension__ (__m128){ glm::half_pi<double>(), glm::half_pi<double>(), glm::half_pi<double>(), glm::half_pi<double>() };

__attribute__((pure, const)) auto const setupfloat()
    {
      std::array<float, SIN_COUNT+1> sint{};
		for (int i = 0; i <= SIN_COUNT; i++) {
			sint[i] = (float) sin(PI * 2 * i / SIN_COUNT);
		}
    return sint;
    } 
	static const std::array<float, SIN_COUNT+1> sint=setupfloat();
		
    
	
  static constinit inline bool      a = true;
  static constinit inline uint32_t  aa;
  static constinit inline pthread_t sys;
  // static inline pthread_t rThrd;
} 

// Apparently Threads other than the  main thread have much smaller stack allocation sizes, whether this is true is completely unconfirmed however
// thsi also has a bug with GCC ATM where the stdout log putput from thsi therad is not displayed untill the thread is joined at termination/exit.close
inline void * Sysm( void * pv_unused )
{
  // _mm256_zeroall();
  while ( a )
  {
    std::cout << aa /* <<"--->"<< duration  */ << "\n";
    // std::cout << cc /* <<"--->"<< duration  */ << "\n";
    // m4.loadAligned( BuffersX::data );
    // m4.show();
    aa = 0;
    sleep( 1 );
  }
  return NULL;
}
int __cdecl main( int argc, char * argv[] )
{

  std::iostream::sync_with_stdio( false );
  std::cout << argv << "-->"
            << "\n";
  for ( int a = 0; a < argc; a++ )
  {
    std::cout << argv[a] << "\n";
  }
  int r;
  if constexpr(VK_EXT_graphics_pipeline_library)
  {
    printf("VK_EXT_graphics_pipeline_library Supported \n");
  }
  r = pthread_create( &sys, nullptr, Sysm, nullptr );
  setupfloat();
  
  while ( !glfwWindowShouldClose( ( VkUtils2::window ) ) )
  {
    renderer2::drawFrame();
    aa++;
  }
  a = false;

  glfwPostEmptyEvent();
  pthread_join( sys, nullptr );

  glfwDestroyWindow( VkUtils2::window );
  glfwTerminate();
}

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

// Lazy way to avoid having to deal with fences via use of SIMULTANEOUS USE BIT
// which depsote the apparent ineffciency of redundant submision is drastically
// more performant than a considrrable degree of more contventional
// fence/Synchronisation setups
inline void renderer2::drawFrame()
{
  // m4.loadAligned( &m5 );
  
    // vkQueueWaitIdle(Queues::GraphicsQueue);
  vkAcquireNextImageKHR( Queues::device, SwapChainSupportDetails::swapChain, -1, R2.AvailableSemaphore, nullptr, &currentFrame );
  // __builtin_prefetch( BuffersX::data );
  // __builtin_prefetch( &viewproj2x );
  // VkCommandBuffer vCMDB[2]={PipelineX::commandBuffers[currentFrame], tT.comBuffer};
//  tT.voidrecComBufferSub(currentFrame);
  renderer2::updateUniformBuffer(); 

    // vkResetCommandPool(Queues::device, Queues::commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);

   
    // PipelineX::recCmdBuffer(currentFrame);
      R2.info.pCommandBuffers = &PipelineX::commandBuffers[currentFrame];
    vkQueueSubmit( Queues::GraphicsQueue, 1, &R2.info, nullptr );
  // }
  


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
//https://jvm-gaming.org/t/extremely-fast-sine-cosine/55153/79
float cosfromsin(float sin, float angle) __attribute__((pure))
{
  __m128 A=_mm_set1_ps(sin);
  float cos = _mm_sqrt_ps(_mm_set1_ps(1)-A*A)[0];
       
        float b = angle - static_cast<int>((angle / 6.2831855F)) * 6.2831855F;
        // if ((double)b < 0.0) {
        //     b += 6.2831855F;
        // }

        return b >= 3.1415927F ? -cos : cos;
}
// auto sin1(const float& __restrict__ rad) {
// 		float index = rad * radToIndex;
// 		float index2 = rad+cosOffset * radToIndex;

//     __m256 aidxi=_mm256_set_ps(index, index2, index, index2, index, index2, index, index2);
// 		//float floor = (float)Math.floor(index); //Correct
// 		__m256i floor12x = _mm256_floor_ps(aidxi);	              //Fast, only for positive angles
// 		__m256i indexedFloor = (uint32_t)(index) - floor12x;
// 		// float alpha = index - floor;
// 		__m256i a=_mm256_castps_si256(floor12x);
// 		__m256i b=_mm256_set1_epi32(SIN_MASK);
// 		uint32_t i = _mm256_and_ps(a,b)[0];
		
//     auto x = _mm256_set_ps(sint[i+0],sint[i+0],sint[i+0],sint[i+0],sint[i+1],sint[i+1],sint[i+1],sint[i+1]);

// 		__m128 sin1 = _mm_set1_ps(sint[i+0]);
// 		__m128 sin2 = _mm_set1_ps(sint[i+1]);
//         // __m256 sin132x = _mm256_set_m128(sin1, sin2);
//   __m256 sin132x = _mm256_loadu2_m128(&sint[i+0],&sint[i+1]);
		
// 		return _mm256_fmaddsub_ps(indexedFloor, (sin132x), x);
// 		// return _mm256_fmaddsub_ps(x, aidxi, _mm256_sub_ps(a, b));
// 		// return sin1 + (sin2 - sin1) * (indexedFloor[0]);
//     // return indexedFloor * sin1 + (1 - indexedFloor) * sin2;
// 	}

/* const void sinxcosx(const __m128& __restrict__ a, __v8sf&  cos,  __v8sf&  sin)
{
  	// const __m128 index = a * radToIndex;
const auto aaa=a+cosOffset;
	// const auto index2 = aaa * radToIndex;

  const __v8sf w= _mm256_set_m128(aaa, a)*radToIndexA;
  // const __m256 xysc= _mm256_set_m128(index2, index);
		//float floor = (float)Math.floor(index); //Correct
    const auto Floorf=_mm256_floor_ps(w);
    const auto Floorf1=__builtin_convertvector((__v8su)w, __v8sf);
	const	size_t floor = static_cast<uint16_t>(Floorf[0])&SIN_MASK;	       //Edit* also settign sclar isnetad of vetcor also helps furtehr improve Compielr/Gen>Compield/ Outpuit/Asm/REdoeeved Ams       //For some Reason seting this variable.Adders to size_t instead of a distrete float/int or a SIMD/128-Biot Vetcor([__m128/__m128i] masively improves the genrased Assembily/ASM By?from/Via the Compiler (At least With Clang.........,..............))
	const	size_t floor2 = static_cast<uint16_t>(Floorf[4])&SIN_MASK;	       //Edit* also settign sclar isnetad of vetcor also helps furtehr improve Compielr/Gen>Compield/ Outpuit/Asm/REdoeeved Ams       //For some Reason seting this variable.Adders to size_t instead of a distrete float/int or a SIMD/128-Biot Vetcor([__m128/__m128i] masively improves the genrased Assembily/ASM By?from/Via the Compiler (At least With Clang.........,..............))
		
	const	auto alpha = _mm_fmsub_ps(a, radToIndex,__builtin_shufflevector((__v8sf)Floorf, (__v8sf)Floorf, 0, 1, 2, 3)); //Must floor here Otherwise as it dosne;t seem to interpolatw proeprly from teh Sin table
		
		;
			// const float* a=sint.data()+1;
	const	auto sin1 = _mm_set1_ps(sint[floor]);
	const	auto sin2 = _mm_set1_ps(sint[floor+1]-sint[floor]);

const	auto sin12 = _mm_set1_ps(sint[floor2]);
	const	auto sin22 = _mm_set1_ps(sint[floor2+1]-sint[floor2]); //Adaptive Inetrpolation/Steps here......[Maybe]

		const auto axzlvehaqiKXQ=_mm_fmadd_ps(sin22, alpha, sin12);
		
		cos= _mm256_set_m128(_mm_fmadd_ps(sin2, alpha, sin1), -_mm_fmadd_ps(sin2, alpha, sin1))*viewproj2x;

		sin = _mm256_broadcast_ps(&axzlvehaqiKXQ);
// const auto radToIndex2=_mm256_broadcast_ps(&radToIndex);
		//float floor = (float)Math.floor(index); //Correct
    // const auto Floorf2=_mm_round_ps(index2, _MM_FROUND_FLOOR);
	// const	auto floor2 = static_cast<uint16_t>(Floorf2[0])&SIN_MASK;	 //_mm_and_ps(Floorf2,_mm_set1_ps(SIN_MASK))[0];	       //Edit* also settign sclar isnetad of vetcor also helps furtehr improve Compielr/Gen>Compield/ Outpuit/Asm/REdoeeved Ams       //For some Reason seting this variable.Adders to size_t instead of a distrete float/int or a SIMD/128-Biot Vetcor([__m128/__m128i] masively improves the genrased Assembily/ASM By?from/Via the Compiler (At least With Clang.........,..............))
		
	// const	auto alpha2 = _mm_fmsub_ps(aaa, radToIndex, Floorf2); //Must floor here Otherwise as it dosne;t seem to interpolatw proeprly from teh Sin table
		
		;
			// const int a2=floor2[0];
	
  //   const __m128 aa=a+cosOffset;
  // 	const __m256 index2 = _mm256_set_m128(aa * radToIndex, aa * radToIndex);
  //   const auto Floorf2=_mm256_round_ps(index2, _MM_FROUND_FLOOR);
	// const	size_t floor2 = static_cast<uint16_t>(Floorf2[0])&SIN_MASK;	       //Edit* also settign sclar isnetad of vetcor also helps furtehr improve Compielr/Gen>Compield/ Outpuit/Asm/REdoeeved Ams       //For some Reason seting this variable.Adders to size_t instead of a distrete float/int or a SIMD/128-Biot Vetcor([__m128/__m128i] masively improves the genrased Assembily/ASM By?from/Via the Compiler (At least With Clang.........,..............))
	// const	auto alph2a = _mm256_fmsub_ps(_mm256_broadcast_ps(&a), _mm256_broadcast_ps(&radToIndex), Floorf2); //Must floor here Otherwise as it dosne;t seem to interpolatw proeprly from teh Sin table
  // const	auto sin12 = _mm256_set1_ps(sint[floor2]);
	// const	auto sin22 = _mm256_set1_ps(sint[floor2+1])-sin12;
  //   sin=_mm256_fmadd_ps(sin22, alph2a, sin12);
  
} */
const auto sinx(const auto& __restrict__ rad) 
{
	const auto index = rad * radToIndex;
		//float floor = (float)Math.floor(index); //Correct
    const auto Floorf=_mm_round_ps(index, _MM_FROUND_FLOOR);
	const	size_t floor = static_cast<uint16_t>(Floorf[0])&SIN_MASK;	       //Edit* also settign sclar isnetad of vetcor also helps furtehr improve Compielr/Gen>Compield/ Outpuit/Asm/REdoeeved Ams       //For some Reason seting this variable.Adders to size_t instead of a distrete float/int or a SIMD/128-Biot Vetcor([__m128/__m128i] masively improves the genrased Assembily/ASM By?from/Via the Compiler (At least With Clang.........,..............))
	const	size_t floor2 = static_cast<uint16_t>(Floorf[4])&SIN_MASK;	       //Edit* also settign sclar isnetad of vetcor also helps furtehr improve Compielr/Gen>Compield/ Outpuit/Asm/REdoeeved Ams       //For some Reason seting this variable.Adders to size_t instead of a distrete float/int or a SIMD/128-Biot Vetcor([__m128/__m128i] masively improves the genrased Assembily/ASM By?from/Via the Compiler (At least With Clang.........,..............))
		
	const	auto alpha = _mm_fmsub_ps(rad, radToIndex, Floorf); //Must floor here Otherwise as it dosne;t seem to interpolatw proeprly from teh Sin table
		
		;
			// const float* a=sint.data()+1;
	const	auto sin1 = _mm_broadcast_ss(&sint[floor]);
	const	auto sin2 = _mm_broadcast_ss(&sint[floor+1])-sin1;
		
		return _mm_fmadd_ps(sin2, alpha, sin1);
	}

//Attemting to avoid a vinsertf128 by "dupling" the sin vetcor prior beforhand, may or maynot be faster than justusing teh priro /previosu sin methodand 
const auto cosx(const auto& __restrict__ rad) 
{
  const auto radToIndex2=_mm256_broadcast_ps(&radToIndex);
	const auto index = rad * radToIndex2;
		//float floor = (float)Math.floor(index); //Correct
    const auto Floorf=_mm256_round_ps(index, _MM_FROUND_FLOOR);
	// const	__m256i floor = _mm256_and_ps(__builtin_convertvector(Floorf, __v8su),_mm256_set1_ps(SIN_MASK));	       //Edit* also settign sclar isnetad of vetcor also helps furtehr improve Compielr/Gen>Compield/ Outpuit/Asm/REdoeeved Ams       //For some Reason seting this variable.Adders to size_t instead of a distrete float/int or a SIMD/128-Biot Vetcor([__m128/__m128i] masively improves the genrased Assembily/ASM By?from/Via the Compiler (At least With Clang.........,..............))
		
	const	auto alpha = _mm256_fmsub_ps(rad, radToIndex2, Floorf); //Must floor here Otherwise as it dosne;t seem to interpolatw proeprly from teh Sin table
		
		;
			const auto a=static_cast<uint16_t>(Floorf[0])&SIN_MASK;//floor[0];
	const	auto sin1 = _mm256_broadcast_ss(&sint[a]);
	const	auto sin2 = _mm256_broadcast_ss(&sint[a+1])-sin1;
		
		return _mm256_fmadd_ps(sin2, alpha, sin1);
	}
	
	
/* const	__m128 cos1(const __m128& __restrict__  rad) {

		
		return sinx(rad+cosOffset);
	} */
inline void renderer2::updateUniformBuffer()
{
  // const float time = static_cast<float>( glfwGetTime() ) * ah;
  const __v4sf a= _mm_set1_ps((glfwGetTime()));
  __builtin_prefetch( BuffersX::data, 1, 3 );
  // __builtin_prefetch( &viewproj, 1, 3 );
  // const auto vfm =  viewproj2x;
  auto c=sinx(a);//*viewproj2x;
  auto s=sinx(a+cosOffset);
  // sinxcosx(a, c, s);
  

//  c=sinx(a)*viewproj2x;
//   s=cosx(_mm256_set_m128(a+cosOffset,a+cosOffset));
  // static constexpr float xs = 1;
  // sincosf(a, &c, &s );
  // const float ax = glfwGetTime() * ah;

  // rot = viewproj * glm::rotate( glm::identity<glm::mat4>(), ax, glm::vec3( 1, 0, 0 ) );

  // const __m128 ones = _mm_broadcast_ss( &xs );
  // _mm256_storeu2_m128i();

  // const __m256 aa = viewproj2x;
  // const __m256 osx2    = _mm256_set_ps( c, c, c, c, 0, 0, 0, 0 );
  // const __m128 osx2    = _mm_set1_ps( c );
  // const __m256 osx     = _mm256_set1_ps( c );
  // const __m256 osxyzsZ = _mm256_set1_ps( s );
  // // const __m256 XORS    = _mm256_sub_ps( _mm256_xor_ps( osx, osx2 ), osx2 );
  // // const __m128 XORS = _mm_sub_ps( _mm_sub_ps( osx2, osx2 ), osx2 );

  const __m256 aa = viewproj2x * _mm256_insertf128_ps( _mm256_broadcast_ps(&c), -c, 1 );
  // _mm256_xor_ps( osx, axvZXLI );
  // _mm256_storeu2_m128( &c, &c2, a );

  const auto x = _mm256_fmaddsub_ps( viewproj2x, _mm256_broadcast_ps(&s), aa );

  //  const auto x=_mm256_fmaddsub_ps( viewproj2x, s, c);
   *BuffersX::data=x;
  //  m4.__a=x;
  // _mm256_zeroupper();

  // memcpy( BuffersX::data, &x, sizeof( x ) );
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
  auto const vkds=VkDev();
   Queues::physicalDevice=vkds.pd;
   Queues::device=vkds.pds;
   BuffersX::memProperties=vkds.memProperties;
  // std::cout << ( "Picking Physical Device" ) << "\n";
  // uint32_t deviceCount;
  // VkUtilsXBase::checkCall( vkEnumeratePhysicalDevices( vkInstance, &deviceCount, nullptr ) );
  // if ( deviceCount == 0 )
  //   std::runtime_error( "Failed to find GPUs with Vulkan support" );
  //  std::vector<VkPhysicalDevice> ppPhysicalDevicesdeviceCount(deviceCount);

  // std::cout << ( "Enumerate Physical Device" ) << "\n";
  // VkUtilsXBase::checkCall( vkEnumeratePhysicalDevices( vkInstance, &deviceCount, ppPhysicalDevicesdeviceCount.data() ) );
  // for ( auto i=0U; i< ppPhysicalDevicesdeviceCount.size(); i++ )
  // {
  //   const auto d =ppPhysicalDevicesdeviceCount.at(i);
  //   std::cout << ( "Check Device:" ) << d << "\n";
  //   VkDev const ab= VkDev(d);
  //   // auto const aaq= Queues(ab);
  //   if ( VkDev(d).is )
  //   {
  //     std::cout << ( "Device Suitable:" ) << d << "\n";
  //    Queues::physicalDevice=d;
  //     return;
  //   }
  //   std::cout << ( "Device Not Suitable:" ) << d << "\n";
  // }
  // if ( Queues::physicalDevice == VK_NULL_HANDLE )
  // {
  //   std::runtime_error( "Failed to find a suitable GPU" );
  // }
}
// // Use VK Tutorial refernce as that sems to be far more reliable that the prior
// // java approach used
// inline bool VkUtils2::isDeviceSuitable( const VkPhysicalDevice device )
// {
//   VkPhysicalDeviceProperties deviceProperties;
//   // VkPhysicalDeviceFeatures   deviceFeatures;
//   /*   VkUtilsXBase::getAddrFuncPtr<PFN_vkGetPhysicalDeviceProperties>( "vkGetPhysicalDeviceProperties" )(
//       device, &deviceProperties );
//     auto b = VkUtilsXBase::getAddrFuncPtr<PFN_vkGetPhysicalDeviceFeatures>( "vkGetPhysicalDeviceFeatures" );
//     b( device, &deviceFeatures );*/
//   vkGetPhysicalDeviceProperties( device, &deviceProperties );
//   // vkGetPhysicalDeviceFeatures( device, &deviceFeatures );
//   checkDeviceExtensionSupport( device );

//   return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU; /*&&
//                                deviceFeatures.geometryShader;*/
// }

// inline void VkUtils2::checkDeviceExtensionSupport( VkPhysicalDevice device )
// {
//   std::cout << "Verifying checkDeviceExtensionSupport"
//             << "\n";
//   uint32_t extensionCount;
//   vkEnumerateDeviceExtensionProperties( device, VK_NULL_HANDLE, &extensionCount, VK_NULL_HANDLE );
//   VkExtensionProperties availableExtensions[extensionCount];  // todo: May MEMory Leak
//   vkEnumerateDeviceExtensionProperties( device, VK_NULL_HANDLE, &extensionCount, availableExtensions );
//   std::cout << extensionCount << "->Extensions"
//             << "\n";
// }

// inline void VkUtils2::createLogicalDevice()
// {
//   std::cout << ( "Creating Logical Device" ) << "\n";

//   uint32_t pQueueFamilyPropertyCount;
//   vkGetPhysicalDeviceQueueFamilyProperties( Queues::physicalDevice, &pQueueFamilyPropertyCount, VK_NULL_HANDLE );

//   VkQueueFamilyProperties uniqueQueueFamilies[pQueueFamilyPropertyCount];
//   vkGetPhysicalDeviceQueueFamilyProperties( Queues::physicalDevice, &pQueueFamilyPropertyCount, uniqueQueueFamilies );

//   uint32_t i = 0;
//   // todo: Likley/Prop won't work with AMD properly and/or specific GPUs with differing Queue Family layouts
//   for ( VkQueueFamilyProperties & uniqueQueue : uniqueQueueFamilies )
//   {
//     std::cout << ( uniqueQueue.queueCount ) << "\n";
//     if ( ( uniqueQueue.queueFlags & VK_QUEUE_GRAPHICS_BIT ) )
//     {
//       Queues::graphicsFamily = i;
//       continue;
//     }
//     // Check that Video Tranfer Queues are not Accidentally selected if the Vulkan beta Drivers from Nvidia are used
//     VkBool32 presentSupport = false;
//     vkGetPhysicalDeviceSurfaceSupportKHR( Queues::physicalDevice, i, Queues::surface, &presentSupport );
//     if ( uniqueQueue.queueFlags & VK_QUEUE_TRANSFER_BIT && !presentSupport )
//     {
//       Queues::transferFamily = i;
//       break;
//     }

//     i++;
//   }
//   std::cout << "Using: " << Queues::graphicsFamily << "-->" << Queues::transferFamily << "\n";

//   constexpr float priority = 1.0f;
//   uint32_t        pIx      = 0;

//   VkDeviceQueueCreateInfo GQ{};

//   GQ.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//   GQ.queueFamilyIndex = Queues::graphicsFamily;
//   GQ.queueCount       = 1;
//   GQ.pQueuePriorities = &priority;
//   GQ.flags            = 0;
//   GQ.pNext            = VK_NULL_HANDLE;

//   VkDeviceQueueCreateInfo PQ{};

//   PQ.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//   PQ.queueFamilyIndex = Queues::transferFamily;
//   PQ.queueCount       = 2;
//   PQ.pQueuePriorities = &priority;
//   PQ.flags            = 0;
//   PQ.pNext            = VK_NULL_HANDLE;

//   VkDeviceQueueCreateInfo queueCreateInfos[2] = { GQ, PQ };

//   static VkPhysicalDeviceVulkan13Features vk13F
//   {
//     .sType=VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_3_FEATURES,
//     .pNext=VK_NULL_HANDLE
//   };


//   static VkPhysicalDeviceVulkan12Features deviceVulkan12Features = {
//     .sType                           = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_VULKAN_1_2_FEATURES,
//     .pNext                           = &vk13F,
//     .descriptorBindingPartiallyBound = true,
//     .imagelessFramebuffer            = true,

//   };

//   static constexpr VkPhysicalDeviceFeatures deviceFeatures = {};

//   VkPhysicalDeviceFeatures2 deviceFeatures2 = { .sType    = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2,
//                                                 .pNext    = &deviceVulkan12Features,
//                                                 /* .features = deviceFeatures */ };


//   //.fillModeNonSolid(true) //dneeded to adres valditaion errors when using
//   // VK_POLIGYON_MODE_LINE or POINT .robustBufferAccess(true);
//   //                        .geometryShader(true);
//   //                        .pipelineStatisticsQuery(true)
//   //                        .alphaToOne(false);
//   vkGetPhysicalDeviceFeatures2( Queues::physicalDevice, &deviceFeatures2 );

//   // vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
//   VkDeviceCreateInfo createInfo      = {};
//   createInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
//   createInfo.pNext                   = &deviceFeatures2;
//   createInfo.queueCreateInfoCount    = 2;
//   createInfo.pQueueCreateInfos       = queueCreateInfos;
//   createInfo.ppEnabledExtensionNames = ( &VkUtilsXBase::deviceExtensions );
//   createInfo.enabledExtensionCount   = 1;
//   // createInfo.ppEnabledLayerNames=(validationLayers.data());
//   createInfo.pEnabledFeatures = nullptr;

//   if ( !deviceVulkan12Features.imagelessFramebuffer )
//   {
//      std::runtime_error( "Failed Enumeration!" );
//   }
//   if constexpr ( VkUtilsXBase::ENABLE_VALIDATION_LAYERS )
//   {
//     createInfo.ppEnabledLayerNames = &VkUtilsXBase::validationLayers;
//   }
//   VkUtilsXBase::checkCall( vkCreateDevice( Queues::physicalDevice, &createInfo, VK_NULL_HANDLE, &Queues::device ) );
//   volkLoadDevice( Queues::device );

//   VkUtilsXBase::clPPJI3<PFN_vkGetDeviceQueue>( createInfo.pQueueCreateInfos[0].queueFamilyIndex, "vkGetDeviceQueue", 0, &Queues::GraphicsQueue );
//   VkUtilsXBase::clPPJI3<PFN_vkGetDeviceQueue>( createInfo.pQueueCreateInfos[1].queueFamilyIndex, "vkGetDeviceQueue", 0, &Queues::TransferQueue[0] );
//   VkUtilsXBase::clPPJI3<PFN_vkGetDeviceQueue>( createInfo.pQueueCreateInfos[1].queueFamilyIndex, "vkGetDeviceQueue", 1, &Queues::TransferQueue[1] );
// }

void VkUtils2::cleanup()
{
 
}

VkFormat PipelineX::findDepthFormat()
{
  constexpr VkFormat formatCandidates[3] = { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
  VkFormatProperties props;

  for ( const VkFormat & format : formatCandidates )
  {
    vkGetPhysicalDeviceFormatProperties( Queues::physicalDevice, format, &props );

    const uint32_t i2 = props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;
    if ( i2 == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT /* && VK10.VK_IMAGE_TILING_OPTIMAL == VK_IMAGE_TILING_OPTIMAL*/ )
    {
      return format;
    }
  }

   std::runtime_error( "failed to find supported format!" );
}

inline void PipelineX::createRenderPasses()
{
  static const VkAttachmentDescription colorAttachment{
    .format         = VK_FORMAT_B8G8R8A8_SRGB,  // SwapChainSupportDetails::swapChainImageFormat,
    .samples        = VK_SAMPLE_COUNT_1_BIT,
    .loadOp         = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .storeOp        = VK_ATTACHMENT_STORE_OP_STORE,
    .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
    .initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED,
    .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  };
  static constexpr VkAttachmentReference colorAttachmentRef{ .attachment = 0, .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
  static constexpr VkSubpassDescription  subpass{ .pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS,
                                                  .colorAttachmentCount = 1,
                                                  .pColorAttachments    = &colorAttachmentRef };

  constexpr VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
    //   .flags=VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,
    .attachmentCount = 1,
    .pAttachments    = &colorAttachment,
    .subpassCount    = 1,
    .pSubpasses      = &subpass,
    // .dependencyCount=1,
    // .pDependencies=&dependency
  };

  VkUtilsXBase::clPPPI3<PFN_vkCreateRenderPass>( &vkRenderPassCreateInfo1, "vkCreateRenderPass", &SwapChainSupportDetails::renderPass );
}

inline void PipelineX::createGraphicsPipelineLayout()
{
  // Thankfully Dont; need to worry about compiling the Shader Files AnyMore due
  // to teh ability to premptively use the SPRI-V Compielr (e.g.GLSLC) prior to compile time...
  std::cout << ( "Setting up PipeLine" ) << "\n";

  // const VkShaderModule vertShaderModule = ShaderSPIRVUtils::compileShaderFile();
  // const VkShaderModule fragShaderModule = ShaderSPIRVUtils::compileShaderFile1();

  VkSpecializationInfo Vks =
  {

  };

  const VkPipelineShaderStageCreateInfo vertexStage = {
    .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
    .stage  = VK_SHADER_STAGE_VERTEX_BIT,
    .module = Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &SPV.VsMCI, "vkCreateShaderModule" ),
    .pName  = "main",

  }; 
  
  /* const VkPipelineShaderStageCreateInfo vertexStage2 = {
    .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
    .stage  = VK_SHADER_STAGE_VERTEX_BIT,
    .module = Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &SPV.VsMCI2, "vkCreateShaderModule" ),
    .pName  = "main",

  };  */

  const VkPipelineShaderStageCreateInfo fragStage = { .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                                                      .stage  = VK_SHADER_STAGE_FRAGMENT_BIT,
                                                      .module = Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &SPV.VsMCI2, "vkCreateShaderModule" ),
                                                      .pName  = "main" };

  const VkPipelineShaderStageCreateInfo shaderStages[] = { fragStage, vertexStage};

  static constexpr VkVertexInputBindingDescription VxL{ 0, ( 24 ), VK_VERTEX_INPUT_RATE_VERTEX };

  static constexpr VkVertexInputAttributeDescription attributeDescriptions[2]{
    { .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = OFFSET_POS },
    { .location = 2, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = OFFSETOF_COLOR },
    // { .location = 3, .binding = 0, .format = VK_FORMAT_R32G32_SFLOAT, .offset = 0 },
    // { .location = 4, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = sizeof(float) * 2}
  };

  static constexpr VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo = {
    .sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .vertexBindingDescriptionCount   = 1,
    .pVertexBindingDescriptions      = &VxL,
    .vertexAttributeDescriptionCount = sizeof( attributeDescriptions ) / sizeof( VkVertexInputAttributeDescription ),
    .pVertexAttributeDescriptions    = attributeDescriptions
  };

  static constexpr VkPipelineInputAssemblyStateCreateInfo inputAssembly = { .sType    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
                                                                            .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
                                                                            .primitiveRestartEnable = VK_FALSE };

  static constexpr VkViewport vkViewport{ .x = 0.0F, .y = 0.0F, .width = width, .height = height, .minDepth = UNormFlt, .maxDepth = 1.0F };

  static constexpr VkRect2D scissor{ .offset = { 0, 0 }, .extent{ width, height } };

  constexpr VkPipelineViewportStateCreateInfo vkViewPortState = {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, .viewportCount = 1, .pViewports = &vkViewport, .scissorCount = 1, .pScissors = &scissor
  };

  constexpr VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization = {
    .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .depthClampEnable        = VK_FALSE,
    .rasterizerDiscardEnable = VK_FALSE,
    .polygonMode             = VK_POLYGON_MODE_FILL,
    .cullMode                = VK_CULL_MODE_BACK_BIT,  // WARNING: VERY IMPORTANT!:
                                                       // Make sure the culling direction is correct
                                                       // as it applies even to 2DVecs/Fixed
                                                       // Function Runtime/Evaluated Shaders
                                                       // with no transforms and with fixed
                                                       // Const/Pre-Determined Runtime
                                                       // Variables
    .frontFace       = VK_FRONT_FACE_COUNTER_CLOCKWISE,
    .depthBiasEnable = VK_FALSE,
    .lineWidth       = 1.0F,
  };

  constexpr VkPipelineMultisampleStateCreateInfo multisampling = { .sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
                                                                   .rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT,
                                                                   .sampleShadingEnable   = VK_FALSE,
                                                                   .minSampleShading      = 1.0F,
                                                                   .pSampleMask           = VK_NULL_HANDLE,
                                                                   .alphaToCoverageEnable = VK_FALSE,
                                                                   .alphaToOneEnable      = VK_FALSE };

  constexpr VkPipelineDepthStencilStateCreateInfo depthStencil = {
    .sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .depthTestEnable       = VK_FALSE,
    .depthWriteEnable      = VK_FALSE,
    .depthCompareOp        = VK_COMPARE_OP_EQUAL,
    .depthBoundsTestEnable = VK_FALSE,
    .stencilTestEnable     = VK_FALSE,
  };
  static constexpr VkPipelineColorBlendAttachmentState colorBlendAttachment = {
    .blendEnable    = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,

  };
  constexpr VkPipelineColorBlendStateCreateInfo colorBlending = {
    .sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .logicOpEnable   = VK_FALSE,
    .logicOp         = VK_LOGIC_OP_COPY,
    .attachmentCount = 1,
    .pAttachments    = &colorBlendAttachment,

  };

  static constexpr VkPushConstantRange vkPushConstantRange{
    .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
    .offset     = 0,
    .size       = sizeof( mat4x ),
  };

  constexpr VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo = { .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                                      .setLayoutCount         = 1,
                                                                      .pSetLayouts            = &UniformBufferObject::descriptorSetLayout,
                                                                      .pushConstantRangeCount = 1,
                                                                      .pPushConstantRanges    = &vkPushConstantRange };

  // std::cout << ( "using pipeLine with Length: " ) << sizeof( SwapChainSupportDetails::swapChainImageViews );
  VkUtilsXBase::clPPPI3<PFN_vkCreatePipelineLayout>( &vkPipelineLayoutCreateInfo, "vkCreatePipelineLayout", &vkLayout );

  const VkGraphicsPipelineCreateInfo pipelineInfo{ .sType      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                                                   .stageCount = sizeof(shaderStages)/sizeof(VkPipelineShaderStageCreateInfo),
                                                   .pStages    = shaderStages,
                                                   // .pNext=VK_NULL_HANDLE,
                                                   .pVertexInputState   = &vkPipelineVertexInputStateCreateInfo,
                                                   .pInputAssemblyState = &inputAssembly,
                                                   .pViewportState      = &vkViewPortState,
                                                   .pRasterizationState = &VkPipeLineRasterization,
                                                   .pMultisampleState   = &multisampling,
                                                   .pDepthStencilState  = &depthStencil,
                                                   .pColorBlendState    = &colorBlending,
                                                   .layout              = vkLayout,
                                                   .renderPass          = SwapChainSupportDetails::renderPass,
                                                   .basePipelineIndex=-1};
  VkUtilsXBase::clPPPJI<PFN_vkCreateGraphicsPipelines>( &pipelineInfo, 1, "vkCreateGraphicsPipelines", &graphicsPipeline );
}

void PipelineX::recCmdBuffers()
{
    constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT) };

    constexpr VkRect2D renderArea = { .offset = { 0, 0 }, .extent = SwapChainSupportDetails::swapChainExtent };


  
  static constexpr VkDeviceSize offsets[] = { 0 };
  int i; 
  for ( const VkCommandBuffer & commandBuffer : commandBuffers )
  {VkRenderPassAttachmentBeginInfo RenderPassAttachments
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO,
    .attachmentCount = 1,
    .pAttachments = &SwapChainSupportDetails::swapChainImageViews[i]
  };

  static VkRenderPassBeginInfo renderPassInfo = {
    .sType           = ( VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),
    .pNext = &RenderPassAttachments,
    .renderPass      = ( SwapChainSupportDetails::renderPass ),
    .renderArea      = renderArea,
    // .clearValueCount = 1,
    // .pClearValues    = &clearValues2,
  };
  VkUtilsXBase::clPI<PFN_vkBeginCommandBuffer>(commandBuffer, "vkBeginCommandBuffer", &beginInfo1 );

    renderPassInfo.framebuffer = ( SwapChainSupportDetails::swapChainFramebuffers[i] );

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,graphicsPipeline );
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, &BuffersX::vertexBuffer, offsets );
    vkCmdBindIndexBuffer(commandBuffer, BuffersX::indexBuffer, 0, VK_INDEX_TYPE_UINT16 );
     
    vkCmdPushConstants(commandBuffer,vkLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, 64, &m4);

    vkCmdBindDescriptorSets( commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineX::vkLayout, 0, 1, &UniformBufferObject::descriptorSets, 0, nullptr );


    vkCmdDrawIndexed( commandBuffer, ( ( BuffersX::sizedsfIdx ) / 2 ), 1, 0, 0, 0 );

    vkCmdEndRenderPass( commandBuffer );
    VkUtilsXBase::clP<PFN_vkEndCommandBuffer>( commandBuffer, "vkEndCommandBuffer" );
    i++;
  }
}
void PipelineX::recCmdBuffer(int i)
{
    constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) };

    constexpr VkRect2D renderArea = { .offset = { 0, 0 }, .extent = SwapChainSupportDetails::swapChainExtent };

  // constexpr VkClearColorValue aa[] = { { { UNormFlt, UNormFlt, UNormFlt, 1.0F } } };
  // // constexpr VkClearDepthStencilValue aaa[] = { { { 0.0F, 1.0F } } };
  // constexpr VkClearValue clearValues = {
  //   .color = { { UNormFlt, UNormFlt, UNormFlt, 1.0F } }
  //   // .depthStencil = { 0.0F, static_cast<uint32_t>( 1.0F ) },
  // };
  constexpr VkClearValue clearValues2[2] = { { .color = { { PipelineX::UNormFlt, PipelineX::UNormFlt, PipelineX::UNormFlt, 1.0F } } }, { .color = { { PipelineX::UNormFlt, PipelineX::UNormFlt, PipelineX::UNormFlt, 1.0F } } } };

  static VkRenderPassBeginInfo renderPassInfo = {
    .sType           = ( VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),
    .renderPass      = ( SwapChainSupportDetails::renderPass ),
    .renderArea      = renderArea,
    .clearValueCount = 2,
    .pClearValues    = clearValues2,
  };
  static constexpr VkDeviceSize offsets[] = { 0 };
  renderer2::updateUniformBuffer(); 
  // for ( const VkCommandBuffer & commandBuffer : commandBuffers )
  {
  VkUtilsXBase::clPI<PFN_vkBeginCommandBuffer>(commandBuffers[i], "vkBeginCommandBuffer", &beginInfo1 );

    renderPassInfo.framebuffer = ( SwapChainSupportDetails::swapChainFramebuffers[i] );

    vkCmdPushConstants(commandBuffers[i],vkLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, 64, &m4);
    vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS,graphicsPipeline );
    vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, &BuffersX::vertexBuffer, offsets );
    vkCmdBindIndexBuffer(commandBuffers[i], BuffersX::indexBuffer, 0, VK_INDEX_TYPE_UINT16 );
    vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

    vkCmdDrawIndexed( commandBuffers[i], ( ( BuffersX::sizedsfIdx ) / 2 ), 1, 0, 0, 0 );
     

    // vkCmdBindDescriptorSets( PipelineX::commandBuffers[0], VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineX::vkLayout, 0, 1, &UniformBufferObject::descriptorSets, 0, nullptr );


    vkCmdEndRenderPass( commandBuffers[i] );

    VkUtilsXBase::clP<PFN_vkEndCommandBuffer>( commandBuffers[i], "vkEndCommandBuffer" );
    i++;
  }
}
inline void PipelineX::createCommandBuffers()
{
  const VkCommandBufferAllocateInfo allocateInfo{ .sType              = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
                                                  .commandPool        = ( Queues::commandPool ),
                                                  .level              = ( VK_COMMAND_BUFFER_LEVEL_PRIMARY ),
                                                  .commandBufferCount = sizeof( commandBuffers ) / sizeof( VkCommandBuffer ) };
  std::cout << allocateInfo.commandBufferCount << "Command Buffers"
            << "\n";
  VkUtilsXBase::clPPI3<PFN_vkAllocateCommandBuffers>( &allocateInfo, "vkAllocateCommandBuffers", commandBuffers );


  /*   VkRenderPassAttachmentBeginInfo attachmentsbeginInfo{ .sType =
     VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO, .attachmentCount = 1, .pAttachments =
                                                            &SwapChainSupportDetails::swapChainImageViews[0] };

   */

  // {
  //   .color        = { UNormFlt, UNormFlt, UNormFlt, 1.0F },
  //   .depthStencil = { 0.0F, static_cast<uint32_t>( 1.0F ) },
  // },

  
  static auto i = 0;
  vkMapMemory( Queues::device, UniformBufferObject::uniformBuffersMemory, 0, 64, 0, (void**)&BuffersX::data );
  
  m4.loadAligned( &viewproj );  // NoS ure on best order............................................................->
    m4.toAddress(BuffersX::data);
 
    recCmdBuffers();
   
  
}

void vkMappedCopy(VkDeviceMemory &Staging, size_t size, const auto* srcVectBuffs, __m256 *data, VkBuffer& Temp)
{
  // void* autoMemAllocs;
    memcpy(data, srcVectBuffs, size );
  
    BuffersX::copyBuffer(Temp, size);
}
inline void BuffersX::setupBuffers()
{
  auto x1 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  auto p1 = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( p1, vertexBuffer, x1, sizedsf, vertexBufferMemory );
  // createSetBuffer( p1, vertexBufferTemp, x1, sizeof(Temp), vertexBufferMemorytemp );

  VkBufferUsageFlagBits x2 = { VK_BUFFER_USAGE_TRANSFER_SRC_BIT };
  constexpr auto        p  = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( p, Bufferstaging, x2, sizedsf, stagingBufferMemory );

  auto x3 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, x3, sizedsfIdx, indexBufferMemory );
  vkMapMemory( Queues::device, stagingBufferMemory, 0, 1024, 0, (void**)&data );
  {

  vkMappedCopy(stagingBufferMemory, sizedsf, vectBuf, data, vertexBuffer);
  vkMappedCopy(stagingBufferMemory, sizedsfIdx, idxBuf, data, indexBuffer);
  }  
  vkUnmapMemory( Queues::device, stagingBufferMemory );

  // BuffersX::copyBuffer( vertexBufferTemp, sizeof(Temp) );

 
}

inline void BuffersX::createSetBuffer(
  VkMemoryPropertyFlagBits properties, VkBuffer & currentBuffer, VkBufferUsageFlagBits usage, size_t sized, VkDeviceMemory & vertexBufferMemory )
{
  const VkBufferCreateInfo allocateInfo = {
    .sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .pNext       = nullptr,
    .size        = sized,
    .usage       = usage,
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
  };

  VkUtilsXBase::clPPPI3<PFN_vkCreateBuffer>( &allocateInfo, "vkCreateBuffer", &currentBuffer );

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements( Queues::device, currentBuffer, &memRequirements );

  VkMemoryAllocateInfo allocateInfo1 = {
    .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext           = nullptr,
    .allocationSize  = memRequirements.size,
    .memoryTypeIndex = findMemoryType( memRequirements.memoryTypeBits, properties ),
  };
  //
  VkUtilsXBase::clPPPI3<PFN_vkAllocateMemory>( &allocateInfo1, "vkAllocateMemory", &vertexBufferMemory );

  VkUtilsXBase::checkCall( vkBindBufferMemory( Queues::device, currentBuffer, vertexBufferMemory, 0 ) );
}

inline uint32_t BuffersX::findMemoryType( uint32_t typeFilter, VkMemoryPropertyFlagBits properties )
{
  // VkPhysicalDeviceMemoryProperties memProperties = {};
  // vkGetPhysicalDeviceMemoryProperties( physicalDevice, &memProperties );
  for ( uint32_t i = 0; i < memProperties.memoryTypeCount; i++ )
  {
    if ( /* ( typeFilter & ( 1U << i ) ) != 0 &&  */( memProperties.memoryTypes[i].propertyFlags & properties ) == properties )
    {
      return i;
    }
  }

  std::runtime_error( "Failed to find suitable memory type" );
}

inline void BuffersX::createVkEvents()
{
  VkEventCreateInfo vkEventCreateInfo = {};
  vkEventCreateInfo.sType             = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
  vkEventCreateInfo.pNext             = nullptr;

  VkUtilsXBase::clPPPI3<PFN_vkCreateEvent>( &vkEventCreateInfo, "vkCreateEvent", &vkEvent );
}

inline void BuffersX::copyBuffer( VkBuffer & dst, const size_t sized )
{
  Queues::beginSingleTimeCommands();
  const VkBufferCopy vkBufferCopy{
    .srcOffset = 0,
    .dstOffset = 0,
    .size      = sized,
  };
  vkCmdCopyBuffer( Queues::commandBuffer, Bufferstaging, dst, 1, &vkBufferCopy );
  Queues::endSingleTimeCommands();
}

inline constexpr void UniformBufferObject::createDescriptorSetLayout()
  {
    // m5.loadAligned( &viewproj2 );

    {
      constexpr VkDescriptorSetLayoutBinding bindings = {
        .binding = 0, .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, .descriptorCount = 1, .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
        /* { .binding = 1,
          .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT} */
      };
      // samplerLayoutBinding

      const VkDescriptorSetLayoutCreateInfo a{
        .sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings    = &bindings,

      };
      VkUtilsXBase::clPPPI3<PFN_vkCreateDescriptorSetLayout>( &a, "vkCreateDescriptorSetLayout", &UniformBufferObject::descriptorSetLayout );
    }
  }

  inline void UniformBufferObject::createUniformBuffers()
  {
    for ( int i = 0; i < 1; i++ )
    {
      BuffersX::createSetBuffer( static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT ),
                                 UniformBufferObject::uniformBuffers,
                                 VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                 Sized,
                                 uniformBuffersMemory );
    }
  }

  inline void UniformBufferObject::createDescriptorPool()
  {
    {
      static constexpr VkDescriptorPoolSize poolSize{

        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, .descriptorCount = 1

      };

      static constexpr VkDescriptorPoolCreateInfo poolCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, .pNext = nullptr, .maxSets = 1, .poolSizeCount = 1, .pPoolSizes = &poolSize
      };
      ( vkCreateDescriptorPool( Queues::device, &poolCreateInfo, nullptr, &descriptorPool ) );
    }
  }

  inline VkSampler createTextureSampler()
  {
    constexpr VkSamplerCreateInfo samplerInfo{
      .sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
      .magFilter               = VK_FILTER_NEAREST,
      .minFilter               = VK_FILTER_NEAREST,
      .mipmapMode              = VK_SAMPLER_MIPMAP_MODE_NEAREST,
      .addressModeU            = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeV            = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeW            = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .mipLodBias              = 0,
      .anisotropyEnable        = false,
      .compareEnable           = false,
      .compareOp               = VK_COMPARE_OP_ALWAYS,
      .minLod                  = 0,
      .maxLod                  = 0,
      .borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
      .unnormalizedCoordinates = false,
    };
    VkSampler sampler = nullptr;
    VkUtilsXBase::clPPPI3<PFN_vkCreateSampler>( &samplerInfo, "vkCreateSampler", &sampler );
    return sampler;
    // nmemFree(samplerInfo.address());
  }

  inline void UniformBufferObject::createDescriptorSets()
  {
    {
      const VkDescriptorSetAllocateInfo allocInfo{ .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                                                   .pNext              = nullptr,
                                                   .descriptorPool     = descriptorPool,
                                                   .descriptorSetCount = 1,
                                                   .pSetLayouts        = &descriptorSetLayout };

      vkAllocateDescriptorSets( Queues::device, &allocInfo, &descriptorSets );

      {
        VkDescriptorBufferInfo bufferInfo{ .buffer = uniformBuffers, .offset = 0, .range = ( Sized ) };

        // const VkDescriptorImageInfo imageInfo{
        //         .sampler=createTextureSampler(),
        //         .imageView=textureImageView,
        //         .imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        // };

        VkWriteDescriptorSet descriptorWrites{

          .sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
          .dstSet          = descriptorSets,
          .dstBinding      = 0,
          .dstArrayElement = 0,
          .descriptorCount = 1,
          .descriptorType  = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
          .pBufferInfo     = &bufferInfo,

          /*  */
        };
        vkUpdateDescriptorSets( Queues::device, 1, &descriptorWrites, 0, nullptr );
      }
    }
  }


inline void Queues::createCommandPool()
{
  constexpr VkCommandPoolCreateInfo poolInfo = {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .queueFamilyIndex = 0,
  };
  commandPool = clPPPI3A<VkCommandPool, PFN_vkCreateCommandPool>( &poolInfo, "vkCreateCommandPool" );
  constexpr VkCommandPoolCreateInfo poolInfo2{
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .queueFamilyIndex = 1,
  };
  commandPool2 = clPPPI3A<VkCommandPool, PFN_vkCreateCommandPool>( &poolInfo2, "vkCreateCommandPool" );
  if ( commandBuffer == nullptr )
  {
    const VkCommandBufferAllocateInfo allocateInfo{
      .sType              = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
      .pNext              = VK_NULL_HANDLE,
      .commandPool        = ( Queues::commandPool2 ),
      .level              = ( VK_COMMAND_BUFFER_LEVEL_PRIMARY ),
      .commandBufferCount = ( 1 ),
    };

    VkUtilsXBase::clPPI3<PFN_vkAllocateCommandBuffers>( &allocateInfo, "vkAllocateCommandBuffers", &commandBuffer );
  }
}

inline void Queues::beginSingleTimeCommands()
{
  VkUtilsXBase::clPI<PFN_vkBeginCommandBuffer>( commandBuffer, "vkBeginCommandBuffer", &vkCommandBufferBeginInfo );
}

inline void Queues::endSingleTimeCommands()
{
  VkUtilsXBase::clP<PFN_vkEndCommandBuffer>( commandBuffer, "vkEndCommandBuffer" );

  a = ( a ^ 1 );
  vkQueueSubmit( TransferQueue[a], 1, &submitInfo1, VK_NULL_HANDLE );
  vkQueueWaitIdle( TransferQueue[a] );
  vkResetCommandPool( device, ( commandPool2 ), VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT );
}
