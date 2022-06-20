
#include "renderer2.hpp"
#include "fakeFBO.hpp"
#include "SwapChain.hpp"
#include "Pipeline2.hpp"


#include <iostream>
#include <pthread.h>

#include <unistd.h>
#include <windef.h>
#include <winnt.h>
#include <winuser.h>


inline namespace
{
 
  pthread_t sys;
  bool a = true;
   uint32_t aa = 0;
   uint32_t tmSecs = 0;
  // static mat4x m4;
 
}

inline void * Sysm( void * pv_unused )
{
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
    static consteval auto tA(int a) -> int { return a*2; };

};
 
struct der_pod : public base_pod
{
    const int k;
};

constexpr void chkTst(VkResult buh) noexcept
{
  if constexpr(checks)
  {
      switch (buh) 
      {
        case VK_NOT_READY:  std::cout << "VK_NOT_READY" << "\n"; break;
        case VK_TIMEOUT: std::cout << "VK_TIMEOUT" << "\n"; break;
        case VK_EVENT_SET: std::cout << "VK_EVENT_SET" << "\n"; break;
        case VK_EVENT_RESET: std::cout << "VK_EVENT_RESET" << "\n"; break;
        case VK_INCOMPLETE: std::cout << "VK_INCOMPLETE" << "\n"; break;
        case VK_ERROR_OUT_OF_HOST_MEMORY: std::cout << "VK_ERROR_OUT_OF_HOST_MEMORY" << "\n"; break;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY: std::cout << "VK_ERROR_OUT_OF_DEVICE_MEMORY" << "\n"; break;
        case VK_ERROR_INITIALIZATION_FAILED: std::cout << "VK_ERROR_INITIALIZATION_FAILED" << "\n"; break;
        case VK_ERROR_DEVICE_LOST: std::cout << "VK_ERROR_DEVICE_LOST" << "\n"; break;
        case VK_ERROR_MEMORY_MAP_FAILED: std::cout << "VK_ERROR_MEMORY_MAP_FAILED" << "\n"; break;
        case VK_ERROR_LAYER_NOT_PRESENT: std::cout << "VK_ERROR_LAYER_NOT_PRESENT" << "\n"; break;
        case VK_ERROR_EXTENSION_NOT_PRESENT: std::cout << "VK_ERROR_EXTENSION_NOT_PRESENT" << "\n"; break;
        case VK_ERROR_FEATURE_NOT_PRESENT: std::cout << "VK_ERROR_FEATURE_NOT_PRESENT" << "\n"; break;
        case VK_ERROR_INCOMPATIBLE_DRIVER: std::cout << "VK_ERROR_INCOMPATIBLE_DRIVER" << "\n"; break;
        case VK_ERROR_TOO_MANY_OBJECTS: std::cout << "VK_ERROR_TOO_MANY_OBJECTS" << "\n"; break;
        case VK_ERROR_FORMAT_NOT_SUPPORTED: std::cout << "VK_ERROR_FORMAT_NOT_SUPPORTED" << "\n"; break;
        case VK_ERROR_FRAGMENTED_POOL: std::cout << "VK_ERROR_FRAGMENTED_POOL" << "\n"; break;
        case VK_ERROR_UNKNOWN: std::cout << "VK_ERROR_UNKNOWN" << "\n"; break;
        case VK_ERROR_OUT_OF_POOL_MEMORY: std::cout <<"VK_ERROR_OUT_OF_POOL_MEMORY" << "\n"; break;
        case VK_ERROR_INVALID_EXTERNAL_HANDLE: std::cout <<"VK_ERROR_INVALID_EXTERNAL_HANDLE" << "\n"; break;
        case VK_ERROR_FRAGMENTATION: std::cout <<"VK_ERROR_FRAGMENTATION" << "\n"; break;
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: std::cout <<"VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS" << "\n"; break;
        case VK_PIPELINE_COMPILE_REQUIRED: std::cout <<"VK_PIPELINE_COMPILE_REQUIRED" << "\n"; break;
        case VK_ERROR_SURFACE_LOST_KHR: std::cout <<"VK_ERROR_SURFACE_LOST_KHR" << "\n"; break;
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: std::cout <<"VK_ERROR_NATIVE_WINDOW_IN_USE_KHR" << "\n"; break;
        case VK_SUBOPTIMAL_KHR: std::cout <<"VK_SUBOPTIMAL_KHR" << "\n"; break;
        case VK_ERROR_OUT_OF_DATE_KHR: std::cout <<"VK_ERROR_OUT_OF_DATE_KHR" << "\n"; break;
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: std::cout <<"VK_ERROR_INCOMPATIBLE_DISPLAY_KHR" << "\n"; break;
        case VK_ERROR_VALIDATION_FAILED_EXT: std::cout <<"VK_ERROR_VALIDATION_FAILED_EXT" << "\n"; break;
        case VK_ERROR_INVALID_SHADER_NV: std::cout <<"VK_ERROR_INVALID_SHADER_NV" << "\n"; break;
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: std::cout <<"VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT" << "\n"; break;
        case VK_ERROR_NOT_PERMITTED_KHR: std::cout <<"VK_ERROR_NOT_PERMITTED_KHR" << "\n"; break;
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: std::cout <<"VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT" << "\n"; break;
        case VK_THREAD_IDLE_KHR: std::cout <<"VK_THREAD_IDLE_KHR" << "\n"; break;
        case VK_THREAD_DONE_KHR: std::cout <<"VK_THREAD_DONE_KHR" << "\n"; break;
        case VK_OPERATION_DEFERRED_KHR: std::cout <<"VK_OPERATION_DEFERRED_KHR" << "\n"; break;
        case VK_OPERATION_NOT_DEFERRED_KHR: std::cout <<"VK_OPERATION_NOT_DEFERRED_KHR" << "\n"; break;
      
        default: return;
        // case VK_SUCCESS: { return;}
      }
      exit(1);
  }


}

