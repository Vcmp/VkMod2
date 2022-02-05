#pragma once

#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Pipeline.hpp"
#include "src/UniformBufferObject.hpp"


//trick to use builtins+Attributes to treat a blob of memory as a vector type which compiles more cleanly into slightly better asm with vmovps (At least with Clang)
typedef size_t __int256 __attribute__((__vector_size__(UniformBufferObject::Sized), __aligned__(256)));
    static __int256* __restrict__ ax=(__int256*)&ubo;

    constexpr float ah=glm::radians(90.0f);
constexpr static struct renderer2 
{
    
    static void setupRenderDraw();
    static void drawFrame();

    constexpr static void memcpy2(__int256 * __restrict__,   __int256 const* __restrict__ ,size_t);
    static void updateUniformBuffer();
    

    static inline VkSemaphore AvailableSemaphore;
   
    static inline uint32_t currentFrame;
    static constexpr uint32_t TmUt = 1000000000;
    static inline constexpr VkPresentInfoKHR VkPresentInfoKHR1
    {
                    .sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                    // .pWaitSemaphores=&FinishedSemaphore,
                    .swapchainCount=1,
                    .pSwapchains= &swapChain,
                    .pImageIndices=&currentFrame,
                    .pResults=nullptr            
    };
    static constexpr VkPipelineStageFlags  waitStages = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT; 
    static inline VkSubmitInfo info
    {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &AvailableSemaphore,
        .pWaitDstStageMask = &waitStages,
        .commandBufferCount = 1,
    };
    static inline constexpr VkSemaphoreCreateInfo vkCreateCSemaphore{
                        .sType=VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                        .pNext=nullptr
                        };
} inline r2;

 
   
 

inline void  renderer2::setupRenderDraw()
{
                        
                        

                        (pstrct.clPPPI(&vkCreateCSemaphore, "vkCreateSemaphore", &AvailableSemaphore));
                           

    

}


//Lazy way to avoid having to deal with fences via use of SIMULTANEOUS USE BIT which depsote the apparent ineffciency of redundant submision is drastically more performant than a considrrable degree of more contventional fence/Synchronisation setups
inline void renderer2::drawFrame()
{
    
    
    pstrct.checkCall(vkAcquireNextImageKHR(pstrct.device, swapChain,TmUt,AvailableSemaphore, VK_NULL_HANDLE, &currentFrame));

    
   updateUniformBuffer();
       info.pCommandBuffers = &PipelineX::commandBuffers[currentFrame];
      

    pstrct.checkCall(vkQueueSubmit(Queues::GraphicsQueue, 1, &info, VK_NULL_HANDLE));
  
  
   
                //  info.pWaitSemaphores = &AvailableSemaphore;


    pstrct.checkCall(vkQueuePresentKHR(Queues::GraphicsQueue, &VkPresentInfoKHR1));

   currentFrame = (currentFrame + 1) % pstrct.Frames;

   
}


constexpr inline void renderer2::memcpy2(__int256 * __restrict__  _Dst,   __int256 const* __restrict__ _Src,size_t _MaxCount)
{
        *_Dst=*_Src;
}

inline void renderer2::updateUniformBuffer()
{
    
    float time = glfwGetTime()*ah;
   
    ubo.model = viewproj * glm::rotate(glm::identity<glm::mat4>(), time, glm::vec3(0.0f, 0.0f, 1.0f));
    // ubo.proj[1][1] *= -1;
//    __m512 a =(__m512)&data+0x200;
    
    /*Should Ideally Peristently map the Uniberform buffer allocation instead 
        *Howver don't currently know of a method to carry this out in C++ without Java Unsafe API Black Magic (Write to mem addresses dierctly without Type checking)
        */
    // vkMapMemory(pstrct.device, UniformBufferObject::uniformBuffersMemory, 0, UniformBufferObject::Sized, 0, &data);
    {
        memcpy2((__int256*)data, (__int256*)&ubo.model, UniformBufferObject::Sized);
    }
    // vkUnmapMemory(pstrct.device, UniformBufferObject::uniformBuffersMemory);
    //  data=nullptr;
    
}