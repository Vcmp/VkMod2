
#pragma once

#include "VkUtilsXBase.hpp"


// static VkSurfaceFormatKHR formats={};
   

inline namespace SwapChainSupportDetails
{
    static VkPresentModeKHR presentModes={};
   static VkSurfaceCapabilitiesKHR capabilities{};
   
   
//    static VkSurfaceFormatKHR* formats;
   

    static VkSurfaceFormatKHR swapChainImageFormat={};
    static VkImageView swapChainImageViews={};
    static VkRenderPass renderPass{};
    static VkExtent2D swapChainExtent{};
    // static void querySwapChainSupport(VkPhysicalDevice);
    static void createSwapChain();
    static void createImageViews();
    static uint32_t clamp(uint32_t,uint32_t,uint32_t);
    static VkExtent2D chooseSwapExtent();
    static VkPresentModeKHR chooseSwapPresentMode(VkPresentModeKHR&);
    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>);
   
};



        inline uint32_t SwapChainSupportDetails::clamp(uint32_t min, uint32_t max, uint32_t value)
            {
                const uint32_t a =  (max < value ? max : value);
                return  (min > a ? min : a);
            }
        inline VkExtent2D SwapChainSupportDetails::chooseSwapExtent()
            //todo: MAy nto Detect Actal Extent Correctly"
            {
                std::cout << "Creating: chooseSwapExtent"<<"\n";
                if (capabilities.currentExtent.width != 0xFFFFFFFF) {
                    return capabilities.currentExtent;
                }
                int width, height;
                // glfwGetFramebufferSize(&window, &width, &height);

                VkExtent2D actualExtent={
                    // static_cast<uint32_t>(width),
                    // static_cast<uint32_t>(height)
                    };
                VkExtent2D minExtent = capabilities.minImageExtent;
                VkExtent2D maxExtent = capabilities.maxImageExtent;
            //     uint32_t xn=SwapChainSupportDetails::clamp(minExtent.width, maxExtent.width, actualExtent.width);
            //     uint32_t yn=SwapChainSupportDetails::clamp(minExtent.height, maxExtent.height, actualExtent.height);
            // std::cout<<xn <<"-"<<yn<<"\n";
                actualExtent.width= SwapChainSupportDetails::clamp(actualExtent.width, maxExtent.width, actualExtent.width);
                actualExtent.height= SwapChainSupportDetails::clamp(actualExtent.height, maxExtent.height, actualExtent.height);


                return actualExtent;
            }

        inline VkPresentModeKHR SwapChainSupportDetails::chooseSwapPresentMode(VkPresentModeKHR &availablePresentModes)
            {

            { 
                    if (availablePresentModes == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                        return availablePresentModes;
                    }
                }

                return VK_PRESENT_MODE_FIFO_KHR;
            }



        inline VkSurfaceFormatKHR SwapChainSupportDetails::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> availableFormats)
        {
            
            {

                for(const VkSurfaceFormatKHR  &formats : availableFormats)
                {
                    if(formats.format==VK_FORMAT_B8G8R8A8_SRGB  && formats.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
                    {
                            return formats;
                    }
                    
                }
            }
              
            
               throw std::runtime_error("------------");
            
          
        }       
        
    
inline void SwapChainSupportDetails::createSwapChain()
{

}
inline void SwapChainSupportDetails::createImageViews()
    {
        std::cout<< ("Creating Image Views") << "\n";

        
          VkImageViewCreateInfo createInfo={};
          createInfo.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

                createInfo.viewType=VK_IMAGE_VIEW_TYPE_2D;
                createInfo.format=SwapChainSupportDetails::swapChainImageFormat.format;
                createInfo.image=*pSwapchainImages;

        createInfo.subresourceRange.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT;
                createInfo.subresourceRange.baseMipLevel=0;
                createInfo.subresourceRange.levelCount=1;
                createInfo.subresourceRange.baseArrayLayer=0;
                createInfo.subresourceRange.layerCount=1;
        
        
        checkCall(clPPPI(&createInfo, "vkCreateImageView", &SwapChainSupportDetails::swapChainImageViews)); //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!

        


    }


