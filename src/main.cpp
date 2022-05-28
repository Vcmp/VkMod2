
#include "renderer2.hpp"
#include "fakeFBO.hpp"

#include <cstdint>
#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <vulkan/vulkan_core.h>
inline namespace
{
  pthread_t sys;
  bool a = true;
  static uint32_t aa = 0;
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
    static constexpr auto tA(int a) -> int { return a*2; };

};
 
struct der_pod : public base_pod
{
    const int k;
};



constexpr der_pod dp{ {base_pod::tA(10) , 2}, 3 };
auto main() -> int
{
    printf("-->");
    std::cout <<(dp.i)<< "\n";
    // std::cout <<(VKI.tst())<< "\n";
    // VkInit give_me_a_name{VkInit::init(), VkInit::createInstance(), VkInit::createSurface(), VkInit::doPhysicalDevice(), VkInit::doDevice()};
    int r =  pthread_create( &sys, nullptr, Sysm, nullptr );

    // std::array<VkShaderModuleCreateInfo, 2> si{SPV.VsMCI3temp, SPV.VsMCI4temp};

    static constexpr VkAttachmentDescription colorAttachment{
    .format         = VK_FORMAT_B8G8R8A8_SRGB,  // SwapChainSupportDetails::swapChainImageFormat,
    .samples        = VK_SAMPLE_COUNT_1_BIT,
    .loadOp         = VK_ATTACHMENT_LOAD_OP_NONE_EXT,
    .storeOp        = VK_ATTACHMENT_STORE_OP_NONE, //Must be NONE, Not Don't Care to retain previous renderpass/Subpass/RenerPass/Subpass/Src Attachment e.g.
    .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
    .initialLayout  = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
    .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  };
  static constexpr VkAttachmentReference colorAttachmentRef{ .attachment = 0, .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
  static constexpr VkSubpassDescription  subpass{ .pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS,
                                                  .colorAttachmentCount = 1,
                                                  .pColorAttachments    = &colorAttachmentRef };

                                                  
  static constexpr VkSubpassDependency  VkSubpassDependency
  {
    .srcSubpass=VK_SUBPASS_CONTENTS_INLINE,
    .dstSubpass=VK_SUBPASS_CONTENTS_INLINE,
    .srcStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
    .dstStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
    .srcAccessMask=VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
    .dstAccessMask=VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT

  };

  constexpr VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
    //   .flags=VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,
    .attachmentCount = 1,
    .pAttachments    = &colorAttachment,
    .subpassCount    = 1,
    .pSubpasses      = &subpass,
    // .dependencyCount=1,
    // .pDependencies=&VkSubpassDependency
  };

  auto rs =  Vks::doPointerAlloc5<VkRenderPass>(&vkRenderPassCreateInfo1, vkCreateRenderPass );
    // const auto rs = SW.createRenderPass(VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL, true);
    // const auto fs = SW.frameBuffer;
    const auto pi2 = PX2.genPipeline({VsMCI3temp, VsMCI4temp}, rs, VK_CULL_MODE_NONE, 1);
    // std::cout << pi2 << "\n";

    fakeFBO fFBO
    {
      pi2, 
      PX2.genCommPool(), 
      rs, 
      SW.frameBuffer, 
      SW.imageViews,
      PX2.genLayout()
    };


    // fFBO.doCommBuffers();
    fFBO.doCommndRec();
    // PX2.genCommBuffers();
    std::cout << "VkInit" <<std::is_standard_layout_v<VkInit> << "\n";
    std::cout << "VkInit" <<std::is_trivially_copyable_v<VkInit> << "\n";
    std::cout << "VkInit" <<std::is_trivially_constructible_v<VkInit> << "\n";

    // std::cout << "fakeFBO" <<std::is_standard_layout<fakeFBO>::value << "\n";
    // std::cout << "fakeFBO" <<std::is_trivially_copyable<fakeFBO>::value << "\n";
    // std::cout << "fakeFBO" <<std::is_trivially_constructible<fakeFBO>::value << "\n";
    while(true)
    {
        // printf("%i \n", aa++);
        // glfwPollEvents();
        R2.drawFrame({PX2.commandBuffer[renderer2::currentFrame], fFBO.commandBuffers[renderer2::currentFrame]});
        aa++;
    }
    a= false;
 

}




void renderer2::drawFrame(std::initializer_list<VkCommandBuffer> commandBuffer) const
{
  // m4.loadAligned( &m5 );
  vkAcquireNextImageKHR( VKI.device, SW.swapChain, -1, R2.AvailableSemaphore, nullptr, &currentFrame );

  
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
              .pWaitSemaphores    = &AvailableSemaphore,
              .pWaitDstStageMask  = &t,
              .commandBufferCount = 2,
              .pCommandBuffers= commandBuffer.begin()
  };
    vkQueueSubmit( VKI.GraphicsQueue, 1, &info, nullptr );
  // }
    static constexpr VkPresentInfoKHR VkPresentInfoKHR1{ .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                                                    .pWaitSemaphores=&R2.FinishedSemaphore,
                                                                    .swapchainCount = 1,
                                                                    .pSwapchains    = &SW.swapChain,
                                                                    .pImageIndices  = &currentFrame,
                                                                    .pResults       = nullptr };


  //  info.pWaitSemaphores = &AvailableSemaphore;

 vkQueuePresentKHR( VKI.GraphicsQueue, &VkPresentInfoKHR1 );

  currentFrame = currentFrame + __builtin_parity( Frames );
}


