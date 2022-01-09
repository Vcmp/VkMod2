#pragma once
#include "VkUtils2.hpp"

static VkPhysicalDevice physicalDevice;
static VkDevice device;

    static uint32_t graphicsFamily;
    static uint32_t presentFamily;
    static VkSurfaceKHR surface;

    static VkQueue GraphicsQueue;
    static VkQueue PresentQueue;


struct Queues
{
    

   
    

    static void enumerateDetermineQueueFamilies(const VkPhysicalDevice&);
    const static bool isComplete();
};

inline void Queues::enumerateDetermineQueueFamilies(const VkPhysicalDevice &device)
{
            std::cout <<("Checking Available Queue families") << "\n";

            uint32_t pQueueFamilyPropertyCount=0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &pQueueFamilyPropertyCount, nullptr);
            VkQueueFamilyProperties queueFamilies[pQueueFamilyPropertyCount];
            vkGetPhysicalDeviceQueueFamilyProperties(device, &pQueueFamilyPropertyCount, queueFamilies);

            //VkBool32 presentSupport = (VK_FALSE);
            uint32_t i = 0;
            
            for (const  VkQueueFamilyProperties &a : queueFamilies) {
                // std::cout <<(a.queueCount())<< "\n";
                if ((a.queueFlags & VK_QUEUE_GRAPHICS_BIT)==0) {
                    graphicsFamily = i;
                }
                if (isComplete())
                    break;
            
                i++;
            }

//
//                while (i <queueFamilyCount.limit() /*&& !isComplete()*/) {

            // std::cout <<a <<"Graphics Family: " << graphicsFamily << " Present family: " << presentFamily<< "\n";

}

const inline bool Queues::isComplete()
{
    return graphicsFamily!= NULL;
}