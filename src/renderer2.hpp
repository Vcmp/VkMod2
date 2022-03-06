#pragma once

#include "VkUtils2.ixx"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"

#include <immintrin.h>

/*
 trick to use builtins+Attributes to treat a blob of memory as a vector type
 which compiles more cleanly into slightly better asm with vmovps (At least
 with Clang)
 static __int256 *__restrict__ ax = reinterpret_cast<__int256 *>(&ubo);
*/
uint64_t       cc = 0;
typedef size_t __int256 __attribute__( ( __vector_size__( sizeof( m4 ) ), __aligned__( 64 ) ) );

struct /* __attribute__( ( internal_linkage, __vector_size__( 32 ), __aligned__( 32 ) ) ) */ renderer2
{
  static constexpr float ah = 90.0F * static_cast<float>( 0.01745329251994329576923690768489 );
  static constexpr void  setupRenderDraw() __attribute__( ( cold ) );
  static void            drawFrame() __attribute__( ( hot, flatten, preserve_most ) );

private:
  constexpr static void memcpy2( __int256 *, __int256 const *, size_t ) __attribute__( ( __aligned__( 32 ), hot, flatten, preserve_all ) );
  ;

  static void updateUniformBuffer() __attribute__( ( __aligned__( 32 ), hot, flatten, preserve_all ) );

  static constinit inline VkSemaphore AvailableSemaphore;

  static constinit inline uint32_t               currentFrame;
  static constexpr const uint32_t                TmUt = 1000000000;
  static inline constinit const VkPresentInfoKHR VkPresentInfoKHR1{ .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                                                    // .pWaitSemaphores=&FinishedSemaphore,
                                                                    .swapchainCount = 1,
                                                                    .pSwapchains    = &swapChain,
                                                                    .pImageIndices  = &currentFrame,
                                                                    .pResults       = nullptr };
  static constexpr VkPipelineStageFlags          waitStages = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  static constinit inline VkSubmitInfo           info{
              .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
              .waitSemaphoreCount = 1,
              .pWaitSemaphores    = &AvailableSemaphore,
              .pWaitDstStageMask  = &waitStages,
              .commandBufferCount = 1,
  };
};

inline constexpr void renderer2::setupRenderDraw()
{
  constexpr VkSemaphoreCreateInfo vkCreateCSemaphore{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, .pNext = nullptr };

  ( AvailableSemaphore = Queues::clPPPI3A<VkSemaphore, PFN_vkCreateSemaphore>( &vkCreateCSemaphore, "vkCreateSemaphore" ) );
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
  vkAcquireNextImageKHR( Queues::device, swapChain, -1, AvailableSemaphore, nullptr, &currentFrame );
  // __builtin_prefetch( BuffersX::data );
  // __builtin_prefetch( &viewproj2x );
  updateUniformBuffer();
  info.pCommandBuffers = &commandBuffers[currentFrame];

  vkQueueSubmit( Queues::GraphicsQueue, 1, &info, nullptr );

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
  asm volatile( "rep movsb" : "=D"( d ), "=S"( s ), "=c"( n ) : "0"( d ), "1"( s ), "2"( n ) : "memory" );
  return d;
}
inline void renderer2::updateUniformBuffer()
{
  // const float time = static_cast<float>( glfwGetTime() ) * ah;

  static constinit float c;
  static constinit float s;
  static constexpr float xs = 1;
  sincosf( glfwGetTime() * ah, &c, &s );
  __builtin_prefetch( BuffersX::data, 1, 3 );
  // const float ax = glfwGetTime() * ah;

  // rot = viewproj * glm::rotate( glm::identity<glm::mat4>(), ax, glm::vec3( 1, 0, 0 ) );

  // const __m128 ones = _mm_broadcast_ss( &xs );
  // _mm256_storeu2_m128i();

  // const __m256 aa = viewproj2x;
  // const __m256 osx2    = _mm256_set_ps( c, c, c, c, 0, 0, 0, 0 );
  const __m128 osx2    = _mm_broadcast_ss( &c );
  const __m256 osx     = _mm256_broadcast_ss( &c );
  const __m256 osxyzsZ = _mm256_broadcast_ss( &s );
  // const __m256 XORS    = _mm256_sub_ps( _mm256_xor_ps( osx, osx2 ), osx2 );
  const __m128 XORS = _mm_sub_ps( _mm_sub_ps( osx2, osx2 ), osx2 );

  const __m256 a = viewproj2x * _mm256_insertf128_ps( osx, XORS, 1 );
  // _mm256_xor_ps( osx, axvZXLI );
  // _mm256_storeu2_m128( &c, &c2, a );

  const auto x = _mm256_fmaddsub_ps( viewproj2x, osxyzsZ, a );

  _mm256_store_ps( reinterpret_cast<float *>( BuffersX::data ), x );
  _mm256_zeroupper();

  // memcpy( BuffersX::data, &x, sizeof( x ) );
}