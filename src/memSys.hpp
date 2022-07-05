


#pragma once
#include "vk_mem_alloc.h"
#include <cstddef>
#include <immintrin.h>

struct [[clang::vecreturn, clang::trivial_abi]] memSys
{
    void* data; //Moved to struct instead of inited in function due to teh abiloty to utilsie TaiLCalls when 
    VmaAllocator vmaAllocator;
    memSys(VkPhysicalDevice physdevice, VkDevice device , VkInstance instance): vmaAllocator(doAlloc(physdevice, device , instance)) {};
    VmaAllocation *reemptMappedSection;
    auto doAlloc(VkPhysicalDevice, VkDevice, VkInstance) -> VmaAllocator;
    auto aAlloc(VkPhysicalDevice, VkDevice, VkInstance) -> VmaAllocator;
    auto allocBuf(size_t, VmaAllocation&) -> VkBuffer;
    [[gnu::pure, gnu::no_split_stack, clang::no_stack_protector, gnu::no_address_safety_analysis, gnu::flatten/* , gnu::force_align_arg_pointer] */]] void mapMem(uint8_t*, VkDeviceSize);
    [[gnu::always_inline]] void addMappedSection(VmaAllocation&, size_t);
};