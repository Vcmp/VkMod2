#pragma once


#include "VkUtilsXBase.hpp"

// = (&set + sizeof(set));

inline namespace Buffers
{
    inline VkOffset2D set{.x=0,.y=0};

        inline VkImageLayout depthImageView;
        // inline VkPipelineLayout vkLayout;
        static void createBuffer(VkBuffer, VkDeviceMemory);
        static void setBuffer(VkBufferUsageFlagBits, size_t, VkBuffer);
        static uint32_t findMemoryType(VkPhysicalDevice, uint32_t, VkMemoryPropertyFlagBits);
};



inline uint32_t Buffers::findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlagBits properties)
{
      VkPhysicalDeviceMemoryProperties memProperties = {};
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) != 0 && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
             
                return i;
            }
        }

        throw std::runtime_error("Failed to find suitable memory type");
}

