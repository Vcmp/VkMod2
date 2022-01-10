#include "VkUtils2.hpp"


bool a = true;
//    private static boolean aa;

    int main()
    {

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
        while (!glfwWindowShouldClose(const_cast<GLFWwindow*>(window)))
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
    


