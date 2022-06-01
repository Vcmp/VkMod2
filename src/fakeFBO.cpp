#include "fakeFBO.hpp"
#include "GLFW/glfw3.h"
#include "Vks.tpp"
#include "glm/ext/vector_float2.hpp"
#include <vulkan/vulkan_core.h>

std::array<VkCommandBuffer, Frames> fakeFBO::doGenCommnd()
{
  std::array<VkCommandBuffer, Frames> PreTestBuffer{};
   const VkCommandBufferAllocateInfo allocateInfo{ .sType              =  VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ,
                                                  .commandPool        =  commandPool ,
                                                  .level              =  VK_COMMAND_BUFFER_LEVEL_PRIMARY ,
                                                  .commandBufferCount = Frames};
  std::cout << allocateInfo.commandBufferCount << "Command Buffers"
            << "\n";
  vkAllocateCommandBuffers(VKI.device, &allocateInfo, PreTestBuffer.data() );
  return PreTestBuffer;
}

struct ITime
{
  glm::vec2 xy;
  float time;
  float stime;
} __attribute__((aligned(16))) ;


void fakeFBO::doCommndRec()
{

  
      constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags =  VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT };

    constexpr VkRect2D renderArea = { .offset = { 0, 0 }, .extent = {width, height} };


  
  static constexpr VkDeviceSize offsets[] = { 0 };
  uint32_t i = 0; 
  const auto at = static_cast<float>(glfwGetTime());
  const ITime iTime = {{(renderArea.extent.width), (renderArea.extent.height)}, at, sinf(at)};

  for(const VkCommandBuffer &commandBuffer : commandBuffers)
  {VkRenderPassAttachmentBeginInfo RenderPassAttachments
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO,
    .attachmentCount = 1,
    .pAttachments = &imageViews[i]
  };

  const VkRenderPassBeginInfo renderPassInfo = {
    .sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ,
    .pNext = &RenderPassAttachments,
    .renderPass      = renderPass ,
    .framebuffer =  frameBuffer ,
    .renderArea      = renderArea,
    // .clearValueCount = 1,
    // .pClearValues    = &clearValues2,
  };
  vkBeginCommandBuffer(commandBuffer, &beginInfo1 );


    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeLine );
     
    vkCmdPushConstants(commandBuffer,layout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 16, &iTime);


    vkCmdDraw( commandBuffer, ( 6), 1, 0, 0 );

    vkCmdEndRenderPass( commandBuffer );
    vkEndCommandBuffer( commandBuffer);
    i++;
  }
  // return commandBuffer;

}