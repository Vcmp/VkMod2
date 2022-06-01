
#include "test.inl"
#include <array>
#include <initializer_list>
#include "SwapChain.hpp"

#include "Buffers.hpp"
#include "Queues.hpp"


 static constexpr uint8_t OFFSETOF_COLOR = 3 * sizeof( float );
  static constexpr uint8_t OFFSET_POS     = 0;

constexpr VkViewport vkViewport{ .x = 0.0F, .y = 0.0F, .width = width, .height = height, .minDepth = 0.0F, .maxDepth = 1.0F };

constexpr VkRect2D scissor{ .offset = { 0, 0 }, .extent{ width, height } };

constexpr std::array<VkShaderModuleCreateInfo, 2> shaderStages2{VsMCI, VsMCI2};

static struct Pipeline2
{
     VkPipelineLayout vkLayout=genLayout();
     VkPipeline pipeline;
     VkCommandPool commandPool;
     std::array<VkCommandBuffer, Frames>commandBuffer;
    //constexpr Pipeline2(): pipeline(genPipeline(shaderStages2, SW.renderpass, VK_CULL_MODE_NONE, -1)), commandPool(genCommPool()), commandBuffer(doCommBuffers()){genCommBuffers();};
    constexpr auto genPipeline(const std::array<VkShaderModuleCreateInfo, 2>&, VkRenderPass, VkCullModeFlagBits, int32_t) const -> VkPipeline;
    void genCommBuffers();
   [[nodiscard]] auto genCommPool() const -> VkCommandPool;
   [[nodiscard]] auto doCommBuffers() const -> std::array<VkCommandBuffer, Frames>;
   [[nodiscard]] auto genLayout() const -> VkPipelineLayout;
   [[nodiscard]] constexpr auto genShaderPiplineStage(VkShaderModuleCreateInfo, VkShaderStageFlagBits) const -> VkPipelineShaderStageCreateInfo;
} __attribute__((aligned(64))) PX2;

    constexpr auto Pipeline2::genShaderPiplineStage(VkShaderModuleCreateInfo a, VkShaderStageFlagBits stageFlag) const -> VkPipelineShaderStageCreateInfo
    {
      
        
        return {
          .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
          .stage  = stageFlag,
          .module = Vks::doPointerAllocX2<VkShaderModule>( &a),
          .pName  = "main",

        };
    }

constexpr auto Pipeline2::genPipeline(const std::array<VkShaderModuleCreateInfo, 2>& shaderStages2, VkRenderPass renderPass, VkCullModeFlagBits cullMode, int32_t baseIndex) const -> VkPipeline
{
    // Thankfully Dont; need to worry about compiling the Shader Files AnyMore due
  // to teh ability to premptively use the SPRI-V Compielr (e.g.GLSLC) prior to compile time...
  // std::cout << ( "Setting up PipeLine" ) << "\n";

  auto vertexStage = genShaderPiplineStage(shaderStages2[0], VK_SHADER_STAGE_VERTEX_BIT);
  auto fragStage = genShaderPiplineStage(shaderStages2[1], VK_SHADER_STAGE_FRAGMENT_BIT);
  
  const VkPipelineShaderStageCreateInfo shaderStages[] = { fragStage, vertexStage};

   constexpr VkVertexInputBindingDescription VxL{ 0, ( 24 ), VK_VERTEX_INPUT_RATE_VERTEX };

   constexpr VkVertexInputAttributeDescription attributeDescriptions[2]{
      { .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = OFFSET_POS },
    { .location = 2, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = OFFSETOF_COLOR },
    // { .location = 3, .binding = 0, .format = VK_FORMAT_R32G32_SFLOAT, .offset = 0 },
    // { .location = 4, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = sizeof(float) * 2}
  };

    VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo = {
    .sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .vertexBindingDescriptionCount   = 0,
    .pVertexBindingDescriptions      = nullptr,
    .vertexAttributeDescriptionCount = 0,
    .pVertexAttributeDescriptions    = nullptr
  };

   constexpr VkPipelineInputAssemblyStateCreateInfo inputAssembly = { .sType    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
                                                                            .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
                                                                            .primitiveRestartEnable = VK_FALSE };


  constexpr VkPipelineViewportStateCreateInfo vkViewPortState = {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, .viewportCount = 1, .pViewports = &vkViewport, .scissorCount = 1, .pScissors = &scissor
  };

  const VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization = {
    .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .depthClampEnable        = VK_FALSE,
    .rasterizerDiscardEnable = VK_FALSE,
    .polygonMode             = VK_POLYGON_MODE_FILL,
    .cullMode                = cullMode,  // WARNING: VERY IMPORTANT!:
                                                       // Make sure the culling direction is correct
                                                       // as it applies even to 2DVecs/Fixed
                                                       // Function Runtime/Evaluated Shaders
                                                       // with no transforms and with fixed
                                                       // Const/Pre-Determined Runtime
                                                       // Variables
    .frontFace       = VK_FRONT_FACE_COUNTER_CLOCKWISE,
    .depthBiasEnable = VK_FALSE,
    .lineWidth       = 1.0F,
  };

  constexpr VkPipelineMultisampleStateCreateInfo multisampling = { .sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
                                                                   .rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT,
                                                                   .sampleShadingEnable   = VK_FALSE,
                                                                   .minSampleShading      = 1.0F,
                                                                   .pSampleMask           = VK_NULL_HANDLE,
                                                                   .alphaToCoverageEnable = VK_FALSE,
                                                                   .alphaToOneEnable      = VK_FALSE };

  constexpr VkPipelineDepthStencilStateCreateInfo depthStencil = {
    .sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .depthTestEnable       = VK_FALSE,
    .depthWriteEnable      = VK_FALSE,
    .depthCompareOp        = VK_COMPARE_OP_EQUAL,
    .depthBoundsTestEnable = VK_FALSE,
    .stencilTestEnable     = VK_FALSE,
  };
   constexpr VkPipelineColorBlendAttachmentState colorBlendAttachment = {
    .blendEnable    = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,

  };
   VkPipelineColorBlendStateCreateInfo colorBlending = {
    .sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .logicOpEnable   = VK_FALSE,
    .logicOp         = VK_LOGIC_OP_COPY,
    .attachmentCount = 1,
    .pAttachments    = &colorBlendAttachment,

  };


  const VkGraphicsPipelineCreateInfo pipelineInfo{ .sType      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                                                   .stageCount = 2,
                                                   .pStages    = shaderStages,
                                                   // .pNext=VK_NULL_HANDLE,
                                                   .pVertexInputState   = &vkPipelineVertexInputStateCreateInfo,
                                                   .pInputAssemblyState = &inputAssembly,
                                                   .pViewportState      = &vkViewPortState,
                                                   .pRasterizationState = &VkPipeLineRasterization,
                                                   .pMultisampleState   = &multisampling,
                                                   .pDepthStencilState  = &depthStencil,
                                                   .pColorBlendState    = &colorBlending,
                                                   .layout              = vkLayout,
                                                   .renderPass          = renderPass,
                                                   .basePipelineIndex=baseIndex};

  return Vks::doPointerAllocX<VkPipeline>(&pipelineInfo);
}

