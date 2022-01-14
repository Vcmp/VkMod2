
#include "GLFW/glfw3.h"
#include "src/Queues.hpp"
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <vector>
#include <vulkan/vulkan.h>


// static VkSurfaceFormatKHR formats={};
   static VkPresentModeKHR presentModes={};
   static VkSurfaceCapabilitiesKHR capabilities{};
   static VkSwapchainKHR swapChain={};
   
//    static VkSurfaceFormatKHR* formats;
   static VkExtent2D swapChainExtent{};

    static VkSurfaceFormatKHR swapChainImageFormat={};
    static VkImageView swapChainImageViews={};
    static VkRenderPass renderPass{};

struct SwapChainSupportDetails
{
    static void querySwapChainSupport(VkPhysicalDevice);
    static void createSwapChain();
    static void createImageViews();
    static uint32_t clamp(uint32_t,uint32_t,uint32_t);
    static VkExtent2D chooseSwapExtent(GLFWwindow&);
    static VkPresentModeKHR chooseSwapPresentMode(VkPresentModeKHR&);
    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>);
   
};



        inline uint32_t SwapChainSupportDetails::clamp(uint32_t min, uint32_t max, uint32_t value)
            {
                const uint32_t a =  (max < value ? max : value);
                return  (min > a ? min : a);
            }
        inline VkExtent2D SwapChainSupportDetails::chooseSwapExtent(GLFWwindow &window)
            
            {
                std::cout << "Creating: chooseSwapExtent"<<"\n";
                if (capabilities.currentExtent.width != 0xFFFFFFFF) {
                    return capabilities.currentExtent;
                }
                int width, height;
                glfwGetFramebufferSize(&window, &width, &height);

                VkExtent2D actualExtent={
                    static_cast<uint32_t>(width),
                    static_cast<uint32_t>(height)
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
        
    




