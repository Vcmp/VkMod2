#pragma once


#include "Pipeline.hpp"


// = (&set + sizeof(set));

inline namespace Buffers
{
    extern VkOffset2D set{.x=0,.y=0};

        extern VkImageLayout depthImageView;
        inline VkPipelineLayout vkLayout;
        static void createBuffer(VkBuffer, VkDeviceMemory);
        static void setBuffer(VkBufferUsageFlagBits, size_t, VkBuffer);
        static uint32_t findMemoryType(VkPhysicalDevice, uint32_t, VkMemoryPropertyFlagBits);
        static VkCommandBuffer beginSingleTimeCommands();
        static void endSingleTimeCommands(VkCommandBuffer&);
};



inline uint32_t Buffers::findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlagBits properties)
{
      VkPhysicalDeviceMemoryProperties memProperties = {};
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
        for (int i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) != 0 && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
             
                return i;
            }
        }

        throw std::runtime_error("Failed to find suitable memory type");
}

inline VkCommandBuffer Buffers::beginSingleTimeCommands()
    {

        VkCommandBufferAllocateInfo allocateInfo = {};
        allocateInfo.sType=(VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO);
        allocateInfo.level=(VK_COMMAND_BUFFER_LEVEL_PRIMARY);
        allocateInfo.commandPool=(Pipeline::commandPool);
        allocateInfo.commandBufferCount=(1);

        VkCommandBuffer commandBuffer = {};
        VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {};
        vkCommandBufferBeginInfo.sType=(VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO);
        vkCommandBufferBeginInfo.flags=(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
        vkBeginCommandBuffer(commandBuffer, &vkCommandBufferBeginInfo);
        return commandBuffer;
    }

    static void Buffers::endSingleTimeCommands(VkCommandBuffer &commandBuffer)
    {
        vkEndCommandBuffer(commandBuffer);
        VkSubmitInfo submitInfo1={};
        submitInfo1.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo1.pCommandBuffers=&commandBuffer;
        submitInfo1.commandBufferCount=(1);

//            VkSubmitInfo.ncommandBufferCount(submitInfo1, 1);

        vkQueueSubmit(GraphicsQueue, 1, &submitInfo1, VK_NULL_HANDLE);

        vkFreeCommandBuffers(device, Pipeline::commandPool, 1, &commandBuffer);
    }