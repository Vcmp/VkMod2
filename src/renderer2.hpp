#pragma once

#include "Pipeline.hpp"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "src/UniformBufferObject.hpp"
#include "src/mat4x.hpp"

// trick to use builtins+Attributes to treat a blob of memory as a vector type
// which compiles more cleanly into slightly better asm with vmovps (At least
// with Clang)
typedef size_t __int256 __attribute__( ( __vector_size__( UniformBufferObject::Sized ), __aligned__( 256 ) ) );
// static __int256 *__restrict__ ax = reinterpret_cast<__int256 *>(&ubo);

constexpr float ah = glm::radians( 90.0F );
struct renderer2
{
  static void setupRenderDraw();
  static void drawFrame();

  constexpr static void memcpy2( __int256 *, __int256 const *, size_t );
  static void           updateUniformBuffer();

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
  static inline constexpr VkSemaphoreCreateInfo vkCreateCSemaphore{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                                                                    .pNext = nullptr };
};

inline void renderer2::setupRenderDraw()
{
  ( clPPPI( &vkCreateCSemaphore, "vkCreateSemaphore", &AvailableSemaphore ) );
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
  checkCall( vkAcquireNextImageKHR( device, swapChain, TmUt, AvailableSemaphore, VK_NULL_HANDLE, &currentFrame ) );

  updateUniformBuffer();
  info.pCommandBuffers = &PipelineX::commandBuffers[currentFrame];

  checkCall( vkQueueSubmit( Queues::GraphicsQueue, 1, &info, VK_NULL_HANDLE ) );

  //  info.pWaitSemaphores = &AvailableSemaphore;

  checkCall( vkQueuePresentKHR( Queues::GraphicsQueue, &VkPresentInfoKHR1 ) );

  currentFrame = ( currentFrame + 1 ) % Frames;
}

constexpr inline void
  renderer2::memcpy2( __int256 * __restrict__ _Dst, __int256 const * __restrict__ _Src, size_t _MaxCount )
{
  *_Dst = *_Src;
}

inline void renderer2::updateUniformBuffer()
{
  float time = glfwGetTime() * ah;

  ubo.model = viewproj * glm::rotate( glm::identity<glm::mat4>(), time, glm::vec3( 0.0F, 0.0F, 1.0F ) );
  //  ubo.proj[1][1] *= -1;
  //     __m512 a =(__m512)&data+0x200;
  m4.loadAligned( &ubo.model );
  /*Should Ideally Peristently map the Uniberform buffer allocation instead
   *Howver don't currently know of a method to carry this out in C++ without
   *Java Unsafe API Black Magic (Write to mem addresses dierctly without Type
   *checking)
   */
  // vkMapMemory(device, UniformBufferObject::uniformBuffersMemory, 0,
  // UniformBufferObject::Sized, 0, &data);
  {
    memcpy2( static_cast<__int256 *>( data ), reinterpret_cast<__int256 *>( &m4 ), UniformBufferObject::Sized );
  }
  // vkUnmapMemory(device, UniformBufferObject::uniformBuffersMemory);
  //  data=nullptr;
}