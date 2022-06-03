#pragma once
#include "Pipeline2.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "mat4x.hpp"

#include <array>
#include <initializer_list>
#include <vulkan/vulkan_core.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_common.hpp>
#include <glm/ext/matrix_clip_space.hpp>

//I will have to assume that this works without needing explicit includes due to forward declarations



// auto genSubmits(const VkSemaphore &AvailableSemaphore)
// {
//     static constexpr VkPipelineStageFlags          waitStages = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;

//   const  VkSubmitInfo           info{
//               .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
//               .waitSemaphoreCount = 1,
//               .pWaitSemaphores    = &AvailableSemaphore,
//               .pWaitDstStageMask  = &waitStages,
//               .commandBufferCount = 1,
//               .pCommandBuffers= &PX2.commandBuffer[0]
//   };
//   const VkSubmitInfo           info1{
//               .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
//               .waitSemaphoreCount = 1,
//               .pWaitSemaphores    = &AvailableSemaphore,
//               .pWaitDstStageMask  = &waitStages,
//               .commandBufferCount = 1,
//               .pCommandBuffers= &PX2.commandBuffer[1]
//   };
//   const VkSubmitInfo           info2{
//               .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
//               .waitSemaphoreCount = 1,
//               .pWaitSemaphores    = &AvailableSemaphore,
//               .pWaitDstStageMask  = &waitStages,
//               .commandBufferCount = 1,
//               .pCommandBuffers= &PX2.commandBuffer[2]
//   };
//   const std::array<VkSubmitInfo, 3> aa = { info, info1, info2};
//   return aa;
// }

/*
 trick to use builtins+Attributes to treat a blob of memory as a vector type which compiles more cleanly into slightly better asm with vmovps (At least with Clang)
 static __int256 *__restrict__ ax = reinterpret_cast<__int256 *>(&ubo);
*/
typedef size_t __int256 __attribute__( ( __vector_size__( sizeof( mat4x ) ), __aligned__( 64 ) ) );

static const struct __attribute__( ( internal_linkage, __vector_size__( 32 ), __aligned__( 32 ) ) ) renderer2// : Queues
{
      static constexpr VkSemaphoreCreateInfo vkCreateCSemaphore{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, .pNext = nullptr };

      static constexpr VkFenceCreateInfo vkFenceCreateInfo{.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, .pNext=nullptr};
      
  static constexpr float ah = 90.0F * static_cast<float>( 0.01745329251994329576923690768489 );
  static constexpr void  setupRenderDraw() __attribute__( ( cold ) );
  void            drawFrame(std::initializer_list<VkCommandBuffer>) const;

  // static void updateUniformBuffer() __attribute__( ( __aligned__( 32 ), hot, flatten, preserve_all ) );
  static constinit inline uint32_t               currentFrame;

  constexpr static void memcpy2( __int256 *, __int256 const *, size_t ) __attribute__( ( __aligned__( 32 ), hot, flatten, preserve_all ) );
  


  const std::array<VkSemaphore, Frames> AvailableSemaphore = {Vks::doPointerAlloc5<VkSemaphore>( &vkCreateCSemaphore, vkCreateSemaphore), Vks::doPointerAlloc5<VkSemaphore>( &vkCreateCSemaphore, vkCreateSemaphore), Vks::doPointerAlloc5<VkSemaphore>( &vkCreateCSemaphore, vkCreateSemaphore)};
  const std::array<VkSemaphore, Frames> FinishedSemaphore = {Vks::doPointerAlloc5<VkSemaphore>( &vkCreateCSemaphore, vkCreateSemaphore), Vks::doPointerAlloc5<VkSemaphore>( &vkCreateCSemaphore, vkCreateSemaphore), Vks::doPointerAlloc5<VkSemaphore>( &vkCreateCSemaphore, vkCreateSemaphore)};
  const std::array<VkFence, Frames> fence = {Vks::doPointerAlloc5<VkFence>( &vkFenceCreateInfo, vkCreateFence), Vks::doPointerAlloc5<VkFence>( &vkFenceCreateInfo, vkCreateFence), Vks::doPointerAlloc5<VkFence>( &vkFenceCreateInfo, vkCreateFence)};

  static constexpr const uint32_t                TmUt = 1000000000;

 
  // const std::array<VkSubmitInfo, 3> aa = genSubmits(AvailableSemaphore);
}R2;

