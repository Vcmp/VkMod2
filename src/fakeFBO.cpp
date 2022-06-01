#include "fakeFBO.hpp"
#include "GLFW/glfw3.h"
#include "Vks.tpp"
#include <vulkan/vulkan_core.h>

std::array<VkCommandBuffer, 3> fakeFBO::doGenCommnd()
{
  std::array<VkCommandBuffer, 3> PreTestBuffer{};
   const VkCommandBufferAllocateInfo allocateInfo{ .sType              =  VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ,
                                                  .commandPool        =  commandPool ,
                                                  .level              =  VK_COMMAND_BUFFER_LEVEL_PRIMARY ,
                                                  .commandBufferCount = 3};
  std::cout << allocateInfo.commandBufferCount << "Command Buffers"
            << "\n";
  vkAllocateCommandBuffers(VKI.device, &allocateInfo, PreTestBuffer.data() );
  return PreTestBuffer;
}


void fakeFBO::doCommndRec()
{

  
      constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags =  VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT };

    constexpr VkRect2D renderArea = { .offset = { 0, 0 }, .extent = {854, 480} };


  
  static constexpr VkDeviceSize offsets[] = { 0 };
  uint32_t i = 0; 

  const auto iTime = {static_cast<float>(glfwGetTime()), static_cast<float>(renderArea.extent.width), static_cast<float>(renderArea.extent.height)};

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
     
    vkCmdPushConstants(commandBuffer,layout, VK_SHADER_STAGE_FRAGMENT_BIT, 0, 12, iTime.begin());


    vkCmdDraw( commandBuffer, ( 6), 1, 0, 0 );

    vkCmdEndRenderPass( commandBuffer );
    vkEndCommandBuffer( commandBuffer);
    i++;
  }
  // return commandBuffer;

}