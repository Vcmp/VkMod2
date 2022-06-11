#include "Pipeline2.hpp"



auto Pipeline2::doGenCommnd() -> std::array<VkCommandBuffer, Frames>
{
  std::array<VkCommandBuffer, Frames> PreTestBuffer{};
   const VkCommandBufferAllocateInfo allocateInfo{ .sType              =  VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ,
                                                  .commandPool        =  commandPool ,
                                                  .level              =  VK_COMMAND_BUFFER_LEVEL_PRIMARY ,
                                                  .commandBufferCount = Frames};
  std::cout << allocateInfo.commandBufferCount << "Command Buffers"
            << "\n";
  vkAllocateCommandBuffers(volkGetLoadedDevice(), &allocateInfo, PreTestBuffer.data() );
  return PreTestBuffer;
}

// void Pipeline2::genCommBuffers()
// {

  
//       constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
//                                                     .flags = ( VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT) };

//     constexpr VkRect2D renderArea = { .offset = { 0, 0 }, .extent = {width, height} };


  
//   static constexpr VkDeviceSize offsets[] = { 0 };
//   uint32_t i = 0; 
// mat4x m4;
// m4.loadAligned(viewproj);

//   for ( const VkCommandBuffer & commandBuffer : commandBuffer )
//   {VkRenderPassAttachmentBeginInfo RenderPassAttachments
//   {
//     .sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO,
//     .attachmentCount = 1,
//     .pAttachments = &SW.imageViews[i]
//   };

//   const VkRenderPassBeginInfo renderPassInfo = {
//     .sType           = ( VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),
//     .pNext = &RenderPassAttachments,
//     .renderPass      = ( SW.renderpass ),
//     .framebuffer = ( SW.frameBuffer ),
//     .renderArea      = renderArea,
//     .clearValueCount = 0,
//     .pClearValues    = nullptr,
//   };
  
//   vkBeginCommandBuffer(commandBuffer, &beginInfo1 );


//     vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

//     vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,pipeline );
//     vkCmdBindVertexBuffers(commandBuffer, 0, 1, &BuffersX::vertexBuffer, offsets );
//     vkCmdBindIndexBuffer(commandBuffer, BuffersX::indexBuffer, 0, VK_INDEX_TYPE_UINT16 );
     
//     vkCmdPushConstants(commandBuffer,vkLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, 64, &m4);

//     // vkCmdBindDescriptorSets( commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineX::vkLayout, 0, 1, &UniformBufferObject::descriptorSets, 0, nullptr );


//     vkCmdDrawIndexed( commandBuffer, ( ( BuffersX::sizedsfIdx ) / 2 ), 1, 0, 0, 0 );

//     vkCmdEndRenderPass( commandBuffer );
//     vkEndCommandBuffer( commandBuffer);
//     i++;
//   }
//   // return commandBuffer;

// }

auto Pipeline2::genCommPool() const -> VkCommandPool
{
 constexpr VkCommandPoolCreateInfo  poolInfo = {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
    .queueFamilyIndex = 0,
  };
  return Vks::doPointerAlloc5<VkCommandPool>( &poolInfo, vkCreateCommandPool );
 
}


auto Pipeline2::genLayout() const -> VkPipelineLayout
{
  
  static constexpr VkPushConstantRange vkPushConstantRange{
    .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
    .offset     = 0,
    .size       = 16,
  };

  constexpr VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo = { .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                                     /*  . setLayoutCount         = 1,
                                                                      .pSetLayouts            = &UniformBufferObject::descriptorSetLayout, */
                                                                      .pushConstantRangeCount = 1,
                                                                      .pPushConstantRanges    = &vkPushConstantRange };

  // std::cout << ( "using pipeLine with Length: " ) << sizeof( SwapChainSupportDetails::swapChainImageViews );
  return Vks::doPointerAlloc5<VkPipelineLayout>( &vkPipelineLayoutCreateInfo, vkCreatePipelineLayout);
}