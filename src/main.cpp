
#include "GLFW/glfw3.h"
#include "renderer2.hpp"
#include "fakeFBO.hpp"
#include "SwapChain.hpp"
#include "Pipeline2.hpp"

#include <cstdint>
#include <cstdio>
#include <pthread.h>
#include <type_traits>
#include <unistd.h>


inline namespace
{
  pthread_t sys;
  bool a = true;
  static uint32_t aa = 0;
  // static mat4x m4;
  SwapChain SW;
  Pipeline2 PX2;
  renderer2 R2;
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

constexpr void chkTst(VkResult buh)
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
auto main() -> int
{
    printf("-->");
    std::cout <<(dp.i)<< "\n";
    std::cout <<(base_pod::tA(2))<< "\n";
    // VkInit give_me_a_name{VkInit::init(), VkInit::createInstance(), VkInit::createSurface(), VkInit::doPhysicalDevice(), VkInit::doDevice()};
    int r =  pthread_create( &sys, nullptr, Sysm, nullptr );

  //   // std::array<VkShaderModuleCreateInfo, 2> si{SPV.VsMCI3temp, SPV.VsMCI4temp};

  //   static constexpr VkAttachmentDescription colorAttachment{
  //   .format         = VK_FORMAT_B8G8R8A8_SRGB,  // SwapChainSupportDetails::swapChainImageFormat,
  //   .samples        = VK_SAMPLE_COUNT_1_BIT,
  //   .loadOp         = VK_ATTACHMENT_LOAD_OP_NONE_EXT,
  //   .storeOp        = VK_ATTACHMENT_STORE_OP_NONE, //Must be NONE, Not Don't Care to retain previous renderpass/Subpass/RenerPass/Subpass/Src Attachment e.g.
  //   .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
  //   .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
  //   .initialLayout  = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  //   .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  // };
  // static constexpr VkAttachmentReference colorAttachmentRef{ .attachment = 0, .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
  // static constexpr VkSubpassDescription  subpass{ .pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS,
  //                                                 .colorAttachmentCount = 1,
  //                                                 .pColorAttachments    = &colorAttachmentRef };

                                                  
  // static constexpr VkSubpassDependency  VkSubpassDependency
  // {
  //   .srcSubpass=VK_SUBPASS_CONTENTS_INLINE,
  //   .dstSubpass=VK_SUBPASS_CONTENTS_INLINE,
  //   .srcStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
  //   .dstStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
  //   .srcAccessMask=VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
  //   .dstAccessMask=VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT

  // };

  // constexpr VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {
  //   .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
  //   //   .flags=VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,
  //   .attachmentCount = 1,
  //   .pAttachments    = &colorAttachment,
  //   .subpassCount    = 1,
  //   .pSubpasses      = &subpass,
  //   // .dependencyCount=1,
  //   // .pDependencies=&VkSubpassDependency
  // };

  // auto rs =  Vks::doPointerAlloc5<VkRenderPass>(&vkRenderPassCreateInfo1, vkCreateRenderPass );
    // const auto rs = SW.createRenderPass(VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL, true);
    // const auto fs = SW.frameBuffer;
    auto pi2 = PX2.genPipeline({VsMCI3temp, VsMCI4temp}, SW.renderpass, VK_CULL_MODE_BACK_BIT, 1);
    // std::cout << pi2 << "\n";

    fakeFBO fFBO
    {
      pi2, 
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

    while(true)
    {
        // printf("%i \n", aa++);
        
        // vkQueueWaitIdle(VKI.GraphicsQueue);
        glfwPollEvents();
        // vkQueueWaitIdle(VKI.GraphicsQueue);
        // vkResetCommandBuffer(fFBO.commandBuffers[renderer2::currentFrame], VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
        fFBO.doCommndRec(renderer2::currentFrame);
        chkTst(vkResetFences(VKI.device, 1, &R2.fence[renderer2::currentFrame]));
        R2.drawFrame({fFBO.commandBuffers[renderer2::currentFrame]});
        aa++;
    }
    a= false;
 

}





void renderer2::drawFrame(std::initializer_list<VkCommandBuffer> commandBuffer) const
{
  // m4.loadAligned( &m5 );
  
 chkTst(vkAcquireNextImageKHR( VKI.tst(), SW.swapChain, 1000, R2.AvailableSemaphore[currentFrame], nullptr, &currentFrame ));
  
  
  // __builtin_prefetch( BuffersX::data );
  // __builtin_prefetch( &viewproj2x );
//  textTemp2.voidrecComBufferSub(currentFrame);
  // renderer2::updateUniformBuffer(); 

    // vkResetCommandPool(Queues::device, Queues::commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);


    // PipelineX::recCmdBuffer(currentFrame);

      // R2.info.pCommandBuffers =commandBuffer.data();
static constexpr VkPipelineStageFlags t=VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
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
  
    static const VkPresentInfoKHR VkPresentInfoKHR1{ .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                                                    .pWaitSemaphores=&FinishedSemaphore[currentFrame],
                                                                    .swapchainCount = 1,
                                                                    .pSwapchains    = &SW.swapChain,
                                                                    .pImageIndices  = &currentFrame,
                                                                    .pResults       = nullptr };


  //  info.pWaitSemaphores = &AvailableSemaphore;

 chkTst(vkQueuePresentKHR( VKI.GraphicsQueue, &VkPresentInfoKHR1 ));
          chkTst(vkWaitForFences(VKI.device, 1, &R2.fence[renderer2::currentFrame], false, 1000));

  currentFrame++;
  // currentFrame = ++currentFrame % Frames;
  if(currentFrame==Frames)
  {
    currentFrame=0;
  }
}




