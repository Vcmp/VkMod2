// #include "mat4.hpp"
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
			// printf("%i \n", aa);
			aa++;

        }
        a=false;

        VkUtils2::cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
    }


   

    //todo: Wake from callBack...
    



// inline void Texture::createDepthResources()
//     {
//           VkFormat depthFormat = findDepthFormat();
//         Texture::createImage(SwapChainSupportDetails::swapChainExtent.width, SwapChainSupportDetails::swapChainExtent.height,
//                 depthFormat,
//                 VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
//         );


//         createImageView(depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, Buffers::depthImageView);
//         transitionImageLayout(depthFormat,
//                 VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
//     }

    
