#pragma once
#include <stdexcept>
#include <stdint.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>
#include "Queues.hpp"

static VkSurfaceFormatKHR formats;
   static VkPresentModeKHR presentModes;
   static VkSurfaceCapabilitiesKHR capabilities;
   static VkSwapchainKHR swapChain;
   
   static VkSurfaceFormatKHR swapChainImageFormat;
   static VkExtent2D swapChainExtent;

    static VkImageView swapChainImagesViews[3];
    static VkRenderPass renderPass;

struct SwapChainSupportDetails
{
    static void querySwapChainSupport(VkPhysicalDevice);
    static void createSwapChain();
    static void createImageViews();
   
};

inline void SwapChainSupportDetails::querySwapChainSupport(VkPhysicalDevice device)
{
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &capabilities);

        uint32_t count;

        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &count, NULL);

        if (count != 0) {
            formats = VkSurfaceFormatKHR{};
            vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &count, &formats);
        }

        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &count, NULL);

        if (count != 0) {
            presentModes = {};
            vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &count, &presentModes);
        }
} 

        static int clamp(int min, int max, int value)
            {
                return std::max(min, std::min(max, value));
            }
        static VkExtent2D chooseSwapExtent()
            {
                if (capabilities.currentExtent.width != 0xFFFFFFFF) {
                    return capabilities.currentExtent;
                }

                VkExtent2D actualExtent;

                VkExtent2D minExtent = capabilities.minImageExtent;
                VkExtent2D maxExtent = capabilities.maxImageExtent;

                actualExtent.width=clamp(minExtent.width, maxExtent.width, actualExtent.width);
                actualExtent.height=clamp(minExtent.height, maxExtent.height, actualExtent.height);


                return actualExtent;
            }

        static VkPresentModeKHR chooseSwapPresentMode(VkPresentModeKHR &availablePresentModes)
            {

            { 
                    if (availablePresentModes == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                        return availablePresentModes;
                    }
                }

                return VK_PRESENT_MODE_FIFO_KHR;
            }

        static VkSurfaceFormatKHR chooseSwapSurfaceFormat(VkSurfaceFormatKHR availableFormats)
            {
                if(availableFormats.format == VK_FORMAT_B8G8R8_UNORM && availableFormats.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
                return availableFormats;
                else std::runtime_error("No AVailable Formats!");
                
            }
    
inline void SwapChainSupportDetails::createSwapChain()
{
    {

            querySwapChainSupport(physicalDevice);
        //These May be Broken
            VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(formats);
            VkPresentModeKHR presentMode = chooseSwapPresentMode(presentModes);
            VkExtent2D extent = chooseSwapExtent();

            uint32_t imageCount = (capabilities.minImageCount + 1);


            if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
                imageCount = capabilities.maxImageCount;
            }

            VkSwapchainCreateInfoKHR createInfo{};

                    createInfo.sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
                    createInfo.surface=surface;

                    // Image settings
                    createInfo.minImageCount=imageCount;
                    createInfo.imageFormat=formats.format;//=&surfaceFormat; //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!
                    createInfo.imageColorSpace=surfaceFormat.colorSpace;
                    createInfo.imageExtent=extent;
                    createInfo.imageArrayLayers=1;
                    createInfo.imageUsage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

//                Queues.findQueueFamilies(Queues.physicalDevice);

            if (!(graphicsFamily== presentFamily)) {
                //VkSwapchainCreateInfoKHR.imageSharingMode(VK_SHARING_MODE_CONCURRENT);
                createInfo.imageSharingMode=VK_SHARING_MODE_EXCLUSIVE;
                createInfo.pQueueFamilyIndices= &graphicsFamily;
            } else {
                createInfo.imageSharingMode=VK_SHARING_MODE_EXCLUSIVE;
            }

            createInfo.preTransform=capabilities.currentTransform;
                    createInfo.compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
                    createInfo.presentMode=presentMode;
                    createInfo.clipped=true;

                    createInfo.oldSwapchain=VK_NULL_HANDLE;

            vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain); //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!


//               callPJPPI(PipeLine.deviceAddress, swapChain, (imageCount), NULL, device.getCapabilities().vkGetSwapchainImagesKHR);

            VkImage pSwapchainImages[3];


            vkGetSwapchainImagesKHR(device, swapChain, &imageCount, pSwapchainImages);

//            System.arraycopy(pSwapchainImages, 0, swapChainImages, 0, pSwapchainImages.length);
            // swapChainImages.put(pSwapchainImages);

            swapChainImageFormat =surfaceFormat;
            swapChainExtent = extent;
        }
}


inline void SwapChainSupportDetails::createImageViews()
    {
        std::cout<< ("Creating Image Views") << "\n";

        
          VkImageViewCreateInfo createInfo{};
          createInfo.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

                createInfo.viewType=VK_IMAGE_VIEW_TYPE_2D;
                createInfo.format=swapChainImageFormat.format;

        createInfo.subresourceRange
                .aspectMask=VK_IMAGE_ASPECT_COLOR_BIT;
                createInfo.subresourceRange.baseMipLevel=0;
                createInfo.subresourceRange.levelCount=1;
                createInfo.subresourceRange.baseArrayLayer=0;
                createInfo.subresourceRange.layerCount=1;
        
        
        vkCreateImageView(device, &createInfo, nullptr, swapChainImagesViews); //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!

        


    }