
#pragma once


#include <array>
#include <vulkan/vulkan_core.h>



//ideally will need to fix this abomination of a Constructor/InitialserList/Layout later
struct fakeFBO
{
    const VkPipeline pipeLine;
    const VkCommandPool commandPool;
    const VkRenderPass &renderPass;
    const VkFramebuffer &frameBuffer;
    const std::array<VkImageView, 3> &imageViews;
    const VkPipelineLayout &layout;
    const std::array<VkCommandBuffer, 3> commandBuffers =  doGenCommnd();
    static VkCommandBuffer doCommBuffers(VkCommandPool, uint32_t);
    std::array<VkCommandBuffer, 3> doGenCommnd();
    void doCommndRec();

    
};


