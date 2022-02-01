#pragma once
// #include "SwapChainSupportDetails.hpp"
#include "Buffers.hpp"
#include "UniformBufferObject.hpp"
#include "src/Queues.hpp"
#include <array>


constexpr int OFFSETOF_COLOR = 2 * sizeof(float);
constexpr int OFFSET_POS = 0;

constexpr int OFFSETOF_TEXTCOORDS = (3 + 3) * sizeof(float);
constexpr float UNormFlt = 0.1F;
static constexpr struct PipelineX {
static inline VkPipelineLayout vkLayout;
static inline VkPipeline graphicsPipeline;

static inline VkCommandBuffer commandBuffers[Frames];
} inline pipeline; 
//     static void createRenderPasses();
//     static void createGraphicsPipelineLayout();
//     static void createCommandBuffers();

//     static    VkPipelineCache axx;

// VkVertexInputBindingDescription* getVertexInputBindingDescription();
// static VkVertexInputAttributeDescription*  getAttributeDescriptions();

//  inline  const VkVertexInputBindingDescription*
//  getVertexInputBindingDescription()
//     {
//          VkVertexInputBindingDescription a {
//                 .binding=0,
// //                    .stride(vertices.length/2)
// //                    .stride(vertices.length/VERT_SIZE+1)
//                 .stride=32,
//                 .inputRate=VK_VERTEX_INPUT_RATE_VERTEX
//         };
//         return &a;
//     }

//     inline constexpr VkVertexInputAttributeDescription*
//     getAttributeDescriptions()
//     {

//         VkVertexInputAttributeDescription attributeDescriptions[3];

//         // Position
//         VkVertexInputAttributeDescription* posDescription =
//         &attributeDescriptions[0]; posDescription->binding=0;
//         posDescription->location=0;
//         posDescription->format=VK_FORMAT_R32G32B32_SFLOAT;
//         posDescription->offset=OFFSET_POS;

//         // Color
//         VkVertexInputAttributeDescription* colorDescription =
//         &attributeDescriptions[1]; colorDescription->binding=0;
//         colorDescription->location=1;
//         colorDescription->format=VK_FORMAT_R32G32B32_SFLOAT;
//         colorDescription->offset=OFFSETOF_COLOR;

//         // Texture coordinates
//         VkVertexInputAttributeDescription* texCoordsDescription =
//         &attributeDescriptions[2]; texCoordsDescription->binding=0;
//         texCoordsDescription->location=2;
//         texCoordsDescription->format=VK_FORMAT_R32G32_SFLOAT;
//         texCoordsDescription->offset=OFFSETOF_TEXTCOORDS;

// //            memFree(attributeDescriptions);

//         return attributeDescriptions;
//     }
VkFormat findDepthFormat() {
  constexpr VkFormat formatCandidates[3] = {VK_FORMAT_D32_SFLOAT,
                                            VK_FORMAT_D32_SFLOAT_S8_UINT,
                                            VK_FORMAT_D24_UNORM_S8_UINT};
  VkFormatProperties props;

  for (const VkFormat &format : formatCandidates) {

    vkGetPhysicalDeviceFormatProperties(Queues.physicalDevice, format, &props);

    const int i2 = props.optimalTilingFeatures &
                   VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;
    if (i2 == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT/* && VK10.VK_IMAGE_TILING_OPTIMAL == VK_IMAGE_TILING_OPTIMAL*/) {
      return format;
    }
  }

  throw std::runtime_error("failed to find supported format!");
}

