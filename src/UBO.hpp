#include <vulkan/vulkan_core.h>
#include "DescriptorSet.hpp"

struct UBO : DescriptorSet
{
    VkBuffer Ubuffer;
    VkDeviceMemory UbufferMem;



};