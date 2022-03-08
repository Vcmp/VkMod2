#pragma once

#include "VkUtils2.ixx"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"

#include <cmath>
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
  static void            drawFrame();

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
