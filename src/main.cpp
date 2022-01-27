// #include "mat4.hpp"
#include "VkUtils2.hpp"
#include "renderer2.hpp"


// struct PStruct{
//      int *a;
// };

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
        std::cout << __cplusplus << "\n";
		VkUtils2::extracted();
        // SwapChainSupportDetails::createSwapChain();
        // SwapChainSupportDetails::createImageViews();
        // Pipeline::createRenderPasses();
        // Pipeline::createGraphicsPipelineLayout();
        // Pipeline::createCommandPool();
        static int axzl=10;
        
        
        
        renderer2::setupRenderDraw();

        static constexpr int aaa=1000;
        static int aa=0;
        while (!glfwWindowShouldClose((window)))
        {
            // static constexpr PStruct ap
            // {
            //     .a=&aa
            // };

            renderer2::drawFrame();
			// // extracted();
            // if (*ap.a==aaa)
            // {
    		// 	printf("%i \n", *ap.a);
            //     // ap.a=0;
            //     *ap.a=0;
            // }

            glfwPollEvents();
			aa++;

        }
        a=false;

        VkUtils2::cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
    }


   

    //todo: Wake from callBack...
    

    
