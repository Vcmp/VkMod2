#pragma once
#include "SwapChain.hpp"
#include "VKI.hpp"

#include "mat4x.hpp"

#include <array>
#include <vulkan/vulkan_core.h>

template <typename type>
constexpr std::array<type, Frames> doSet( auto &s, auto f)
{
   
   std::array<type, Frames> aa;

   for(type & i: aa)
   {
     i=Vks::doPointerAlloc5<type>( &s, f);
   }
  return aa;
}

/*
 trick to use builtins+Attributes to treat a blob of memory as a vector type which compiles more cleanly into slightly better asm with vmovps (At least with Clang)
 static __int256 *__restrict__ ax = reinterpret_cast<__int256 *>(&ubo);
*/
typedef size_t __int256 __attribute__( ( __vector_size__( sizeof( mat4x ) ), __aligned__( 64 ) ) );

struct renderer2// : Queues
{
      static constexpr VkSemaphoreCreateInfo vkCreateCSemaphore{ .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, .pNext = nullptr };

      static constexpr VkFenceCreateInfo vkFenceCreateInfo{.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, .pNext=nullptr};
      
  static constexpr float ah = 90.0F * static_cast<float>( 0.01745329251994329576923690768489 );
  static constexpr void  setupRenderDraw() __attribute__( ( cold ) );
  [[gnu::pure, gnu::const, gnu::regcall, clang::preserve_all, gnu::hot]] void            drawFrame(const VkInit&, const SwapChain&, std::initializer_list<VkCommandBuffer>) const;

  static constinit inline uint32_t               currentFrame;

  constexpr static void memcpy2( __int256 *, __int256 const *, size_t ) __attribute__( ( __aligned__( 32 ), hot, flatten, preserve_all ) );
  


  std::array<VkSemaphore, Frames> AvailableSemaphore = doSet<VkSemaphore>(vkCreateCSemaphore, vkCreateSemaphore);
  std::array<VkSemaphore, Frames> PresentSemaphore = doSet<VkSemaphore>(vkCreateCSemaphore, vkCreateSemaphore);
  std::array<VkSemaphore, Frames> FinishedSemaphore = doSet<VkSemaphore>(vkCreateCSemaphore, vkCreateSemaphore);
  std::array<VkFence, Frames> fence = doSet<VkFence>(vkFenceCreateInfo, vkCreateFence);

  static constexpr const uint32_t                TmUt = 1000000000;

 
} __attribute__((aligned(128)));

