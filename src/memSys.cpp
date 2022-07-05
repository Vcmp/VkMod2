#include "memSys.hpp"
#include "vk_mem_alloc.h"
#include <cstddef>
#include <cstdio>
#include <vulkan/vulkan_core.h>

constexpr auto getMaxBARSize(auto &mheaps) -> VkDeviceSize
{
    auto xl=0;
    
    for(const auto memTypes : mheaps.memoryTypes)
   {
    
    printf("Type %u, \n", memTypes.heapIndex);
    printf("Size %u, \n", memTypes.propertyFlags);
    //Windows for some reason does not allocate/provide the full 256MB allowed by the default BAR if Resizeable BAR is not enabled/Supported
    xl=(memTypes.propertyFlags==(VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)) ? memTypes.heapIndex : xl;
    
   }
   return mheaps.memoryHeaps[xl].size;
}

auto memSys::doAlloc(VkPhysicalDevice physdevice, VkDevice device , VkInstance instance) -> VmaAllocator
{

    VkPhysicalDeviceMemoryProperties  vkPhysicalDeviceProperties;

    vkGetPhysicalDeviceMemoryProperties(physdevice, &vkPhysicalDeviceProperties);

   constexpr VkMemoryHeapFlags x={VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT};
   const VkDeviceSize aa= {vkPhysicalDeviceProperties.memoryHeapCount}; 
   VkDeviceSize MAX_BAR=getMaxBARSize(vkPhysicalDeviceProperties);
    printf("memHeap %llu, \n", MAX_BAR);
auto xx= 0xFFFFFFFF;
   VmaVulkanFunctions vmaVulkanFunctions;
  VmaAllocatorCreateInfo VmaAllocationCreateInfo
  {
    .physicalDevice=physdevice,
    .device=device,
    .preferredLargeHeapBlockSize=MAX_BAR,
    .pHeapSizeLimit=&aa,
    //.pVulkanFunctions=&vmaVulkanFunctions,
    .instance=instance,
    .vulkanApiVersion=VK_API_VERSION_1_3,
  };


  vmaCreateAllocator(&VmaAllocationCreateInfo, &vmaAllocator);
  return vmaAllocator;
}

VkBuffer memSys::allocBuf(VkBuffer buffer, size_t size, VmaAllocation &vmaAllocation)
{
  VkBufferCreateInfo VkBufferCreateInfo
  {
    .sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .size=size,
    .usage=VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    .sharingMode=VK_SHARING_MODE_EXCLUSIVE,
    .queueFamilyIndexCount=1,
    // .pQueueFamilyIndices=2UL,
  };
  // VmaAllocation vmaAllocation;
  VmaAllocationCreateInfo VmaAllocationCreateInfo
  {
    .usage=VMA_MEMORY_USAGE_AUTO,
    .memoryTypeBits=VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
    
  };
  vmaCreateBuffer(vmaAllocator, &VkBufferCreateInfo, &VmaAllocationCreateInfo, &buffer, &vmaAllocation, nullptr);
  //vmaBindImageMemory(vmaAllocator)
}