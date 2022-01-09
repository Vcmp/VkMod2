#pragma once

#include <vulkan/vulkan_core.h>

static VkOffset2D set{
    .x=0,
    .y=0
};

static VkPipelineLayout vkLayout;// = (&set + sizeof(set));

struct Buffers
{

};