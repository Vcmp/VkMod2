#include "Queues.hpp"
#include "Buffers.hpp"
#include <cstddef>
#include "Pipeline.hpp"


//this Code ios extremely Ugly ATm just t get an intial Primtive./Rundimenray.baisc/Makshift/Crude/Limited/ Inhibited/Impelmhetd SetuP Runnign


void textTemp::doBuffers()
{
    auto x1 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT );
  auto p1 = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  BuffersX::createSetBuffer( p1, VertexTemp, x1, (sizeof(Vktemp)), VertexTempMem );

  VkBufferUsageFlagBits x2 = { VK_BUFFER_USAGE_TRANSFER_SRC_BIT };
  constexpr auto        p  = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
   BuffersX::createSetBuffer( p, BuffersX::Bufferstaging, x2, (sizeof(Vktemp)), BuffersX::stagingBufferMemory );

  textTemp::vkMappedCopy(BuffersX::stagingBufferMemory, (sizeof(Vktemp)), Vktemp, BuffersX::data, VertexTemp);

}


void textTemp::vkMappedCopy(VkDeviceMemory &Staging, size_t size, const float* srcVectBuffs, __m256 *data, VkBuffer& Temp)
{
  void* autoMemAllocs;
  vkMapMemory( Queues::device, Staging, 0, size, 0, (void**)&data );
  {
    memcpy(data, srcVectBuffs, size );
  }
  vkUnmapMemory( Queues::device, Staging );
    BuffersX::copyBuffer(Temp, size);
}

//Might getaway without need for Addiitonal/Self-Conatined /Dedicated renderpass...
void textTemp::initPipelineCustom()
{
    static constexpr VkViewport vkViewport{ .x = 0.0F, .y = 0.0F, .width = width, .height = height, .minDepth = 0.0F, .maxDepth = 1.0F };

  static constexpr VkRect2D scissor{ .offset = { 0, 0 }, .extent{ width, height } };

  constexpr VkPipelineViewportStateCreateInfo vkViewPortState = {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, .viewportCount = 1, .pViewports = &vkViewport, .scissorCount = 1, .pScissors = &scissor
  };



   const VkPipelineShaderStageCreateInfo vertexStage2 = {
          .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
          .stage  = VK_SHADER_STAGE_VERTEX_BIT,
          .module = Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &SPV.VsMCI3temp, "vkCreateShaderModule" ),
          .pName  = "main",

        }; 
        
        const VkPipelineShaderStageCreateInfo fragStage2 = {
          .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
          .stage  = VK_SHADER_STAGE_FRAGMENT_BIT,
          .module = Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &SPV.VsMCI4temp, "vkCreateShaderModule" ),
          .pName  = "main",

        }; 

        vkShaderStages[0]={vertexStage2},
        vkShaderStages[1]={fragStage2};

static constexpr VkPipelineColorBlendAttachmentState colorBlendAttachment = {
    .blendEnable    = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,

  };

constexpr VkPipelineColorBlendStateCreateInfo colourBlendState
{
    .sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .logicOpEnable   = VK_FALSE,
    .logicOp         = VK_LOGIC_OP_COPY,
    .attachmentCount = 1,
    .pAttachments    = &colorBlendAttachment,
};

   static constexpr VkVertexInputAttributeDescription attributeDescriptions[1]{

    { .location = 3, .binding = 0, .format = VK_FORMAT_R32G32_SFLOAT, .offset = 0 },
    // { .location = 4, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = sizeof(float) * 2}
  };


 constexpr VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization = {
    .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .depthClampEnable        = VK_FALSE,
    .rasterizerDiscardEnable = VK_FALSE,
    .polygonMode             = VK_POLYGON_MODE_FILL,
    .cullMode                = VK_CULL_MODE_NONE,  // WARNING: VERY IMPORTANT!:
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


  static constexpr VkVertexInputBindingDescription VxL2{ 0, ( 8 ), VK_VERTEX_INPUT_RATE_VERTEX };

  
  static constexpr VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo = {
    .sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .vertexBindingDescriptionCount   = 1,
    .pVertexBindingDescriptions      = &VxL2,
    .vertexAttributeDescriptionCount = sizeof( attributeDescriptions ) / sizeof( VkVertexInputAttributeDescription ),
    .pVertexAttributeDescriptions    = attributeDescriptions
  };

  static constexpr VkPipelineInputAssemblyStateCreateInfo inputAssembly = { .sType    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
                                                                            .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
                                                                            .primitiveRestartEnable = VK_FALSE };
  constexpr VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo = { .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                                      // .setLayoutCount         = 1,
                                                                      // .pSetLayouts            = &UniformBufferObject::descriptorSetLayout,
                                                                      .pushConstantRangeCount = 0,
                                                                       };

  // std::cout << ( "using pipeLine with Length: " ) << sizeof( SwapChainSupportDetails::swapChainImageViews );
  VkPipelineLayout vkLayout;
  VkUtilsXBase::clPPPI3<PFN_vkCreatePipelineLayout>( &vkPipelineLayoutCreateInfo, "vkCreatePipelineLayout", &vkLayout );

      VkGraphicsPipelineCreateInfo xx
     { 
          .sType      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
          .stageCount=1,
          .pStages = vkShaderStages,
          .pVertexInputState=&vkPipelineVertexInputStateCreateInfo,
          .pInputAssemblyState=&inputAssembly,
          .pViewportState = &vkViewPortState,
          .pRasterizationState=&VkPipeLineRasterization,
          .pMultisampleState=&multisampling,
          .pDepthStencilState=nullptr,
          .pColorBlendState=&colourBlendState,
          .layout=vkLayout,
          .renderPass = SwapChainSupportDetails::renderPass,
          .basePipelineHandle=x,
          .basePipelineIndex=0,
      };

      vkCreateGraphicsPipelines(Queues::device, nullptr, 1, &xx, nullptr, &x);
}

void textTemp::voidrecComBufferSub(int i)
{

  vkResetCommandPool(Queues::device, p, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);

  constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) };

  constexpr VkRect2D renderArea = { .offset = { 0, 0 }, .extent = SwapChainSupportDetails::swapChainExtent };

  constexpr VkClearValue clearValues2 = { .color = { 110.0, 0.0, 0.0, 1.0F } };


  static VkRenderPassBeginInfo renderPassInfo = {
    .sType           = ( VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),
    .renderPass      = ( SwapChainSupportDetails::renderPass ),
    .renderArea      = renderArea,
    .clearValueCount = 1,
    .pClearValues    = &clearValues2,
  };
    static constexpr VkDeviceSize offsets[] = { 0 };

    vkBeginCommandBuffer(comBuffer, &beginInfo1);
    renderPassInfo.framebuffer = ( SwapChainSupportDetails::swapChainFramebuffers[i] );

    vkCmdBeginRenderPass(comBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

    vkCmdBindPipeline(comBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,x );
    vkCmdBindVertexBuffers(comBuffer, 0, 1, &VertexTemp, offsets );
     


    vkCmdDraw(comBuffer, sizeof(Vktemp) / sizeof(float), 1, 0, 0);

    vkCmdEndRenderPass( comBuffer );
    VkUtilsXBase::clP<PFN_vkEndCommandBuffer>( comBuffer, "vkEndCommandBuffer" );




    
}