inline static void createRenderPasses() {
  static const VkAttachmentDescription colorAttachment{
      .format = swapChainImageFormat,
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
      .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
      .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
      .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
      .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
      .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
  };
  static constexpr VkAttachmentReference colorAttachmentRef{
      .attachment = 0, .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
  static constexpr VkSubpassDescription subpass{
      .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
      .colorAttachmentCount = 1,
      .pColorAttachments = &colorAttachmentRef};

  constexpr VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {
      .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
      .attachmentCount = 1,
      .pAttachments = &colorAttachment,
      .subpassCount = 1,
      .pSubpasses = &subpass,
      // .dependencyCount=1,
      // .pDependencies=&dependency
  };
  //        memPutLong(vkRenderPassCreateInfo1.address() +
  //        VkRenderPassCreateInfo.PDEPENDENCIES, dependency.address());
  //        memPutInt(vkRenderPassCreateInfo1.address() +
  //        VkRenderPassCreateInfo.DEPENDENCYCOUNT, 1);

  // MemSysm.Memsys2.doPointerAllocSafeX(vkRenderPassCreateInfo1,
  // Buffers.capabilities.vkCreateRenderPass,
  // SwapChainSupportDetails.renderPass);
  //        MemSysm.Memsys2.free(dependency);
  // MemSysm.Memsys2.free(vkRenderPassCreateInfo1);

  clPPPI(&vkRenderPassCreateInfo1, "vkCreateRenderPass",
         &SwapChainSupportDetails::renderPass);
}

inline static void createGraphicsPipelineLayout() {
  // Thankfully Dont; need to worry about compiling the Shader Files AnyMore due
  // to
  std::cout << ("Setting up PipeLine") << "\n";

  const VkShaderModule vertShaderModule =
      ShaderSPIRVUtils::compileShaderFile("shaders/21_shader_ubo.vert.spv");
  const VkShaderModule fragShaderModule =
      ShaderSPIRVUtils::compileShaderFile("shaders/21_shader_ubo.frag.spv");
  // constexpr char entryPoint[]={"main"};

  const VkPipelineShaderStageCreateInfo vertexStage = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_VERTEX_BIT,
      .module = vertShaderModule,
      .pName = "main",

  };

  const VkPipelineShaderStageCreateInfo fragStage = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
      .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
      .module = fragShaderModule,
      .pName = "main"};

  const VkPipelineShaderStageCreateInfo shaderStages[2] = {fragStage,
                                                           vertexStage};

  static constexpr VkVertexInputBindingDescription VxL {
                0,
                (sizedsf/4),
                VK_VERTEX_INPUT_RATE_VERTEX
        };

        
        static constexpr VkVertexInputAttributeDescription attributeDescriptions[]
        {
            { .location=0,
                .binding=0,
            VK_FORMAT_R32G32_SFLOAT,
            OFFSET_POS},
            {
            .location=1,
                .binding=0,
            VK_FORMAT_R32G32B32_SFLOAT,
            OFFSETOF_COLOR},
            /* {0,
            2,
            VK_FORMAT_R32G32_SFLOAT,
            OFFSETOF_TEXTCOORDS} */
            
        };

        // // Position
        // VkVertexInputAttributeDescription* posDescription =
        // &attributeDescriptions[0]; 

        // // Color
        // VkVertexInputAttributeDescription* colorDescription =
        // &attributeDescriptions[1]; colorDescription->binding=0;
        // colorDescription->location=1;
        // colorDescription->format=VK_FORMAT_R32G32B32_SFLOAT;
        // colorDescription->offset=OFFSETOF_COLOR;

        // // Texture coordinates
        // VkVertexInputAttributeDescription* texCoordsDescription =
        // &attributeDescriptions[2]; texCoordsDescription->binding=0;
        // texCoordsDescription->location=2;
        // texCoordsDescription->format=VK_FORMAT_R32G32_SFLOAT;
        // texCoordsDescription->offset=OFFSETOF_TEXTCOORDS;
        

  static constexpr VkPipelineVertexInputStateCreateInfo
      vkPipelineVertexInputStateCreateInfo = {
          .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
          .vertexBindingDescriptionCount = 1,
          .pVertexBindingDescriptions = &VxL,
          .vertexAttributeDescriptionCount = sizeof(attributeDescriptions)/sizeof(VkVertexInputAttributeDescription),
          .pVertexAttributeDescriptions = attributeDescriptions
          };

  static constexpr VkPipelineInputAssemblyStateCreateInfo inputAssembly = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
      .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
      .primitiveRestartEnable = VK_FALSE};
  // inputAssembly.pNext=VK_NULL_HANDLE;
  /*todo: Fixed Viewport COnstruction/Initilaistaion?Configration: ([Had use
   *wrong Function?method Veowpprt/Stagong function Calls/cfongurations e.g.])
   *(had also used vkViewport instead of VkViewport of Type Buffer which is the
   *atcual correct Obejct/Stage/Steup.veiwport conponnat.consituent
   *
   * (CorretcioN: had actually also used viewportBuffer and not vkViewport(Of
   *type VkViewport.Bufferand not VkViewPort....) in
   *VkPipelineViewportStateCreateInfo as well)
   */
  static constexpr VkViewport vkViewport{.x = 0.0F,
                                         .y = 0.0F,
                                         .width = width,
                                         .height = height,
                                         .minDepth = UNormFlt,
                                         .maxDepth = 1.0F};

   static constexpr VkRect2D scissor{
      //                    .offset(vkOffset2D ->vkViewport.y()) //todo: not
      //                    sure if correct Offset
      .offset = {0, 0},
      .extent{width, height}};

  constexpr VkPipelineViewportStateCreateInfo vkViewPortState = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
      .viewportCount = 1,
      .pViewports = &vkViewport,
      //                    .pScissors(vkrect2DBuffer);
      .scissorCount = 1,
      .pScissors = &scissor
      // vkViewPortState.pNext=VK_NULL_HANDLE;
  };

  constexpr VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
      .depthClampEnable = VK_FALSE,
      .rasterizerDiscardEnable = VK_FALSE,
      .polygonMode = VK_POLYGON_MODE_FILL,
      .lineWidth = 1.0f,
      .cullMode =
          VK_CULL_MODE_NONE, // WARNING: EXTREMEL:Y VERY VERY IMPORTANT!:
                                 // Make sur ethe culling direction is correct
                                 // as it applies even to 2DVecs/Fixed
                                 // Function.Const Runtime/Evaluated Shaders
                                 // with no transforms and withixed
                                 // FUnctin/COnst/PRe-Determined Runtime
                                 // Vraibles?Dlecarations/Initialistaions (as it
                                 // sems to Inteace with teh Driver Directly and
                                 // can Overide ve shader Dierctinves/Fixed
                                 // Functiosn pipelines/ShadersFrags/Verts
                                 // Directly!,
      .frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
      .depthBiasEnable = VK_FALSE
      // VkPipeLineRasterization.pNext=VK_NULL_HANDLE;
  };
  // todo: actuall need multismapling to
  // Compleet.Initialsie.Construct.Substanciate the renderPipeline corretcly
  // even if Antialsing /AF/MMs are not neeeded......
  constexpr VkPipelineMultisampleStateCreateInfo multisampling = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
      .sampleShadingEnable = VK_FALSE,
      .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
      .minSampleShading = 1.0F,
      .pSampleMask = VK_NULL_HANDLE,
      .alphaToCoverageEnable = VK_FALSE,
      .alphaToOneEnable = VK_FALSE};

          VkPipelineDepthStencilStateCreateInfo depthStencil={};
                     depthStencil.sType=VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
                  depthStencil.depthTestEnable=VK_TRUE;
                  depthStencil.depthWriteEnable=VK_TRUE;
                  depthStencil.depthCompareOp=VK_COMPARE_OP_LESS;
                  depthStencil.depthBoundsTestEnable=VK_FALSE;
  //                    .minDepthBounds(0) //Optional
  //                    .maxDepthBounds(1) //Optional
                  depthStencil.stencilTestEnable=VK_FALSE;

  static constexpr VkPipelineColorBlendAttachmentState colorBlendAttachment = {
      .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                        VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
      //(Actually)Add blending?transparency to be suproted
      .blendEnable = VK_FALSE,
      // colorBlendAttachment.srcColorBlendFactor=VK_BLEND_FACTOR_SRC_ALPHA;
      //   colorBlendAttachment
      //   .dstColorBlendFactor=(VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA);
      // colorBlendAttachment.dstColorBlendFactor=VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
      //   colorBlendAttachment .colorBlendOp=(VK_BLEND_OP_MAX);

      //   colorBlendAttachment .srcAlphaBlendFactor=(VK_BLEND_FACTOR_ONE);
      //   colorBlendAttachment .dstAlphaBlendFactor=(VK_BLEND_FACTOR_ZERO);
      //   colorBlendAttachment .alphaBlendOp=(VK_BLEND_OP_ADD);
  };
  // float blendConstants[]={0.0f, 0.0f, 0.0f, 0.0f};
  constexpr VkPipelineColorBlendStateCreateInfo colorBlending = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
      .logicOpEnable = VK_FALSE,
      .logicOp = VK_LOGIC_OP_COPY,
      .pAttachments = &colorBlendAttachment,
      .attachmentCount = 1
      // colorBlending.blendConstants[0]=0.0f;
      // colorBlending.blendConstants[1]=0.0f;
      // colorBlending.blendConstants[2]=0.0f;
      // colorBlending.blendConstants[3]=0.0f;
      //            memFree(colorBlendAttachment);
  };
  // VkPushConstantRange vkPushConstantRange={};
  //         vkPushConstantRange.offset=0;
  //         vkPushConstantRange.size=16 * sizeof(float);
  //         vkPushConstantRange.stageFlags=VK_SHADER_STAGE_VERTEX_BIT;

  constexpr VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo = {
      .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
      // vkPipelineLayoutCreateInfo.pPushConstantRanges=&vkPushConstantRange;
      .pSetLayouts=&descriptorSetLayout,
      // vkPipelineLayoutCreateInfo.flags=0;
      // vkPipelineLayoutCreateInfo.pushConstantRangeCount =1;
      .setLayoutCount=1,
      // vkPipelineLayoutCreateInfo.pNext=VK_NULL_HANDLE;
      //            vkPipelineLayoutCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  };

  std::cout << ("using pipeLine with Length: ")
            << sizeof(SwapChainSupportDetails::swapChainImageViews);
  // nmemFree(vkPipelineLayoutCreateInfo1.address());
  clPPPI(&vkPipelineLayoutCreateInfo, "vkCreatePipelineLayout", &PipelineX::vkLayout);
  // MemSysm.Memsys2.doPointerAllocSafeX(vkPipelineLayoutCreateInfo,
  // Buffers.capabilities.vkCreatePipelineLayout, Buffers.vkLayout);

  const VkGraphicsPipelineCreateInfo pipelineInfo = {
      .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
      .stageCount = 2,
      .pStages = shaderStages,
      // .pNext=VK_NULL_HANDLE,
      .pVertexInputState = &vkPipelineVertexInputStateCreateInfo,
      .pInputAssemblyState = &inputAssembly,
      .pViewportState = &vkViewPortState,
      .pRasterizationState = &VkPipeLineRasterization,
      .pMultisampleState = &multisampling,
    //   .pDepthStencilState=&depthStencil,
      .pColorBlendState = &colorBlending,
      //                    .pDynamicState(null,
      .layout = PipelineX::vkLayout,
      .renderPass = renderPass
      // pipelineInfo.subpass=0;
      //    pipelineInfo.basePipelineHandle=VK_NULL_HANDLE;
      // pipelineInfo.basePipelineIndex=-1;
  };

  // Memsys2.free(entryPoint);
  // todo: WARN: Potnetial Major Breakage
  constexpr uint32_t a = 1;
  // // vulkan_layer_chassis::CreateGraphicsPipelines

  checkCall(vkCreateGraphicsPipelines(device, nullptr, a, &pipelineInfo,
                                      nullptr, &PipelineX::graphicsPipeline));
  // clPPPI(&pipelineInfo, "vkCreateGraphicsPipelines", &graphicsPipeline);
  //        if (graphicsPipeline == nullptr)
  //         {
  //                 std::cout << graphicsPipeline << "\n" <<
  //                 &graphicsPipeline<< "\n"; throw std::runtime_error("bad
  //                 Alloctaion!: Handle is NUll!/Null handle!");
  //         }
  // Buffers.graphicsPipeline = MemSysm.doPointerAlloc5L(device, pipelineInfo);

  vkDestroyShaderModule(device, vertShaderModule, VK_NULL_HANDLE);
  vkDestroyShaderModule(device, fragShaderModule, VK_NULL_HANDLE);
}

