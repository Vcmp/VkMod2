#pragma once

#include "Pipeline.hpp"
#include "UniformBufferObject.hpp"

// #include "mat4x.hpp"

// trick to use builtins+Attributes to treat a blob of memory as a vector type
// which compiles more cleanly into slightly better asm with vmovps (At least
// with Clang)
// static __int256 *__restrict__ ax = reinterpret_cast<__int256 *>(&ubo);

typedef size_t __int256 __attribute__( ( __vector_size__( sizeof( m4 ) ), __aligned__( 64 ) ) );

// const PFN_vkAcquireNextImageKHR * vckANI =
//   VkUtilsXBase::getAddrFuncPtr<PFN_vkAcquireNextImageKHR>( "vkAcquireNextImageKHR" );
struct /* __attribute__( ( internal_linkage, __vector_size__( 32 ), __aligned__( 32 ) ) ) */ renderer2
{
  static constexpr float ah = glm::radians( 90.0F );
  static constexpr void  setupRenderDraw() __attribute__( ( cold ) );
  static void            drawFrame() __attribute__( ( hot, flatten, preserve_most ) );

private:
  constexpr static void memcpy2( __int256 *, __int256 const *, size_t )
    __attribute__( ( __aligned__( 32 ), hot, flatten, preserve_all ) );
  ;

  static void updateUniformBuffer();  // __attribute__( ( __aligned__( 32 ), hot, flatten, preserve_all ) );

  static inline VkSemaphore AvailableSemaphore;

  static inline uint32_t                   currentFrame;
  static constexpr uint32_t                TmUt = 1000000000;
  static inline constexpr VkPresentInfoKHR VkPresentInfoKHR1{ .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                                              // .pWaitSemaphores=&FinishedSemaphore,
                                                              .swapchainCount = 1,
                                                              .pSwapchains    = &swapChain,
                                                              .pImageIndices  = &currentFrame,
                                                              .pResults       = nullptr };
  static constexpr VkPipelineStageFlags    waitStages = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  static inline VkSubmitInfo               info{
                  .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                  .waitSemaphoreCount = 1,
                  .pWaitSemaphores    = &AvailableSemaphore,
                  .pWaitDstStageMask  = &waitStages,
                  .commandBufferCount = 1,
  };
};

inline constexpr void renderer2::setupRenderDraw()
{
  constexpr VkSemaphoreCreateInfo vkCreateCSemaphore{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                                                      .pNext = nullptr };

  ( AvailableSemaphore = VkUtilsXBase::clPPPI2<VkSemaphore>( &vkCreateCSemaphore, "vkCreateSemaphore" ) );
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
  VkUtilsXBase::checkCall(
    vkAcquireNextImageKHR( Queues::device, swapChain, TmUt, AvailableSemaphore, VK_NULL_HANDLE, &currentFrame ) );

  updateUniformBuffer();
  info.pCommandBuffers = &PipelineX::commandBuffers[currentFrame];

  VkUtilsXBase::checkCall( vkQueueSubmit( Queues::GraphicsQueue, 1, &info, VK_NULL_HANDLE ) );

  //  info.pWaitSemaphores = &AvailableSemaphore;

  VkUtilsXBase::checkCall( vkQueuePresentKHR( Queues::GraphicsQueue, &VkPresentInfoKHR1 ) );

  currentFrame = ( currentFrame + 1 ) % VkUtilsXBase::Frames;
}

constexpr inline void
  renderer2::memcpy2( __int256 * __restrict__ _Dst, __int256 const * __restrict__ _Src, size_t _MaxCount )
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
  const float time = static_cast<float>( glfwGetTime() ) * ah;

  // ubo.model = glm::rotate( viewproj, time, glm::vec3( 0.0F, 0.0F, 1.0F ) );
  //  ubo.proj[1][1] *= -1;
  //     __m512 a =(__m512)&data+0x200;
  // const float ax[16] = {
  //   time, time, time, time, time, time, time, time, time, time, time, time, time, time, time, time
  // };
  // const float ax2[16] = { time * 2, time * 2, time * 2, time * 2, time * 2, time * 2, time * 2, time * 2,
  //                         time * 2, time * 2, time * 2, time * 2, time * 2, time * 2, time * 2, time * 2 };
  // m4.loadTmp( ax2 );
  // m5.loadTmp( ax2 );
  // m4.loadAligned( &ubo.model );

  m4.rotateL( time /* , glm::vec3( 0.0F, 0.0F, 1.0F ) */ );
  // m4.domatFMA( m5 );
  /*Should Ideally Peristently map the Uniberform buffer allocation instead
   *Howver don't currently know of a method to carry this out in C++ without
   *Java Unsafe API Black Magic (Write to mem addresses dierctly without Type
   *checking)
   */
  // vkMapMemory(device, UniformBufferObject::uniformBuffersMemory, 0,
  // UniformBufferObject::Sized, 0, &data);
  {
    // memcpy2( reinterpret_cast<__int256 *>( data ), reinterpret_cast<__int256 *>( &m4 ), sizeof( m4 ) );
    // memcpy2( reinterpret_cast<__int256 *>( data ), reinterpret_cast<__int256 *>( &m4 ), UniformBufferObject::Sized );
  }
  // vkUnmapMemory(device, UniformBufferObject::uniformBuffersMemory);
  //  data=nullptr;
}