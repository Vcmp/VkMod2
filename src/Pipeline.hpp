#pragma once
// #include "SwapChainSupportDetails.hpp"
#include "ShaderSPIRVUtils.hpp"
#include "UniformBufferObject.hpp"
#include "src/UniformBufferObject.hpp"
#include "src/mat4x.hpp"

struct PipelineX
{
private:
  static constexpr int OFFSETOF_COLOR = 3 * sizeof( float );
  static constexpr int OFFSET_POS     = 0;

  static constexpr int           OFFSETOF_TEXTCOORDS = ( 3 + 3 ) * sizeof( float );
  static constexpr float         UNormFlt            = 0.1F;
  static inline VkPipelineLayout vkLayout;
  static inline VkPipeline       graphicsPipeline;

public:
  static inline VkCommandBuffer commandBuffers[Frames];
  inline static void            createGraphicsPipelineLayout();
  inline static void            createCommandBuffers();
};

VkFormat findDepthFormat()
{
  constexpr VkFormat formatCandidates[3] = { VK_FORMAT_D32_SFLOAT,
                                             VK_FORMAT_D32_SFLOAT_S8_UINT,
                                             VK_FORMAT_D24_UNORM_S8_UINT };
  VkFormatProperties props;

  for ( const VkFormat & format : formatCandidates )
  {
    vkGetPhysicalDeviceFormatProperties( Queues::physicalDevice, format, &props );

    const int i2 = props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;
    if (
      i2 ==
      VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT /* && VK10.VK_IMAGE_TILING_OPTIMAL == VK_IMAGE_TILING_OPTIMAL*/ )
    {
      return format;
    }
  }

  throw std::runtime_error( "failed to find supported format!" );
}

inline static void createRenderPasses()
{
  static const VkAttachmentDescription colorAttachment{
    .format         = VK_FORMAT_B8G8R8A8_SRGB,  // SwapChainSupportDetails::swapChainImageFormat,
    .samples        = VK_SAMPLE_COUNT_1_BIT,
    .loadOp         = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .storeOp        = VK_ATTACHMENT_STORE_OP_STORE,
    .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
    .initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED,
    .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  };
  static constexpr VkAttachmentReference colorAttachmentRef{ .attachment = 0,
                                                             .layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
  static constexpr VkSubpassDescription  subpass{ .pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS,
                                                  .colorAttachmentCount = 1,
                                                  .pColorAttachments    = &colorAttachmentRef };

  constexpr VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
    //   .flags=VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,
    .attachmentCount = 1,
    .pAttachments    = &colorAttachment,
    .subpassCount    = 1,
    .pSubpasses      = &subpass,
    // .dependencyCount=1,
    // .pDependencies=&dependency
  };

  clPPPI( &vkRenderPassCreateInfo1, "vkCreateRenderPass", &SwapChainSupportDetails::renderPass );
}

