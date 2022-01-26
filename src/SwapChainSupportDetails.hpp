
#pragma once

#include "Queues.hpp"
#include <vulkan/vulkan_core.h>





// static VkSurfaceFormatKHR formats={};
   

inline namespace SwapChainSupportDetails
{
    // static VkPresentModeKHR presentModes={};
   static VkSurfaceCapabilitiesKHR capabilities{};
   
   static VkImageLayout depthImageView;
    // static VkSurfaceFormatKHR *formats;
    // static VkPresentModeKHR   *presentModes;
//    static VkSurfaceFormatKHR* formats;
   static VkSwapchainKHR swapChain;
    static uint32_t count;

    static VkFormat swapChainImageFormat;
    static VkImageView swapChainImageViews[Frames];
    static VkRenderPass renderPass;
    static VkExtent2D swapChainExtent;
    static VkImage swapchainImages[Frames];
    static VkFramebuffer swapChainFramebuffers[Frames];
    // static void querySwapChainSupport(VkPhysicalDevice);
  
   



        inline uint32_t clamp(uint32_t min, uint32_t max, uint32_t value)
            {
                const uint32_t a =  (max < value ? max : value);
                return  (min > a ? min : a);
            }
        inline VkExtent2D chooseSwapExtent()
            //todo: MAy nto Detect Actal Extent Correctly"
            {
               if (capabilities.currentExtent.width != 0xFFFFFFFF) {
                    return capabilities.currentExtent;
                }

                VkExtent2D actualExtent = {854, 480};

                VkExtent2D minExtent = capabilities.minImageExtent;
                VkExtent2D maxExtent = capabilities.maxImageExtent;

                actualExtent.width=clamp(minExtent.width, maxExtent.width, actualExtent.width);
                actualExtent.height=clamp(minExtent.height, maxExtent.height, actualExtent.height);


                return actualExtent;
            }

        inline VkPresentModeKHR chooseSwapPresentMode(const VkPresentModeKHR *availablePresentModes)
            {

            for(uint32_t i=0;i<count;i++)
            { 
                    if (availablePresentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                        return availablePresentModes[i];
                    }
                }

                            return VK_PRESENT_MODE_FIFO_KHR;
            }



        inline VkSurfaceFormatKHR chooseSwapSurfaceFormat(const VkSurfaceFormatKHR* formats)
        {
            
            {

                for(uint32_t i=0;i<count;i++)
                {
                    if(formats[i].format==VK_FORMAT_B8G8R8A8_SRGB  && formats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
                    {
                            return formats[i];
                    }
                    
                }
            }
              
            
               throw std::runtime_error("------------");
            
          
        }       
        
inline void querySwapChainSupport(VkSurfaceFormatKHR* formats, VkPresentModeKHR* presentModes)
{

      
        // VkSurfaceFormatKHR *formats;
        if (count != 0) {
            //formats =  new VkSurfaceFormatKHR[count];
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, formats);
        }

        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, nullptr);

        // VkPresentModeKHR    presentModes;
        if (count != 0) {
            // presentModes = new VkPresentModeKHR[count];
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, presentModes);
        }
    //   formats1=formats;
} 

inline void createSwapChain()
{
      vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &capabilities);

       

        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, nullptr);
    VkSurfaceFormatKHR surfaceFormats[count];
   
     if (count != 0) vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, surfaceFormats);
        

        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, nullptr);
 VkPresentModeKHR presentModes[count];
        // VkPresentModeKHR    presentModes;
        if (count != 0) vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, presentModes);
        
    
        VkSurfaceFormatKHR surfaceFormat;
        for(const VkSurfaceFormatKHR &surfaceFormat1: surfaceFormats)
                {
                    if(surfaceFormat1.format==VK_FORMAT_B8G8R8A8_SRGB  && surfaceFormat1.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
                    {
                           surfaceFormat= surfaceFormat1;
                           break;
                    }
                    
                }
         VkPresentModeKHR presentMode;
             for(const VkPresentModeKHR &presentMode1: presentModes)
            { 
                    if (presentMode1 == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                        presentMode=presentMode1;
                        break;
                    }
                    else presentMode=VK_PRESENT_MODE_FIFO_KHR;
            }

                            // return VK_PRESENT_MODE_FIFO_KHR;
            
            VkExtent2D extent = SwapChainSupportDetails::chooseSwapExtent();
            uint32_t imageCount= (SwapChainSupportDetails::capabilities.minImageCount + 1);

            if (SwapChainSupportDetails::capabilities.maxImageCount > 0 && imageCount > SwapChainSupportDetails::capabilities.maxImageCount) {
                imageCount = SwapChainSupportDetails::capabilities.maxImageCount;
            }

            std::cout<<"ImageCount: "<<imageCount<<"\n";

const uint32_t aa[] =  {graphicsFamily, presentFamily};;

            const VkSwapchainCreateInfoKHR createInfo{

                    .sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
                    .surface=Queues::surface,

                    // Image settings
                    .minImageCount=imageCount,
                    .imageFormat=surfaceFormat.format,//=&surfaceFormat; //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG,
                    .imageColorSpace=surfaceFormat.colorSpace,
                    .imageExtent=extent,
                    .imageArrayLayers=1,
                    .imageUsage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
                    .pNext=nullptr,

                // if (graphicsFamily != presentFamily) {
                //     .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
                //     .queueFamilyIndexCount = 2,
                //     .pQueueFamilyIndices = aa,
                // } else {
                    .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
                    // .queueFamilyIndexCount = 0; // Optiona,
                    // .pQueueFamilyIndices = nullptr; // Optiona,
                // }
        
                    .preTransform=SwapChainSupportDetails::capabilities.currentTransform,
                    .compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
                    .presentMode=presentMode,
                    .clipped=true,

                    .oldSwapchain=VK_NULL_HANDLE
                    };
                    std::cout << device<<"\n";

            // vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain);
            // auto xx=PFN_vkVoidFunction(swapChain);
            checkCall(vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain)); //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!
           


            // checkCall(vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr));
            
            // if(imageCount!=Frames)
            // {
            //     throw std::runtime_error("Swapchains not equal to allocated length: Bad SwapChain");
            // }
            checkCall(vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapchainImages));
            SwapChainSupportDetails::swapChainImageFormat =surfaceFormat.format;
            SwapChainSupportDetails::swapChainExtent = extent;

}

