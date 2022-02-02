// #include "mat4.hpp"
#include "VkUtils2.hpp"
#include "renderer2.hpp"


#include <pthread.h>
#include <unistd.h>

// struct PStruct{
//      int *a;
// };

// using namespace VkU2;
  
//    private static boolean aa;
inline namespace{
    inline  bool a = true;
    static inline uint16_t aa;
     static inline pthread_t sys;
    static inline    pthread_t rThrd;
    // static    inline uint64_t duration;
    //  static   inline std::chrono::time_point<std::chrono::system_clock> startP;
    //  void * Sysm(void * pv_unused);
}
//Apparently Therads other main main therad have much smaller stall alloctaion Sizes...<Query-> Confirm>
inline void * Sysm(void * pv_unused)
   { _mm256_zeroall();
       while (a)
       {
            // duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-startP).count();
            // if(duration>1000)
            {
                std::cout << aa /* <<"--->"<< duration  */<< "\n";
                aa=0;
            //    startP = std::chrono::system_clock::now();
            }
            sleep(1);
       }
             return NULL;
   }
//    inline void * RDrw(void * pv_unused)
//    { _mm256_zeroall();
//        while (a)
//        {
//             // drawFrame();aa++;
//        }
//              return NULL;
//    }
     int __vectorcall main()
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
        // std::cout << __cplusplus << "\n";
        // std::cout << VULKAN_HPP_CPLUSPLUS << "\n";
        // std::cout << __cpp_lib_span << "\n";
        // std::cout << _LIBCPP_STD_VER << "\n";
		VkUtils2::extracted();
        // SwapChainSupportDetails::createSwapChain();
        // SwapChainSupportDetails::createImageViews();
        // Pipeline::createRenderPasses();
        // Pipeline::createGraphicsPipelineLayout();
        // Pipeline::createCommandPool();
        // static int axzl=10;
        int r;
       
        r=pthread_create(&sys, nullptr, Sysm, nullptr);
        // r=pthread_create(&rThrd, nullptr, RDrw, nullptr);
        
        //  pthread_join(sys, nullptr);
        setupRenderDraw();

        // static constexpr int aaa=1000;
         
    //    startP = std::chrono::system_clock::now(); 
       _mm256_zeroall();
       while (!glfwWindowShouldClose((window)))
        {
            // static constexpr PStruct ap
            // {
            //     .a=&aa
            // };
           
            
            //todo: setup Frame dbeugger setup heer to allow Frame-By=Frame Step through with Mosue.Lkeyboatd keys intandem with teh Versitile Callback featire provided by GLFW.
			// // extracted();
            // if (*ap.a==aaa)
            // {
    		// 	printf("%i \n", *ap.a);
            //     // ap.a=0;
            //     *ap.a=0;
            // }
            // pthread_join(rThrd, nullptr);
            glfwPollEvents();
            // glfwWaitEventsTimeout(1);
             drawFrame();aa++;
            // endP = std::chrono::system_clock::now();
            
            
			

        }
        a=false;glfwPostEmptyEvent();
        pthread_join(sys, nullptr);
        
        
        VkUtils2::cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
    }


  

    //todo: Wake from callBack...
    

    
