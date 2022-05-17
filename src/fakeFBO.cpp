#include "fakeFBO.hpp"


void fakeFBO::doCommndRec()
{

  
      constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT) };

    constexpr VkRect2D renderArea = { .offset = { 0, 0 }, .extent = {854, 480} };


  
  static constexpr VkDeviceSize offsets[] = { 0 };
  uint32_t i = 0; 
  for(const VkCommandBuffer &commandBuffer : commandBuffers)
  {VkRenderPassAttachmentBeginInfo RenderPassAttachments
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO,
    .attachmentCount = 1,
    .pAttachments = &imageViews[i]
  };

  const VkRenderPassBeginInfo renderPassInfo = {
    .sType           = ( VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),
    .pNext = &RenderPassAttachments,
    .renderPass      = ( renderPass ),
    .framebuffer = ( frameBuffer ),
    .renderArea      = renderArea,
    // .clearValueCount = 1,
    // .pClearValues    = &clearValues2,
  };
  vkBeginCommandBuffer(commandBuffer, &beginInfo1 );


    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeLine );
    // vkCmdBindVertexBuffers(commandBuffer, 0, 1, &BuffersX::vertexBuffer, offsets );
    // vkCmdBindIndexBuffer(commandBuffer, BuffersX::indexBuffer, 0, VK_INDEX_TYPE_UINT16 );
     
    // vkCmdPushConstants(commandBuffer,vkLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, 64, &m4);

    // vkCmdBindDescriptorSets( commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineX::vkLayout, 0, 1, &UniformBufferObject::descriptorSets, 0, nullptr );


    vkCmdDraw( commandBuffer, ( 3), 1, 0, 0 );

    vkCmdEndRenderPass( commandBuffer );
    vkEndCommandBuffer( commandBuffer);
    i++;
  }
  // return commandBuffer;

}