auto  Pipeline2::doCommBuffers() const -> std::array<VkCommandBuffer, Frames>
{
  Queues::createCommandPool();
  BuffersX::setupBuffers();
  std::array<VkCommandBuffer, Frames> PreTestBuffer{};
   const VkCommandBufferAllocateInfo allocateInfo{ .sType              = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
                                                  .commandPool        = ( commandPool ),
                                                  .level              = ( VK_COMMAND_BUFFER_LEVEL_PRIMARY ),
                                                  .commandBufferCount = 3};
  std::cout << allocateInfo.commandBufferCount << "Command Buffers"
            << "\n";
  vkAllocateCommandBuffers(VKI.tst(), &allocateInfo, PreTestBuffer.data() );
  return PreTestBuffer;
}

void Pipeline2::genCommBuffers()
{

  
      constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT) };

    constexpr VkRect2D renderArea = { .offset = { 0, 0 }, .extent = {width, height} };


  
  static constexpr VkDeviceSize offsets[] = { 0 };
  uint32_t i = 0; 
mat4x m4;
m4.loadAligned(viewproj);

  for ( const VkCommandBuffer & commandBuffer : commandBuffer )
  {VkRenderPassAttachmentBeginInfo RenderPassAttachments
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO,
    .attachmentCount = 1,
    .pAttachments = &SW.imageViews[i]
  };

  const VkRenderPassBeginInfo renderPassInfo = {
    .sType           = ( VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),
    .pNext = &RenderPassAttachments,
    .renderPass      = ( SW.renderpass ),
    .framebuffer = ( SW.frameBuffer ),
    .renderArea      = renderArea,
    .clearValueCount = 0,
    .pClearValues    = nullptr,
  };
  
  vkBeginCommandBuffer(commandBuffer, &beginInfo1 );


    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,pipeline );
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, &BuffersX::vertexBuffer, offsets );
    vkCmdBindIndexBuffer(commandBuffer, BuffersX::indexBuffer, 0, VK_INDEX_TYPE_UINT16 );
     
    vkCmdPushConstants(commandBuffer,vkLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, 64, &m4);

    // vkCmdBindDescriptorSets( commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineX::vkLayout, 0, 1, &UniformBufferObject::descriptorSets, 0, nullptr );


    vkCmdDrawIndexed( commandBuffer, ( ( BuffersX::sizedsfIdx ) / 2 ), 1, 0, 0, 0 );

    vkCmdEndRenderPass( commandBuffer );
    vkEndCommandBuffer( commandBuffer);
    i++;
  }
  // return commandBuffer;

}

auto Pipeline2::genCommPool() const -> VkCommandPool
{
 constexpr VkCommandPoolCreateInfo  poolInfo = {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
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