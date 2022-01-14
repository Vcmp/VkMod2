#include "VkUtils2.hpp"
#include "mat4.hpp"


bool a = true;
//    private static boolean aa;

    int main()
    {
        float laa[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        mat4 m4(laa);
         float laaa[16]={1};
        mat4 m45(laaa);
        m4.domatFMA(&m45);
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
    


