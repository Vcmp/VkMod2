#include "Pipeline.hpp"

inline namespace renderer2 
{
    VkSemaphore AvailableSemaphore;
    VkSemaphore FinishedSemaphore;

    inline void setupRenderDraw();
    inline void drawFrame();

}


inline void renderer2::setupRenderDraw()
{
                        VkSemaphoreCreateInfo vkCreateCSemaphore = {};
                        vkCreateCSemaphore.sType=VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

                        vkCreateSemaphore(device, &vkCreateCSemaphore, nullptr, &AvailableSemaphore);
                        vkCreateSemaphore(device, &vkCreateCSemaphore, nullptr, &FinishedSemaphore);

                        //  VkSubmitInfo info ={
                    	
                    	// 	.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO,
                    	// 	NULL,
                    	// 	1,
                    	// 	MemSysm.stack.longs(AvailableSemaphore),
                    	// 	MemSysm.ints(VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT), MemSysm.longs(Buffers.commandBuffers),
                    	// 	MemSysm.stack.longs(FinishedSemaphore)
                        //  };

}



inline void renderer2::drawFrame()
{
     uint32_t imageIndex;
    vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, AvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
}