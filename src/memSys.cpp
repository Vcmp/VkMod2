#include "memSys.hpp"
#include <cstdio>

constexpr auto getMaxBARSize(auto &mheaps) -> VkDeviceSize
{
    auto xl=0;
    for(const auto& memHeaps : mheaps)
   {
    printf("Type %u, \n", memHeaps.flags);
    printf("Size %llu, \n", memHeaps.size);
    //Windows for some reason does not allocate/provide the full 256MB allowed by the default BAR if Resizeable BAR is not enabled/Supported
    if(memHeaps.flags==VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
    {
        xl=(memHeaps.size&0xD6F4240) ? memHeaps.size : xl;
    }
    
   }
   return xl;
}

auto memSys::doAlloc(VkPhysicalDevice physdevice, VkDevice device , VkInstance instance) -> VmaAllocator
{

    VkPhysicalDeviceMemoryProperties  vkPhysicalDeviceProperties;

    vkGetPhysicalDeviceMemoryProperties(physdevice, &vkPhysicalDeviceProperties);

   constexpr VkMemoryHeapFlags x={VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT};
   const VkDeviceSize aa= {vkPhysicalDeviceProperties.memoryHeapCount}; VkDeviceSize MAX_BAR;
   MAX_BAR=getMaxBARSize(vkPhysicalDeviceProperties.memoryHeaps);
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