constexpr der_pod dp{ {base_pod::tA(10) , 2}, 3 };
int WinMain(HINSTANCE instance, int v)
{
    printf("-->");
    std::cout <<(dp.i)<< "\n";
    std::cout <<(base_pod::tA(2))<< "\n";
    // VkInit give_me_a_name{VkInit::init(), VkInit::createInstance(), VkInit::createSurface(), VkInit::doPhysicalDevice(), VkInit::doDevice()};
    // int r =  pthread_create( &sys, nullptr, Sysm, nullptr );
  mat4x m4;
  mat4x m5;
  // float a = m4[0];
  // m4[0]=a;

  m4.identity();
  std::cout << &m4 << "\n";
  for(auto a =0; a<sizeof(m4)/sizeof(float); a++)
  {
    if(!(a&3))
    {
      std::cout  << "\n";
    }
    std::cout << m4[a];
  }
   static const VkInit VKI(instance);
   Vks::Device=VKI.tst();
  static const SwapChain SW(VKI.physdevice, VKI.surface);
  static const Pipeline2 PX2;
  static const renderer2 R2;                                   
  
    const auto pi1 = PX2.genPipeline({VsMCI3temp, VsMCI2}, SW.renderpass, VK_CULL_MODE_BACK_BIT, 1);
    const auto pi2 = PX2.genPipeline({VsMCI3temp, VsMCI4temp}, SW.renderpass, VK_CULL_MODE_BACK_BIT, 1);

    static const fakeFBO fFBO
    {
      pi2, 
      PX2.commandPool, 
      SW.renderpass, 
      SW.frameBuffer, 
      SW.imageViews,
      PX2.vkLayout,
      PX2.commandBuffer
    };
    // auto x = PX2.genCommPool();
static const fakeFBO fFBO1
    {
      pi1, 
      PX2.commandPool, 
      SW.renderpass, 
      SW.frameBuffer, 
      SW.imageViews,
      PX2.vkLayout,
      PX2.commandBuffer
    };


    // fFBO.doCommBuffers();
    
    // PX2.genCommBuffers();
    std::cout << "VkInit" <<std::is_standard_layout_v<VkInit> << "\n";
    std::cout << "VkInit" <<std::is_trivially_copyable_v<VkInit> << "\n";
    std::cout << "VkInit" <<std::is_trivially_constructible_v<VkInit> << "\n";

    std::cout << "fakeFBO" <<std::is_standard_layout_v<fakeFBO> << "\n";
    std::cout << "fakeFBO" <<std::is_trivially_copyable_v<fakeFBO> << "\n";
    std::cout << "fakeFBO" <<std::is_trivially_constructible_v<fakeFBO> << "\n";

      
    while(IsWindow(VKI.window))
    {
      static LPMSG msg;
      static DWORD prevTime;
     
        const auto x = clock();
        if(tmSecs%10==0)
        {
        fFBO.doCommndRec(renderer2::currentFrame, x);
        chkTst(vkResetFences(VKI.device, 1, &R2.fence[renderer2::currentFrame]));
          R2.drawFrame(VKI, SW, {fFBO.commandBuffers[renderer2::currentFrame]});
        }
        else 
        {
        fFBO1.doCommndRec(renderer2::currentFrame, x);
        chkTst(vkResetFences(VKI.device, 1, &R2.fence[renderer2::currentFrame]));
          R2.drawFrame(VKI, SW, {fFBO1.commandBuffers[renderer2::currentFrame]});
        }
        aa++;
        
          PeekMessageA(msg, VKI.window, WM_KEYFIRST, WM_MOVING, PM_REMOVE);
          
        if(prevTime+CLOCKS_PER_SEC<clock())
        {
          tmSecs++;
        prevTime=x;
          std::cout << aa << "\n";
          aa=0;
        }
    }
    a= false;
 

}





