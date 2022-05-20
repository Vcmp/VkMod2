
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
  static mat4x m4;
}

inline void * Sysm( void * pv_unused )
{
  while ( a )
  {
    std::cout << aa /* <<"--->"<< duration  */ << "\n";
    // std::cout << cc /* <<"--->"<< duration  */ << "\n";
    // m4.loadAligned( BuffersX::data );
    m4.show();
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
    std::cout <<(dp.i)<< "\n";
    // std::cout <<(VKI.tst())<< "\n";
    // VkInit give_me_a_name{VkInit::init(), VkInit::createInstance(), VkInit::createSurface(), VkInit::doPhysicalDevice(), VkInit::doDevice()};
    int r =  pthread_create( &sys, nullptr, Sysm, nullptr );

    // std::array<VkShaderModuleCreateInfo, 2> si{SPV.VsMCI3temp, SPV.VsMCI4temp};
/*     const auto rs = SW.createRenderPass(VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
    const auto fs = SW.createFramebuffers(rs);
    const auto pi2 = PX2.genPipeline({ShaderSPIRVUtils::VsMCI3temp, ShaderSPIRVUtils::VsMCI4temp}, rs, VK_CULL_MODE_NONE, 1);
 */    // std::cout << pi2 << "\n";

/*     fakeFBO fFBO
    {
      pi2, 
      PX2.genCommPool(), 
      rs, 
      fs, 
      SW.createImageViews(),
      PX2.genLayout()
    };
 */

    // fFBO.doCommBuffers();
    // fFBO.doCommndRec();
    // PX2.genCommBuffers();
    std::cout << "VkInit" <<std::is_standard_layout_v<VkInit> << "\n";
    std::cout << "VkInit" <<std::is_trivially_copyable_v<VkInit> << "\n";
    std::cout << "VkInit" <<std::is_trivially_constructible_v<VkInit> << "\n";

    std::cout << "fakeFBO" <<std::is_standard_layout<fakeFBO>::value << "\n";
    std::cout << "fakeFBO" <<std::is_trivially_copyable<fakeFBO>::value << "\n";
    std::cout << "fakeFBO" <<std::is_trivially_constructible<fakeFBO>::value << "\n";
    while(true)
    {
        // printf("%i \n", aa++);
        // glfwPollEvents();
        R2.drawFrame(PX2.commandBuffer[renderer2::currentFrame]);
        aa++;
    }
    a= false;
 

}

