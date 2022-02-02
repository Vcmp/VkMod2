#pragma once
#include "GLFW/glfw3.h"
#include "Pipeline.hpp"
#include "UniformBufferObject.hpp"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "Buffers.hpp"


typedef size_t __int256 __attribute__((__vector_size__(UniformBufferObject::Sized), __aligned__(256)));
    static __int256* ax=(__int256*)&ubo;
constexpr static struct renderer2 
{

    static void setupRenderDraw();
    static void drawFrame();
    static void updateUniformBuffer();
    

static inline VkSemaphore AvailableSemaphore;
    // static inline VkSemaphore FinishedSemaphore;
    // static VkFence FFence;
    
    // static VkPresentInfoKHR VkPresentInfoKHR1;
    // static VkSemaphore AvailableSemaphores[Frames];
    // static VkSemaphore FinishedSemaphores[Frames];
    // static VkFence vkCreateCFences[Frames];
    // static VkSwapchainKHR swapChains[Frames];
    // static VkSwapchainKHR swapChains[] = {swapChain};
    static inline uint32_t currentFrame;
    static constexpr uint32_t TmUt = 1000000000;
    static inline constexpr VkPresentInfoKHR VkPresentInfoKHR1= {
                    .sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                    // .pWaitSemaphores=&FinishedSemaphore,
                    .swapchainCount=1,
                    .pSwapchains= &swapChain,
                    .pImageIndices=&currentFrame,
                    .pResults=nullptr
                    
    };
static constexpr VkPipelineStageFlags  waitStages = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT; 
 static inline VkSubmitInfo info = {
        .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,

        // AvailableSemaphore = {AvailableSemaphore};
        // VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        .waitSemaphoreCount = 1,
        .pWaitSemaphores = &AvailableSemaphore,
        .pWaitDstStageMask = &waitStages,

        .commandBufferCount = 1,
 };
 static inline constexpr VkSemaphoreCreateInfo vkCreateCSemaphore = {
                        .sType=VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
                        .pNext=nullptr
                        };
} inline r2;

 
   
 

inline void setupRenderDraw()
{
                        
//  VkFenceCreateInfo vkCreateCFence{};
//                          vkCreateCFence.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
//                          vkCreateCFence.pNext=nullptr;
                        // for (int i=0;i<3; i++)
                        {

                        (clPPPI(&r2.vkCreateCSemaphore, "vkCreateSemaphore", &r2.AvailableSemaphore));
                        // (clPPPI(&vkCreateCSemaphore, "vkCreateSemaphore", &FinishedSemaphore));
                        // checkCall(vkCreateFence(device, &vkCreateCFence, nullptr, &FFence));
                         }
                       

                        // AvailableSemaphores[0]={AvailableSemaphore};
                        // FinishedSemaphores[0]={FinishedSemaphore};

                        
                    // info ={};
                    	
                    // 		info.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
                    // 		info.pNext=nullptr;
                    // 		info.waitSemaphoreCount=1;
                    // 		info.pWaitSemaphores=&AvailableSemaphore;
                    // 		info.pWaitDstStageMask=waitStages;
                    //         info.commandBufferCount=1;
                    //         info.pCommandBuffers=PipelineX::commandBuffers;
                    //         info.signalSemaphoreCount=1;
                    //         info.pSignalSemaphores=&FinishedSemaphore;
                         

 
                        
                        
                        
                    // VkSubmitInfo.ncommandBufferCount(address2, 1);
                    // memPutLong(VkPresentInfoKHR1 + VkPresentInfoKHR.PIMAGEINDICES, MemSysm.address);
                    // memPutLong(VkPresentInfoKHR1 + VkPresentInfoKHR.PSWAPCHAINS, SwapChainSupportDetails.swapChain);
                    //nmemFree(VkPresentInfoKHR1);
//                    VkPresentInfoKHR.nsType(VkPresentInfoKHR1, VK_STRUCTURE_TYPE_PRESENT_INFO_KHR);
//                    memPutLong(VkPresentInfoKHR1 + VkPresentInfoKHR.PWAITSEMAPHORES, (AvailableSemaphore));
//                    memPutInt(VkPresentInfoKHR1 + VkPresentInfoKHR.SWAPCHAINCOUNT, 1);
                    // Align address to the specified alignment
                    // VkSubmitInfo.validate(address2);
                    // VkPresentInfoKHR.validate(VkPresentInfoKHR1);

}



inline void drawFrame()
{
    // uint32_t currentFrame;
    // vkResetFences(device, 1, &vkCreateCFences[currentFrame]);
    
    checkCall(vkAcquireNextImageKHR(device, swapChain, r2.TmUt, r2.AvailableSemaphore, VK_NULL_HANDLE, &r2.currentFrame));

    
    r2.updateUniformBuffer();
        r2.info.pCommandBuffers = &PipelineX::commandBuffers[r2.currentFrame];
        // info.signalSemaphoreCount = 1;
        // info.pSignalSemaphores = &FinishedSemaphore;

    checkCall(vkQueueSubmit(Queues::GraphicsQueue, 1, &r2.info, VK_NULL_HANDLE));
    // VkPresentInfoKHR1.pWaitSemaphores=&AvailableSemaphore;
    //   vkWaitForFences(device, 1, &vkCreateCFence, false, TmUt);

  
   
                  


    checkCall(vkQueuePresentKHR(Queues::GraphicsQueue, &r2.VkPresentInfoKHR1));

    r2.currentFrame = (r2.currentFrame + 1) % Frames;

   
}

// struct UBO{
//      glm::mat4 model;
//       glm::mat4 proj;
//       glm::mat4 view;
//     //mat4 Trans;
// } inline ubo;

constexpr void memcpy2(__int256 *  _Dst,   __int256 const* _Src,size_t _MaxCount)
{
    // for (uint64_t i=0;i<1; i++)
    
    {
        // _Dst=(__m5121*)&data+256;
        *_Dst=*_Src;
    }
}

inline void renderer2::updateUniformBuffer()
{
   

  
    
    float time = glfwGetTime()*glm::radians(90.0f);
   
    
    ubo.model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0.0f, 0.0f, 1.0f));
    // ubo.proj[1][1] *= -1;
//    __m512 a =(__m512)&data+0x200;
    
    vkMapMemory(device, UniformBufferObject::uniformBuffersMemory[currentFrame], 0, UniformBufferObject::Sized, 0, &data);
    {
        memcpy2((__int256*)data, ax, UniformBufferObject::Sized);
    }
    vkUnmapMemory(device, UniformBufferObject::uniformBuffersMemory[currentFrame]);
    
}