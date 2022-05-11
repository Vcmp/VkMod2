#pragma once
#include "Pipeline2.hpp"
#include "mat4x.hpp"

//I will have to assume that this works without needing explicit includes due to forward declarations





/*
 trick to use builtins+Attributes to treat a blob of memory as a vector type which compiles more cleanly into slightly better asm with vmovps (At least with Clang)
 static __int256 *__restrict__ ax = reinterpret_cast<__int256 *>(&ubo);
*/
typedef size_t __int256 __attribute__( ( __vector_size__( sizeof( mat4x ) ), __aligned__( 64 ) ) );

static struct __attribute__( ( internal_linkage, __vector_size__( 32 ), __aligned__( 32 ) ) ) renderer2// : Queues
{
      static constexpr VkSemaphoreCreateInfo vkCreateCSemaphore{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, .pNext = nullptr };
  renderer2(): AvailableSemaphore(Vks::doPointerAllocSml<VkSemaphore>( &vkCreateCSemaphore, vkCreateSemaphore))
  {


  }
  static constexpr float ah = 90.0F * static_cast<float>( 0.01745329251994329576923690768489 );
  static constexpr void  setupRenderDraw() __attribute__( ( cold ) );
  void            drawFrame();

  // static void updateUniformBuffer() __attribute__( ( __aligned__( 32 ), hot, flatten, preserve_all ) );
private:
  constexpr static void memcpy2( __int256 *, __int256 const *, size_t ) __attribute__( ( __aligned__( 32 ), hot, flatten, preserve_all ) );
  


  const VkSemaphore AvailableSemaphore;

  static constinit inline uint32_t               currentFrame;
  static constexpr const uint32_t                TmUt = 1000000000;
  static constexpr VkPresentInfoKHR VkPresentInfoKHR1{ .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                                                    // .pWaitSemaphores=&FinishedSemaphore,
                                                                    .swapchainCount = 1,
                                                                    .pSwapchains    = &SW.swapChain,
                                                                    .pImageIndices  = &currentFrame,
                                                                    .pResults       = nullptr };
  static constexpr VkPipelineStageFlags          waitStages = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  VkSubmitInfo           info{
              .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
              .waitSemaphoreCount = 1,
              .pWaitSemaphores    = &AvailableSemaphore,
              .pWaitDstStageMask  = &waitStages,
              .commandBufferCount = 1,
  };
}R2;


void renderer2::drawFrame()
{
  // m4.loadAligned( &m5 );
  
  vkAcquireNextImageKHR( VKI.device, SW.swapChain, -1, R2.AvailableSemaphore, nullptr, &currentFrame );
  // __builtin_prefetch( BuffersX::data );
  // __builtin_prefetch( &viewproj2x );
//  textTemp2.voidrecComBufferSub(currentFrame);
  // renderer2::updateUniformBuffer(); 

    // vkResetCommandPool(Queues::device, Queues::commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);


    // PipelineX::recCmdBuffer(currentFrame);

      R2.info.pCommandBuffers =&PX2.commandBuffer[currentFrame];
    vkQueueSubmit( VKI.GraphicsQueue, 1, &R2.info, nullptr );
  // }
  


  //  info.pWaitSemaphores = &AvailableSemaphore;

 vkQueuePresentKHR( VKI.GraphicsQueue, &VkPresentInfoKHR1 );

  currentFrame = currentFrame + __builtin_parity( Frames );
}