#pragma once

#include <vulkan/vulkan_core.h>



inline namespace UniformBufferObject
{
    static void createDescriptorSetLayout();
    static inline VkDescriptorSetLayout descriptorSetLayout;
};