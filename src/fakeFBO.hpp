
#pragma once


#include <volk.h>

//ideally will need to fix this abomination of a Constructor/InitialserList/Layout later
struct fakeFBO
{
    const VkPipeline pipeLine;
    const VkCommandPool commandPool;
    const VkRenderPass renderPass;
    const VkFramebuffer frameBuffer;
    const VkImageView imageViews[3];
    const VkPipelineLayout layout;
    const VkCommandBuffer commandBuffers[3];
    static VkCommandBuffer doCommBuffers(VkCommandPool, uint32_t);
    void doCommndRec();

    
};


