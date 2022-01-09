#include "VkUtils2.hpp"
#include "src/SwapChainSupportDetails.hpp"


bool a = true;
//    private static boolean aa;

    int main()
    {

      //  VkUtils2.extracted();
        //System.gc();

//            int i = 0;
		VkUtils2::setupWindow();
        VkUtils2::createInstance();
        VkUtils2::setupDebugMessenger();
        VkUtils2::createSurface();
        VkUtils2::pickPhysicalDevice();
        VkUtils2::createLogicalDevice();
        SwapChainSupportDetails::createSwapChain();
        SwapChainSupportDetails::createImageViews();
        Pipeline::createRenderPasses();
        Pipeline::createGraphicsPipelineLayout();
        Pipeline::createCommandPool();

        int aa=0;
        while (!glfwWindowShouldClose(window))
        {


            //renderer2.Renderer2.drawFrame();
			// extracted();

            glfwPollEvents();
			//  std::cout <<aa << "\n";
			aa++;

        }
        a=false;

        //VkUtils2.cleanup();
        glfwTerminate();
    }

    //todo: Wake from callBack...
    


