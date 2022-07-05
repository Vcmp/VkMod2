



#include "vk_mem_alloc.h"
#include <cstddef>

struct memSys
{
    VmaAllocator vmaAllocator;
    memSys(VkPhysicalDevice physdevice, VkDevice device , VkInstance instance): vmaAllocator(doAlloc(physdevice, device , instance)) {};
    
    auto doAlloc(VkPhysicalDevice, VkDevice, VkInstance) -> VmaAllocator;
    auto allocBuf(VkBuffer, size_t, VmaAllocation&) -> VkBuffer;
};