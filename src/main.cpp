// #include "mat4.hpp"
#include "VkUtils2.hpp"
#include "renderer2.hpp"


#include <pthread.h>
#include <unistd.h>





/*
    This is horribly Ported from  Prior Java version written with LWJGL 3 so May Suffer/Incur Considerable Breakage
*/






inline namespace{
    inline  bool a = true;
    static inline uint16_t aa;
     static inline pthread_t sys;
    static inline    pthread_t rThrd;
}
//Apparently Threads other main main therad have much smaller stall alloctaion Sizes...<Query-> Confirm>
inline void * Sysm(void * pv_unused)
   { 
       _mm256_zeroall();
       while (a)
       {
            {
                std::cout << aa /* <<"--->"<< duration  */<< "\n";
                aa=0;
            }
            sleep(1);
       }
             return NULL;
   }

int __vectorcall main()
    {
		VkUtils2::extracted();
        int r;
       
        r=pthread_create(&sys, nullptr, Sysm, nullptr);
        setupRenderDraw();
       _mm256_zeroall();
       while (!glfwWindowShouldClose((window)))
        {
            glfwPollEvents();
            // glfwWaitEventsTimeout(1);
             drawFrame();aa++;
            
            
			

        }
        a=false;glfwPostEmptyEvent();
        pthread_join(sys, nullptr);
        
        
        VkUtils2::cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
    }


  

    //todo: Wake from callBack...
    

    