inline void PipelineX::createGraphicsPipelineLayout()
{
  // Thankfully Dont; need to worry about compiling the Shader Files AnyMore due
  // to
  std::cout << ( "Setting up PipeLine" ) << "\n";

  const VkShaderModule vertShaderModule = ShaderSPIRVUtils::compileShaderFile( "shaders/21_shader_ubo.vert.spv" );
  const VkShaderModule fragShaderModule = ShaderSPIRVUtils::compileShaderFile( "shaders/21_shader_ubo.frag.spv" );
  // constexpr char entryPoint[]={"main"};

  const VkPipelineShaderStageCreateInfo vertexStage = {
    .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
    .stage  = VK_SHADER_STAGE_VERTEX_BIT,
    .module = vertShaderModule,
    .pName  = "main",

  };

  const VkPipelineShaderStageCreateInfo fragStage = { .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                                                      .stage  = VK_SHADER_STAGE_FRAGMENT_BIT,
                                                      .module = fragShaderModule,
                                                      .pName  = "main" };

  const VkPipelineShaderStageCreateInfo shaderStages[2] = { fragStage, vertexStage };

  static constexpr VkVertexInputBindingDescription VxL{ 0, ( 24 ), VK_VERTEX_INPUT_RATE_VERTEX };

  static constexpr VkVertexInputAttributeDescription attributeDescriptions[]{
    { .location = 0, .binding = 0, VK_FORMAT_R32G32B32_SFLOAT, OFFSET_POS },
    { .location = 1, .binding = 0, VK_FORMAT_R32G32B32_SFLOAT, OFFSETOF_COLOR },
    /* {0,
    2,
    VK_FORMAT_R32G32_SFLOAT,
    OFFSETOF_TEXTCOORDS} */

  };

  static constexpr VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo = {
    .sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .vertexBindingDescriptionCount   = 1,
    .pVertexBindingDescriptions      = &VxL,
    .vertexAttributeDescriptionCount = sizeof( attributeDescriptions ) / sizeof( VkVertexInputAttributeDescription ),
    .pVertexAttributeDescriptions    = attributeDescriptions
  };

  static constexpr VkPipelineInputAssemblyStateCreateInfo inputAssembly = {
    .sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
    .topology               = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
    .primitiveRestartEnable = VK_FALSE
  };

  static constexpr VkViewport vkViewport{
    .x = 0.0F, .y = 0.0F, .width = width, .height = height, .minDepth = UNormFlt, .maxDepth = 1.0F
  };

  static constexpr VkRect2D scissor{ //                    .offset(vkOffset2D ->vkViewport.y()) //todo: not
                                     //                    sure if correct Offset
                                     .offset = { 0, 0 },
                                     .extent{ width, height }
  };

  constexpr VkPipelineViewportStateCreateInfo vkViewPortState = {
    .sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
    .viewportCount = 1,
    .pViewports    = &vkViewport,
    //                    .pScissors(vkrect2DBuffer);
    .scissorCount = 1,
    .pScissors    = &scissor
    // vkViewPortState.pNext=VK_NULL_HANDLE;
  };

  constexpr VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization = {
    .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .depthClampEnable        = VK_FALSE,
    .rasterizerDiscardEnable = VK_FALSE,
    .polygonMode             = VK_POLYGON_MODE_FILL,
    .lineWidth               = 1.0f,
    .cullMode                = VK_CULL_MODE_BACK_BIT,  // WARNING: VERY IMPORTANT!:
                                                       // Make sure the culling direction is correct
                                                       // as it applies even to 2DVecs/Fixed
                                                       // Function Runtime/Evaluated Shaders
                                                       // with no transforms and withixed
                                                       // Const/Pre-Determined Runtime
                                                       // Variables
    .frontFace       = VK_FRONT_FACE_COUNTER_CLOCKWISE,
    .depthBiasEnable = VK_FALSE
    // VkPipeLineRasterization.pNext=VK_NULL_HANDLE;
  };

  constexpr VkPipelineMultisampleStateCreateInfo multisampling = {
    .sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
    .sampleShadingEnable   = VK_FALSE,
    .rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT,
    .minSampleShading      = 1.0F,
    .pSampleMask           = VK_NULL_HANDLE,
    .alphaToCoverageEnable = VK_FALSE,
    .alphaToOneEnable      = VK_FALSE
  };

  constexpr VkPipelineDepthStencilStateCreateInfo depthStencil = {
    .sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .depthTestEnable       = VK_FALSE,
    .depthWriteEnable      = VK_FALSE,
    .depthCompareOp        = VK_COMPARE_OP_LESS,
    .depthBoundsTestEnable = VK_FALSE,
    //                    .minDepthBounds(0) //Optional
    //                    .maxDepthBounds(1) //Optional
    .stencilTestEnable = VK_FALSE,
  };
  static constexpr VkPipelineColorBlendAttachmentState colorBlendAttachment = {
    .colorWriteMask =
      VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
    .blendEnable = VK_FALSE,

  };
  // float blendConstants[]={0.0f, 0.0f, 0.0f, 0.0f};
  constexpr VkPipelineColorBlendStateCreateInfo colorBlending = {
    .sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .logicOpEnable   = VK_FALSE,
    .logicOp         = VK_LOGIC_OP_COPY,
    .pAttachments    = &colorBlendAttachment,
    .attachmentCount = 1

  };

  static constexpr VkPushConstantRange vkPushConstantRange{
    .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
    .offset     = 0,
    .size       = sizeof( ubo ),
  };

  constexpr VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo = { .sType =
                                                                        VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                                      .setLayoutCount = 1,
                                                                      .pSetLayouts =
                                                                        &UniformBufferObject::descriptorSetLayout,
                                                                      .pushConstantRangeCount = 1,
                                                                      .pPushConstantRanges    = &vkPushConstantRange };

  std::cout << ( "using pipeLine with Length: " ) << sizeof( SwapChainSupportDetails::swapChainImageViews );
  clPPPI( &vkPipelineLayoutCreateInfo, "vkCreatePipelineLayout", &PipelineX::vkLayout );

  const VkGraphicsPipelineCreateInfo pipelineInfo = {
    .sType      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
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
    //                    .pDynamicState(null,
    .layout     = vkLayout,
    .renderPass = renderPass
    // pipelineInfo.subpass=0;
    //    pipelineInfo.basePipelineHandle=VK_NULL_HANDLE;
    // pipelineInfo.basePipelineIndex=-1;
  };

  checkCall( vkCreateGraphicsPipelines( device, nullptr, 1, &pipelineInfo, nullptr, &PipelineX::graphicsPipeline ) );

  vkDestroyShaderModule( device, vertShaderModule, VK_NULL_HANDLE );
  vkDestroyShaderModule( device, fragShaderModule, VK_NULL_HANDLE );
}