inline void createImageViews()
    {
        std::cout<< ("Creating Image Views") << "\n";
        int i=0;
         for (const VkImage &swapchainImage : swapchainImages)
         {
         VkImageViewCreateInfo createInfo={};
                createInfo.sType=VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

                        createInfo.viewType=VK_IMAGE_VIEW_TYPE_2D;
                        createInfo.format=swapChainImageFormat;

                    //     createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
                    // createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
                    // createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
                    //     createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
                        

        
                
       
                createInfo.subresourceRange.aspectMask=VK_IMAGE_ASPECT_COLOR_BIT;
                        createInfo.subresourceRange.baseMipLevel=0;
                        createInfo.subresourceRange.levelCount=1;
                        createInfo.subresourceRange.baseArrayLayer=0;
                        createInfo.subresourceRange.layerCount=1;
       
        
           createInfo.image=swapchainImage;
        
        clPPPI(&createInfo, "vkCreateImageView", &SwapChainSupportDetails::swapChainImageViews[i++]); //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!
        }

        


    }

    inline void createFramebuffers()
    {
        //  PointerBuffer attachments;
//               if(depthBuffer)
//               else
//                   attachments = stack.stack.longs(1);
 VkFramebufferCreateInfo framebufferCreateInfo ={};
                    framebufferCreateInfo.sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
                    framebufferCreateInfo.renderPass=renderPass;
                    framebufferCreateInfo.width=swapChainExtent.width;
                    framebufferCreateInfo.height=swapChainExtent.height;
                    framebufferCreateInfo.layers=1;
            // attachments = MemSysm.longs=(swapChainImageFormat, &Buffers::depthImageView));

            //                      .sType(VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO)
            // int a =swapChainImageFormat;
            // int b=depthImageView;
            // int abx[]={a,b};
            framebufferCreateInfo.attachmentCount=1;//(framebufferCreateInfo.address(), (attachments).remaining());
        //    framebufferCreateInfo.pAttachments= swapChainImageViews;
                for (size_t i = 0; i < Frames; i++) {
                    // VkImageView attachments[] = {swapChainImageViews[i]};
            // VkFramebufferAttachmentImageInfo AttachmentImageInfo[2];// = VkFramebufferAttachmentImageInfo.create(MemSysm.calloc(VkFramebufferAttachmentImageInfo.SIZEOF * 2L), 2);
            // AttachmentImageInfo[0]={};
            //         // AttachmentImageInfo[0].sType=VK_STRUCTURE
            //         AttachmentImageInfo[0].layerCount=(1);
            //         AttachmentImageInfo[0].width=(swapChainExtent.width);
            //         AttachmentImageInfo[0].height=(swapChainExtent.height);
            //         AttachmentImageInfo[0].usage=(VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT);
            //         AttachmentImageInfo[0].pViewFormats=(VK_FORMAT_R8G8B8A8_SRGB);
            
           framebufferCreateInfo.pAttachments= &swapChainImageViews[i];
            // AttachmentImageInfo[1]= {};
            //         // AttachmentImageInfo[1].sType$Default();
            //         AttachmentImageInfo[1].layerCount=(1);
            //         AttachmentImageInfo[1].width=(swapChainExtent.width);
            //         AttachmentImageInfo[1].height=(swapChainExtent.height);
            //         AttachmentImageInfo[1].usage=(VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);
            //         AttachmentImageInfo[1].pViewFormats=(&Texture::findDepthFormat());
                    // AttachmentImageInfo[1].pViewFormats=(&Texture::findDepthFormat());

            

            // Lets allocate the create info struct once and just update the pAttachments field each iteration
           

            //todo: Check only oneusbpass runing due to differing ColourDpetHFormats and isn;t coauong probelsm sude to Sumuetnous ComandBuffering nort requiinG fencing.Allowing for FenceSkip
            //memPutLong(framebufferCreateInfo.address() + VkFramebufferCreateInfo.PATTACHMENTS, memAddress0(attachments));
//               memPutInt(framebufferCreateInfo.address() + VkFramebufferCreateInfo.ATTACHMENTCOUNT, 1);
            //memPutInt(framebufferCreateInfo.address() + VkFramebufferCreateInfo.ATTACHMENTCOUNT, attachments.capacity());
            //Memsys2.free(framebufferCreateInfo);
            //nmemFree(framebufferCreateInfo.address());
            //TODO: warn Possible Fail!

            clPPPI(&framebufferCreateInfo, "vkCreateFramebuffer", &swapChainFramebuffers[i]);
                }
            // for (int i = 0; i < swapChainImageViews.capacity(); i++) {
            //     attachments.put(0, swapChainImageViews.get(i));


            //     swapChainFramebuffers.put(i, MemSysm.doPointerAllocSafe(framebufferCreateInfo/*.pNext(NULL)*/, Buffers.capabilities.vkCreateFramebuffer));
            // }
    }


};