constexpr void renderer2::drawFrame(VkInit const &__restrict__ VKI, SwapChain const &__restrict__ SW, std::initializer_list<VkCommandBuffer> commandBuffer) const
{
  // m4.loadAligned( &m5 );
  if(IsHungAppWindow(VKI.window))
  {
    std::cout << "HUNG!" << "\n";
  }
 chkTst(vkAcquireNextImageKHR( VKI.tst(), SW.swapChain, 1000, AvailableSemaphore[currentFrame], nullptr, &currentFrame ));
  
  
  // __builtin_prefetch( BuffersX::data );
  // __builtin_prefetch( &viewproj2x );
//  textTemp2.voidrecComBufferSub(currentFrame);
  // renderer2::updateUniformBuffer(); 

    // vkResetCommandPool(Queues::device, Queues::commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);


    // PipelineX::recCmdBuffer(currentFrame);

      // R2.info.pCommandBuffers =commandBuffer.data();
constexpr VkPipelineStageFlags t=VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
      const  VkSubmitInfo           info{
              .sType              = VK_STRUCTURE_TYPE_SUBMIT_INFO,
              .waitSemaphoreCount = 1,
              .pWaitSemaphores    = &AvailableSemaphore[currentFrame],
              .pWaitDstStageMask  = &t,
              .commandBufferCount = 1,
              .pCommandBuffers= commandBuffer.begin()
  };
    chkTst(vkQueueSubmit( VKI.GraphicsQueue, 1, &info, fence[currentFrame] ));
  // }
  
    const VkPresentInfoKHR VkPresentInfoKHR1{ .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                                                    .pWaitSemaphores=&FinishedSemaphore[currentFrame],
                                                                    .swapchainCount = 1,
                                                                    .pSwapchains    = &SW.swapChain,
                                                                    .pImageIndices  = &currentFrame,
                                                                    .pResults       = nullptr };


  //  info.pWaitSemaphores = &AvailableSemaphore;

 chkTst(vkQueuePresentKHR( VKI.GraphicsQueue, &VkPresentInfoKHR1 ));

          chkTst(vkWaitForFences(VKI.device, 1, &fence[currentFrame], false, -1)); //This is Unstable and 1000 TiemOut+ all efnce wait only work/wfunctions/behaves rleibly of the Swapchian dpeth is at the Maixmum supprtted at 8 FrameChain?SwapChian?faremBuffer Dpeth/ Octule/OctupleBuffered
  currentFrame++;
  currentFrame&=0x7;
}