inline static void createCommandBuffers() {
  const VkCommandBufferAllocateInfo allocateInfo = {
      .sType = (VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO),
      .commandPool = (VkCommandPool)(Queues.commandPool),
      .level = (VK_COMMAND_BUFFER_LEVEL_PRIMARY),
      .commandBufferCount = sizeof(PipelineX::commandBuffers)/sizeof(VkCommandBuffer)};
  std::cout << allocateInfo.commandBufferCount << "Command Buffers"
            << "\n";
  // = memPointerBuffer(allocateInfo.address(),
  // allocateInfo.commandBufferCount());
  //            MemSysm.Memsys2.free(allocateInfo);
  vkAllocateCommandBuffers(device, &allocateInfo, PipelineX::commandBuffers);
  // doPointerAllocS(allocateInfo, capabilities.vkAllocateCommandBuffers,
  // descriptorSets); commandBuffers.put(descriptorSets); descriptorSets.free();

  constexpr VkCommandBufferBeginInfo beginInfo1 = {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .flags = (VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT)};

  //            VkRenderPassAttachmentBeginInfo vkRenderPassAttachmentBeginInfo1
  //            =
  //            VkRenderPassAttachmentBeginInfo.create(MemSysm.malloc(VkRenderPassAttachmentBeginInfo
  //            .SIZEOF))
  //                    .sType$Default();
  //.pAttachments(VkUtils2.MemSys.stack.longs(VkUtils2.SwapChainSupportDetails.swapChainImageViews));
  const VkRect2D renderArea = {
      .offset = {0, 0}, .extent = SwapChainSupportDetails::swapChainExtent};

  constexpr VkClearValue clearValues[2] = {
      [0].color = {{UNormFlt, UNormFlt, UNormFlt, 1.0f}}, [1].depthStencil = {1.0f, 0}};

  // VkClearValue clearColour = {{{0.0f, 0.0f, 0.0f, 1.0f}}};

  // VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};

  VkRenderPassBeginInfo renderPassInfo = {};
  renderPassInfo.sType = (VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO);
  renderPassInfo.pClearValues = clearValues;
  renderPassInfo.clearValueCount = 2;
  renderPassInfo.renderPass = (renderPass);
  renderPassInfo.renderArea = renderArea;
  uint8_t i = 0;

  
  for (const VkCommandBuffer &commandBuffer : PipelineX::commandBuffers) {
    // extracted(beginInfo1, renderPassInfo, commandBuffer, i);

    checkCall(vkBeginCommandBuffer(commandBuffer, &beginInfo1));

    renderPassInfo.framebuffer =
        (SwapChainSupportDetails::swapChainFramebuffers[i]);

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo,
                         VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                      PipelineX::graphicsPipeline);
    constexpr VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, &vertexBuffer, offsets);
    vkCmdBindIndexBuffer(commandBuffer, indexBuffer, 0, VK_INDEX_TYPE_UINT16);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,PipelineX::vkLayout, 0, 1, &descriptorSets[i], 0, nullptr);

    vkCmdDrawIndexed(commandBuffer, ((BuffersX::sizedsfIdx)/2), 1, 0, 0, 0);

    vkCmdEndRenderPass(commandBuffer);
    checkCall(vkEndCommandBuffer(commandBuffer));
    i++;
  }
}

// namespace PipelineX