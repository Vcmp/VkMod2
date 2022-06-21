
#pragma once


#include <array>
#include <cstdint>
#include "Vks.tpp"



//ideally will need to fix this abomination of a Constructor/InitialserList/Layout later
struct fakeFBO
{
    VkPipeline pipeLine;
    VkCommandPool commandPool;
    VkRenderPass renderPass;
    VkFramebuffer frameBuffer;
    std::array<VkImageView, Frames> imageViews;
    VkPipelineLayout layout;
    std::array<VkCommandBuffer, Frames> commandBuffers;
    // static VkCommandBuffer doCommBuffers(VkCommandPool, uint32_t);
    // std::array<VkCommandBuffer, Frames> doGenCommnd();
    void doCommndRec(uint32_t, clock_t) const;

    
} __attribute__((aligned(128)));


