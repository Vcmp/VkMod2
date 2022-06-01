
#pragma once


#include <array>
#include "VKI.hpp"



//ideally will need to fix this abomination of a Constructor/InitialserList/Layout later
struct fakeFBO
{
    VkPipeline &pipeLine;
    VkCommandPool commandPool;
    VkRenderPass &renderPass;
    VkFramebuffer &frameBuffer;
    std::array<VkImageView, Frames> &imageViews;
    VkPipelineLayout layout;
    std::array<VkCommandBuffer, Frames> commandBuffers =  doGenCommnd();
    static VkCommandBuffer doCommBuffers(VkCommandPool, uint32_t);
    std::array<VkCommandBuffer, Frames> doGenCommnd();
    void doCommndRec();

    
};


