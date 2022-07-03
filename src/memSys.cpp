#include "memSys.hpp"
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
