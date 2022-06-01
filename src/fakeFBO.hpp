
#pragma once


#include <array>
#include <vulkan/vulkan_core.h>



//ideally will need to fix this abomination of a Constructor/InitialserList/Layout later
struct fakeFBO
{
    VkPipeline &pipeLine;
    VkCommandPool commandPool;
    VkRenderPass &renderPass;
    VkFramebuffer &frameBuffer;
    std::array<VkImageView, 3> &imageViews;
    VkPipelineLayout layout;
    std::array<VkCommandBuffer, 3> commandBuffers =  doGenCommnd();
    static VkCommandBuffer doCommBuffers(VkCommandPool, uint32_t);
    std::array<VkCommandBuffer, 3> doGenCommnd();
    void doCommndRec();

    
};


