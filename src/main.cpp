// #include "mat4.hpp"
#include "VkUtils2.hpp"
#include "renderer2.hpp"


#include <pthread.h>
#include <unistd.h>

#define ASAN_OPTIONS = debug=true



/*
    This is horribly Ported from  Prior Java version written with LWJGL 3 so May Suffer/Incur Considerable Breakage
    Assumed to compile and run with a 4790K and a GTX 1080Ti and may not be gurenteed to function on all  hardware configurations
    TODO:
        Use Imageless Framebuffers to cleanup the ugly setups used for the FrameBuffer/SwapChain
        Setup a proper VBO/Instancing setup tomallow seperage "Chunks" to be Added, removed and updated incrementally as needed
        Change GLM MAtrix Functions/Handling for built-in native setup with AVX/FMA3
        Allow Simple text.Temetry>Diganostics/Other data to be Displayed/Composited/rendered on Screen to avoid the need for the poential overhead needed for dedicated threads just to print to stdout

        Find a better setup than the Simulatneous submission used currently for Command Buffers to avoid additonal cpu overhead from submissions e.g.
        Setup dedicated Transfer Queue: (Apparently at least on Nvidia Thrasfer queus have a slightly higher Peak throught and effciency than the pther queue families )

    ISSUES:
        Slow Linking/COmpile Speed on incremental Changes/Compilations: nut sue if a CMAke/COmpiler/Clang64 /.Misc confiogurtaion ssue or due to the poor Linking layout/Hieracy.Namespace spam Used.utilsied which may be bogigng donw the linked eg.
            Should try on GCC.ICC and not just Clang
        Likely not gurenteed to Wokr/Compule;Function witH MSVC:-> 
            as while this has been compiled on Windows thsi was done however witH MSys2+ Clang64+ libc++ isnetad of teh more conventional MSVC+WIn10/8.1/7 SDk with libstdc++
            Also some specific extentions/Cpaboltirs/Macros/may not evaluate /Be Detected.Impleemt priperly (e.g. __int128, some specific intrinic hearer functions suchas __BiTScanForward64 Being Different on MSVC vs other Compilers/headers.Standardisations e.g. .Misc.Etc. I.E.)

        BuGS:
            If valditaion layers are not enbaled, the Vertex Buffers/Uniform buffers do not seem to be initialised/Added/Implemenetd curertcly with the Pipeline and etehrfore cannot be Boudn proeprly: 
                No issue were detected Asvertained.verifies witH AddressSantitiser so may ne anull,alignemnt,struct intilaistaion issue with mising/null-Initialised/Incorretcly Initilaised Fields
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
                std::cout << aa /* <<"--->"<< duration  */<< "\n";
                aa=0;
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
    

    
