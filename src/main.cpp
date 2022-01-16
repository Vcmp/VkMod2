#include "mat4.hpp"
#include "VkUtils2.hpp"


// using namespace VkU2;
bool a = true;
//    private static boolean aa;

    int main()
    {
        // float laa[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        // mat4 m4;
        //  float laaa[16]={1};
        // mat4 m45;
        // m45.loadAligned(laaa);
        // m4.identity()->domatFMA(&m45);
      //  VkUtils2.extracted();
        //System.gc();

//            int i = 0;
		VkUtils2::extracted();
        // SwapChainSupportDetails::createSwapChain();
        // SwapChainSupportDetails::createImageViews();
        // Pipeline::createRenderPasses();
        // Pipeline::createGraphicsPipelineLayout();
        // Pipeline::createCommandPool();

        int aa=0;
        while (!glfwWindowShouldClose((window)))
        {


            //renderer2.Renderer2.drawFrame();
			// extracted();

            glfwPollEvents();
			printf("%i \n", aa);
			aa++;

        }
        a=false;

        //VkUtils2.cleanup();
        glfwTerminate();
    }

    //todo: Wake from callBack...
    

inline void VkUtils2::createSwapChain()
{
            VkSurfaceFormatKHR surfaceFormat = querySwapChainSupport(Queues::physicalDevice);
        
            VkExtent2D extent = SwapChainSupportDetails::chooseSwapExtent(*window);
            uint32_t imageCount= (capabilities.minImageCount + 1);

            if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) {
                imageCount = capabilities.maxImageCount;
            }

            std::cout<<"ImageCount: "<<imageCount<<"\n";

            VkSwapchainCreateInfoKHR createInfo={};

                    createInfo.sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
                    createInfo.surface=Queues::surface;

                    // Image settings
                    createInfo.minImageCount=imageCount;
                    createInfo.imageFormat=surfaceFormat.format;//=&surfaceFormat; //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!
                    createInfo.imageColorSpace=surfaceFormat.colorSpace;
                    createInfo.imageExtent=extent;
                    createInfo.imageArrayLayers=1;
                    createInfo.imageUsage=capabilities.supportedUsageFlags;
                    createInfo.pNext=nullptr;

                    createInfo.imageSharingMode=VK_SHARING_MODE_EXCLUSIVE;
                    // createInfo.queueFamilyIndexCount=0;
                    // createInfo.pQueueFamilyIndices= nullptr;
        
                    createInfo.preTransform=capabilities.currentTransform;
                    createInfo.compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
                    createInfo.presentMode=VK_PRESENT_MODE_IMMEDIATE_KHR;
                    createInfo.clipped=true;

                    createInfo.oldSwapchain=VK_NULL_HANDLE;
                    std::cout << Queues::device<<"\n";

            // vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain);
            // auto xx=PFN_vkVoidFunction(swapChain);
            clPPPI(&createInfo, "vkCreateSwapchainKHR", &swapChain); //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!
           ;


            checkCall(vkGetSwapchainImagesKHR(Queues::device, swapChain, &imageCount, pSwapchainImages));

            swapChainImageFormat =surfaceFormat;
            swapChainExtent = extent;
        
}
