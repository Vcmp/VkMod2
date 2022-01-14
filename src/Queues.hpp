#include <iostream>
#include <stdint.h>
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

static VkPhysicalDevice physicalDevice;
static VkDevice device;

    static uint32_t graphicsFamily;
    static uint32_t presentFamily;
    static VkSurfaceKHR surface;

    static VkQueue GraphicsQueue;
    static VkQueue PresentQueue;


struct Queues
{
    

   
    

    static VkQueueFamilyProperties enumerateDetermineQueueFamilies(const VkPhysicalDevice&, uint32_t, VkQueueFamilyProperties[]);
    const static bool isComplete();
};

inline VkQueueFamilyProperties Queues::enumerateDetermineQueueFamilies(const VkPhysicalDevice &device, uint32_t VkQueueFamilyProperties, struct VkQueueFamilyProperties *queueFamilies)
{
            //std::cout <<("Checking Available Queue families") << "\n";

            // uint32_t pQueueFamilyPropertyCount=0;
            // vkGetPhysicalDeviceQueueFamilyProperties(device, &pQueueFamilyPropertyCount, nullptr);
            //VkQueueFamilyProperties queueFamilies[pQueueFamilyPropertyCount];
            vkGetPhysicalDeviceQueueFamilyProperties(device, &VkQueueFamilyProperties, queueFamilies);

            //VkBool32 presentSupport = (VK_FALSE);
           // std::cout << queueFamilies << "\n";
            uint32_t i = 0;
            
            for (;i<VkQueueFamilyProperties;i++) {
                std::cout <<(queueFamilies[i].queueCount)<< "\n";
                if ((queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
                    graphicsFamily = i;
                }
                // if (isComplete())
                //     break;
            
                //i++;
            }
            return *queueFamilies;

//
//                while (i <queueFamilyCount.limit() /*&& !isComplete()*/) {

            // std::cout <<a <<"Graphics Family: " << graphicsFamily << " Present family: " << presentFamily<< "\n";

}

const inline bool Queues::isComplete()
{
    return graphicsFamily== 0;
}