inline void PipelineX::createCommandBuffers()
{
  const VkCommandBufferAllocateInfo allocateInfo{ .sType       = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
                                                  .commandPool = (VkCommandPool)( Queues::commandPool ),
                                                  .level       = ( VK_COMMAND_BUFFER_LEVEL_PRIMARY ),
                                                  .commandBufferCount =
                                                    sizeof( PipelineX::commandBuffers ) / sizeof( VkCommandBuffer ) };
  std::cout << allocateInfo.commandBufferCount << "Command Buffers"
            << "\n";
  checkCall( vkAllocateCommandBuffers( device, &allocateInfo, PipelineX::commandBuffers ) );

  constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT ) };

  VkRenderPassAttachmentBeginInfo attachmentsbeginInfo{ .sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO,
                                                        .attachmentCount = 1,
                                                        .pAttachments =
                                                          &SwapChainSupportDetails::swapChainImageViews[0] };

  const VkRect2D renderArea = { .offset = { 0, 0 }, .extent = SwapChainSupportDetails::swapChainExtent };

  constexpr VkClearValue clearValues[2] = {
    [0].color = { { UNormFlt, UNormFlt, UNormFlt, 1.0f } }, [1].depthStencil = { 1.0f, 0 }
  };

  // VkClearValue clearColour = {{{0.0f, 0.0f, 0.0f, 1.0f}}};

  // VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};

  VkRenderPassBeginInfo renderPassInfo = {};
  renderPassInfo.sType                 = ( VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO );
  //   renderPassInfo.pNext =&attachmentsbeginInfo;
  renderPassInfo.pClearValues    = clearValues;
  renderPassInfo.clearValueCount = 2;
  renderPassInfo.renderPass      = ( renderPass );
  renderPassInfo.renderArea      = renderArea;
  uint8_t i                      = 0;
  vkMapMemory( device, UniformBufferObject::uniformBuffersMemory, 0, UniformBufferObject::Sized, 0, &data );
  for ( const VkCommandBuffer & commandBuffer : PipelineX::commandBuffers )
  {
    // extracted(beginInfo1, renderPassInfo, commandBuffer, i);

    checkCall( vkBeginCommandBuffer( commandBuffer, &beginInfo1 ) );

    renderPassInfo.framebuffer = ( SwapChainSupportDetails::swapChainFramebuffers[i] );

    vkCmdBeginRenderPass( commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

    vkCmdBindPipeline( commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, PipelineX::graphicsPipeline );
    constexpr VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers( commandBuffer, 0, 1, &vertexBuffer, offsets );
    vkCmdBindIndexBuffer( commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16 );

    vkCmdBindDescriptorSets( commandBuffer,
                             VK_PIPELINE_BIND_POINT_GRAPHICS,
                             PipelineX::vkLayout,
                             0,
                             1,
                             &UniformBufferObject::descriptorSets,
                             0,
                             nullptr );
    m4.loadAligned( &viewproj );  // NoS ure on best order............................................................->

    memcpy( ( data ), ( &viewproj ), UniformBufferObject::Sized );

    vkCmdDrawIndexed( commandBuffer, ( ( BuffersX::sizedsfIdx ) / 2 ), 1, 0, 0, 0 );

    vkCmdEndRenderPass( commandBuffer );
    checkCall( vkEndCommandBuffer( commandBuffer ) );
    i++;
  }
}
