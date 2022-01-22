#pragma once
#include "VkUtilsXBase.hpp"
#include <vulkan/vulkan_core.h>



   
inline namespace Queues
{
    static VkPhysicalDevice physicalDevice;
  
    static uint32_t graphicsFamily;
     static uint32_t presentFamily;
     static VkQueue GraphicsQueue;
     static VkQueue PresentQueue;
static void createCommandPool();
 static VkCommandPool commandPool;
 static VkCommandBuffer beginSingleTimeCommands();
        static void endSingleTimeCommands(VkCommandBuffer&);
    
    static VkSurfaceKHR surface;

    
    

    void enumerateDetermineQueueFamilies(uint32_t, VkQueueFamilyProperties[]);
    // const static bool isComplete();
};

inline void Queues::enumerateDetermineQueueFamilies( uint32_t VkQueueFamilyProperties, struct VkQueueFamilyProperties *queueFamilies)
{
            //std::cout <<("Checking Available Queue families") << "\n";

            // uint32_t pQueueFamilyPropertyCount=0;
            // vkGetPhysicalDeviceQueueFamilyProperties(device, &pQueueFamilyPropertyCount, nullptr);
            //VkQueueFamilyProperties queueFamilies[pQueueFamilyPropertyCount];
            vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &VkQueueFamilyProperties, queueFamilies);

            //VkBool32 presentSupport = (VK_FALSE);
           // std::cout << queueFamilies << "\n";
            uint32_t i = 0;
            
            for (;i<VkQueueFamilyProperties;i++) {
                // std::cout <<(queueFamilies[i].queueCount)<< "\n";
                if ((queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
                    graphicsFamily = i;
                }
                // if (isComplete())
                //     break;
            
                //i++;
            }
            // return *queueFamilies;

//
//                while (i <queueFamilyCount.limit() /*&& !isComplete()*/) {

            // std::cout <<a <<"Graphics Family: " << graphicsFamily << " Present family: " << presentFamily<< "\n";

}
inline void Queues::createCommandPool()
    {
        VkCommandPoolCreateInfo poolInfo={};
                poolInfo.sType=VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
                poolInfo.queueFamilyIndex=graphicsFamily;
                poolInfo.flags=0;
        //Memsys2.free(poolInfo);
        clPPPI(&poolInfo, "vkCreateCommandPool", &commandPool);
    }

    inline VkCommandBuffer Queues::beginSingleTimeCommands()
    {

        VkCommandBufferAllocateInfo allocateInfo = {};
        allocateInfo.sType=(VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO);
        allocateInfo.level=(VK_COMMAND_BUFFER_LEVEL_PRIMARY);
        allocateInfo.commandPool=(Queues::commandPool);
        allocateInfo.commandBufferCount=(1);
        allocateInfo.pNext=VK_NULL_HANDLE;

        VkCommandBuffer commandBuffer = {};
        VkCommandBufferBeginInfo vkCommandBufferBeginInfo = {};
        vkCommandBufferBeginInfo.sType=(VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO);
        vkCommandBufferBeginInfo.flags=(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);
        vkCommandBufferBeginInfo.pNext=VK_NULL_HANDLE;
        vkBeginCommandBuffer(commandBuffer, &vkCommandBufferBeginInfo);
        return commandBuffer;
    }

    static void Queues::endSingleTimeCommands(VkCommandBuffer &commandBuffer)
    {
        vkEndCommandBuffer(commandBuffer);
        VkSubmitInfo submitInfo1={};
        submitInfo1.sType=VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo1.pCommandBuffers=&commandBuffer;
        submitInfo1.commandBufferCount=(1);
        submitInfo1.pNext=VK_NULL_HANDLE;

//            VkSubmitInfo.ncommandBufferCount(submitInfo1, 1);

        vkQueueSubmit(GraphicsQueue, 1, &submitInfo1, VK_NULL_HANDLE);

        vkFreeCommandBuffers(device, Queues::commandPool, 1, &commandBuffer);
    }