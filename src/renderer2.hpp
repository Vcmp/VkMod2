#include "Pipeline.hpp"
#include "src/Queues.hpp"

inline namespace renderer2 
{
    static VkSemaphore AvailableSemaphore;
    static VkSemaphore FinishedSemaphore;
    // static VkFence FFence;
    static VkSubmitInfo info;
    static VkPresentInfoKHR VkPresentInfoKHR1;
    // static VkSemaphore AvailableSemaphores[Frames];
    // static VkSemaphore FinishedSemaphores[Frames];
    // static VkFence vkCreateCFences[Frames];
    // static VkSwapchainKHR swapChains[Frames];
    // static VkSwapchainKHR swapChains[] = {swapChain};
    static  uint32_t currentFrame;
     constexpr uint32_t TmUt = 1000000000;

    static void setupRenderDraw();
    static void drawFrame();
constexpr VkPipelineStageFlags  waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
}


inline void renderer2::setupRenderDraw()
{
                        VkSemaphoreCreateInfo vkCreateCSemaphore = {};
                        vkCreateCSemaphore.sType=VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
                        vkCreateCSemaphore.pNext=nullptr;
//  VkFenceCreateInfo vkCreateCFence{};
//                          vkCreateCFence.sType=VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
//                          vkCreateCFence.pNext=nullptr;
                        // for (int i=0;i<3; i++)
                        {

                        checkCall(vkCreateSemaphore(device, &vkCreateCSemaphore, nullptr, &AvailableSemaphore));
                        checkCall(vkCreateSemaphore(device, &vkCreateCSemaphore, nullptr, &FinishedSemaphore));
                        // checkCall(vkCreateFence(device, &vkCreateCFence, nullptr, &FFence));
                         }
                        
                         info = {};
        info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        // AvailableSemaphore = {AvailableSemaphore};
        // VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = &AvailableSemaphore;
        info.pWaitDstStageMask = waitStages;

        info.commandBufferCount = 1;
                       

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
                         

 VkPresentInfoKHR1= {};
                    VkPresentInfoKHR1.sType=VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
                    VkPresentInfoKHR1.pWaitSemaphores=&FinishedSemaphore;
                    VkPresentInfoKHR1.swapchainCount=1;
                    VkPresentInfoKHR1.pSwapchains= &swapChain;
                    VkPresentInfoKHR1.pImageIndices=&currentFrame;
                    VkPresentInfoKHR1.pResults=nullptr;
                        
                        
                        
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



inline void renderer2::drawFrame()
{
    // uint32_t currentFrame;
    // vkResetFences(device, 1, &vkCreateCFences[currentFrame]);
    
    checkCall(vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, AvailableSemaphore, VK_NULL_HANDLE, &currentFrame));

    
        info.pCommandBuffers = &commandBuffers[currentFrame];

        // info.signalSemaphoreCount = 1;
        // info.pSignalSemaphores = &FinishedSemaphore;

    checkCall(vkQueueSubmit(Queues::GraphicsQueue, 1, &info, VK_NULL_HANDLE));
    // VkPresentInfoKHR1.pWaitSemaphores=&AvailableSemaphore;
    //   vkWaitForFences(device, 1, &vkCreateCFence, false, TmUt);

   
                    
   
   
                  


    checkCall(vkQueuePresentKHR(Queues::GraphicsQueue, &VkPresentInfoKHR1));

    currentFrame = (currentFrame + 1) % Frames;

   
}