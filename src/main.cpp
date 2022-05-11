
#include "renderer2.hpp"
#include <array>
#include <pthread.h>
#include <type_traits>
#include <unistd.h>
#include <iostream>
#include <vulkan/vulkan_core.h>

namespace
{
  pthread_t sys;
  bool a = true;
static uint32_t aa = 0;
}

inline void * Sysm( void * pv_unused )
{
  // _mm256_zeroall();
  while ( a )
  {
    std::cout << aa /* <<"--->"<< duration  */ << "\n";
    // std::cout << cc /* <<"--->"<< duration  */ << "\n";
    // m4.loadAligned( BuffersX::data );
    // m4.show();
    aa = 0;
    sleep( 1 );
  }
  return nullptr;
}

struct base_pod
{
    const int i, j;
    // constexpr base_pod( int i1, int j1): i(i1), j(j1) {};
    static constexpr auto tA(int a) -> int { return a*2; };

};
 
struct der_pod : public base_pod
{
    const int k;
};

constexpr der_pod dp{ {base_pod::tA(10) , 2}, 3 };
int main()
{
    printf("-->");
    // std::cout <<(VKI.device)<< "\n";
    // std::cout <<(SW.imageCount)<< "\n";
    std::cout <<(dp.i)<< "\n";
    // std::cout <<(VKI.tst())<< "\n";
    // VkInit give_me_a_name{VkInit::init(), VkInit::createInstance(), VkInit::createSurface(), VkInit::doPhysicalDevice(), VkInit::doDevice()};
    int r =  pthread_create( &sys, nullptr, Sysm, nullptr );

    // std::array<VkShaderModuleCreateInfo, 2> si{SPV.VsMCI3temp, SPV.VsMCI4temp};
    auto pi2 = PX2.genPipeline({SPV.VsMCI3temp, SPV.VsMCI4temp}, SW.renderpass, VK_CULL_MODE_NONE, 1);
   
    std::cout << pi2 << "\n";
    // PX2.genCommBuffers();
    std::cout << "VkInit" <<std::is_standard_layout<VkInit>::value << "\n";
    std::cout << "VkInit" <<std::is_trivially_copyable<VkInit>::value << "\n";
    std::cout << "VkInit" <<std::is_trivially_constructible<VkInit>::value << "\n";
    while(true)
    {
        // printf("%i \n", aa++);
        glfwPollEvents();
        R2.drawFrame();
        aa++;
    }
    a= false;
 

}

