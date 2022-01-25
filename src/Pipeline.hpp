#pragma once
#include "SwapChainSupportDetails.hpp"
#include <array>


 constexpr int OFFSETOF_COLOR = 3 * sizeof(float);
 constexpr int OFFSET_POS = 0;

 constexpr int OFFSETOF_TEXTCOORDS = (3 + 3) * sizeof(float);

inline namespace PipelineX
{   static VkPipelineLayout vkLayout;
    static VkPipeline graphicsPipeline;

    
    static std::array<VkCommandBuffer, Frames> commandBuffers;

//     static void createRenderPasses();
//     static void createGraphicsPipelineLayout();
//     static void createCommandBuffers();

//     static    VkPipelineCache axx;
   
    // VkVertexInputBindingDescription* getVertexInputBindingDescription();
    //static VkVertexInputAttributeDescription*  getAttributeDescriptions();





//  inline  VkVertexInputBindingDescription* Pipeline::getVertexInputBindingDescription()
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

//     inline VkVertexInputAttributeDescription*  Pipeline::getAttributeDescriptions()
//     {

//         VkVertexInputAttributeDescription attributeDescriptions[3];

//         // Position
//         VkVertexInputAttributeDescription* posDescription = &attributeDescriptions[0];
//         posDescription->binding=0;
//         posDescription->location=0;
//         posDescription->format=VK_FORMAT_R32G32B32_SFLOAT;
//         posDescription->offset=OFFSET_POS;

//         // Color
//         VkVertexInputAttributeDescription* colorDescription = &attributeDescriptions[1];
//         colorDescription->binding=0;
//         colorDescription->location=1;
//         colorDescription->format=VK_FORMAT_R32G32B32_SFLOAT;
//         colorDescription->offset=OFFSETOF_COLOR;

//         // Texture coordinates
//         VkVertexInputAttributeDescription* texCoordsDescription = &attributeDescriptions[2];
//         texCoordsDescription->binding=0;
//         texCoordsDescription->location=2;
//         texCoordsDescription->format=VK_FORMAT_R32G32_SFLOAT;
//         texCoordsDescription->offset=OFFSETOF_TEXTCOORDS;

// //            memFree(attributeDescriptions);

//         return attributeDescriptions;
//     } 
VkFormat findDepthFormat()
    {
        VkFormat formatCandidates[3]={VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT};
        VkFormatProperties props;

        for (VkFormat format : formatCandidates) {

           
            vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

            const int i2 = props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;
            if (i2 == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT/* && VK10.VK_IMAGE_TILING_OPTIMAL == VK_IMAGE_TILING_OPTIMAL*/) {
                return format;
            }
        }

       throw std::runtime_error("failed to find supported format!");
    }

inline void createRenderPasses()
    {
       VkAttachmentDescription colorAttachment{};
        colorAttachment.format = swapChainImageFormat;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

     


        VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {
                .sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
                .attachmentCount=1,
                .pAttachments=&colorAttachment,
                .subpassCount=1,
                .pSubpasses=&subpass,
                // .dependencyCount=1,
                // .pDependencies=&dependency
        };
//        memPutLong(vkRenderPassCreateInfo1.address() + VkRenderPassCreateInfo.PDEPENDENCIES, dependency.address());
//        memPutInt(vkRenderPassCreateInfo1.address() + VkRenderPassCreateInfo.DEPENDENCYCOUNT, 1);


        // MemSysm.Memsys2.doPointerAllocSafeX(vkRenderPassCreateInfo1, Buffers.capabilities.vkCreateRenderPass, SwapChainSupportDetails.renderPass);
//        MemSysm.Memsys2.free(dependency);
        // MemSysm.Memsys2.free(vkRenderPassCreateInfo1);
               


        clPPPI(&vkRenderPassCreateInfo1, "vkCreateRenderPass", &SwapChainSupportDetails::renderPass);
        
       

    }

    inline void createGraphicsPipelineLayout()
    {
        //Thankfully Dont; need to worry about compiling the Shader Files AnyMore due to
        std::cout<<("Setting up PipeLine")<< "\n";

          
         
        const VkShaderModule vertShaderModule = ShaderSPIRVUtils::compileShaderFile("shaders/21_shader_ubo.vert.spv");
        const VkShaderModule fragShaderModule = ShaderSPIRVUtils::compileShaderFile("shaders/21_shader_ubo.frag.spv");
        // constexpr char entryPoint[]={"main"};

        const VkPipelineShaderStageCreateInfo vertexStage={
            .sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                .stage=VK_SHADER_STAGE_VERTEX_BIT,
                .module=vertShaderModule,
                .pName="main",
               
                };
       

        const VkPipelineShaderStageCreateInfo fragStage={
                .sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                .stage=VK_SHADER_STAGE_FRAGMENT_BIT,
                .module=fragShaderModule,
                .pName="main"
    };
        

       VkPipelineShaderStageCreateInfo shaderStages[2] = {fragStage, vertexStage};

        
        VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo={};
                   vkPipelineVertexInputStateCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
                vkPipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount=0;
                vkPipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount =0;


        VkPipelineInputAssemblyStateCreateInfo inputAssembly={};
                   inputAssembly.sType=VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
                inputAssembly.topology=VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
                inputAssembly.primitiveRestartEnable=VK_FALSE;
                // inputAssembly.pNext=VK_NULL_HANDLE;
        /*todo: Fixed Viewport COnstruction/Initilaistaion?Configration: ([Had use wrong Function?method Veowpprt/Stagong function Calls/cfongurations e.g.])
         *(had also used vkViewport instead of VkViewport of Type Buffer which is the atcual correct Obejct/Stage/Steup.veiwport conponnat.consituent
         *
         * (CorretcioN: had actually also used viewportBuffer and not vkViewport(Of type VkViewport.Bufferand not VkViewPort....) in VkPipelineViewportStateCreateInfo as well)
         */
        VkViewport vkViewport{};
                vkViewport.x=0.0F;
                vkViewport.y=0.0F;
                vkViewport.width=(float)swapChainExtent.width;
                vkViewport.height=(float)swapChainExtent.height;
                vkViewport.minDepth=0.0F;
                vkViewport.maxDepth=1.0F;
        

        VkRect2D scissor{};
//                    .offset(vkOffset2D ->vkViewport.y()) //todo: not sure if correct Offset
                scissor.offset={0,0};
                scissor.extent=SwapChainSupportDetails::swapChainExtent;
      

        VkPipelineViewportStateCreateInfo vkViewPortState={};
                   vkViewPortState.sType=VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
                vkViewPortState.viewportCount=1;
                vkViewPortState.pViewports=&vkViewport;
//                    .pScissors(vkrect2DBuffer);
                vkViewPortState.scissorCount=1;
                vkViewPortState.pScissors=&scissor;
                // vkViewPortState.pNext=VK_NULL_HANDLE;


        VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization={};
                   VkPipeLineRasterization.sType=VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
                VkPipeLineRasterization.depthClampEnable=VK_FALSE;
                VkPipeLineRasterization.rasterizerDiscardEnable=VK_FALSE;
                VkPipeLineRasterization.polygonMode=VK_POLYGON_MODE_FILL;
                VkPipeLineRasterization.lineWidth=1.0f;
                  VkPipeLineRasterization.cullMode=VK_CULL_MODE_BACK_BIT;
                  VkPipeLineRasterization.frontFace=VK_FRONT_FACE_CLOCKWISE;
                VkPipeLineRasterization.depthBiasEnable=VK_FALSE;
                // VkPipeLineRasterization.pNext=VK_NULL_HANDLE;

        //todo: actuall need multismapling to Compleet.Initialsie.Construct.Substanciate the renderPipeline corretcly even if Antialsing /AF/MMs are not neeeded......
        VkPipelineMultisampleStateCreateInfo multisampling={};
                   multisampling.sType=VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
                multisampling.sampleShadingEnable=VK_FALSE;
                multisampling.rasterizationSamples=VK_SAMPLE_COUNT_1_BIT;
                multisampling.minSampleShading =1.0F;
                multisampling.pSampleMask = VK_NULL_HANDLE;
		multisampling.alphaToCoverageEnable = VK_FALSE;
		multisampling.alphaToOneEnable = VK_FALSE;


//         VkPipelineDepthStencilStateCreateInfo depthStencil={};
//                    depthStencil.sType=VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
//                 depthStencil.depthTestEnable=VK_TRUE;
//                 depthStencil.depthWriteEnable=VK_TRUE;
//                 depthStencil.depthCompareOp=VK_COMPARE_OP_LESS;
//                 depthStencil.depthBoundsTestEnable=VK_FALSE;
// //                    .minDepthBounds(0) //Optional
// //                    .maxDepthBounds(1) //Optional
//                 depthStencil.stencilTestEnable=VK_FALSE;


        VkPipelineColorBlendAttachmentState colorBlendAttachment={};
                colorBlendAttachment.colorWriteMask=VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
                //(Actually)Add blending?transparency to be suproted
                colorBlendAttachment.blendEnable=VK_FALSE;
                // colorBlendAttachment.srcColorBlendFactor=VK_BLEND_FACTOR_SRC_ALPHA;
                //   colorBlendAttachment .dstColorBlendFactor=(VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA);
                // colorBlendAttachment.dstColorBlendFactor=VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
                //   colorBlendAttachment .colorBlendOp=(VK_BLEND_OP_MAX);

                //   colorBlendAttachment .srcAlphaBlendFactor=(VK_BLEND_FACTOR_ONE);
                //   colorBlendAttachment .dstAlphaBlendFactor=(VK_BLEND_FACTOR_ZERO);
                //   colorBlendAttachment .alphaBlendOp=(VK_BLEND_OP_ADD);

        // float blendConstants[]={0.0f, 0.0f, 0.0f, 0.0f};
        VkPipelineColorBlendStateCreateInfo colorBlending={};
                   colorBlending.sType=VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
                colorBlending.logicOpEnable=VK_FALSE;
                colorBlending.logicOp=VK_LOGIC_OP_COPY;
                colorBlending.pAttachments=&colorBlendAttachment;
                colorBlending.attachmentCount=1;
                // colorBlending.blendConstants[0]=0.0f;
                // colorBlending.blendConstants[1]=0.0f;
                // colorBlending.blendConstants[2]=0.0f;
                // colorBlending.blendConstants[3]=0.0f;
//            memFree(colorBlendAttachment);

        // VkPushConstantRange vkPushConstantRange={};
        //         vkPushConstantRange.offset=0;
        //         vkPushConstantRange.size=16 * sizeof(float);
        //         vkPushConstantRange.stageFlags=VK_SHADER_STAGE_VERTEX_BIT;


        VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo={};
                   vkPipelineLayoutCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                // vkPipelineLayoutCreateInfo.pPushConstantRanges=&vkPushConstantRange;
                // vkPipelineLayoutCreateInfo.pSetLayouts=0;//&UniformBufferObject::descriptorSetLayout;
                // vkPipelineLayoutCreateInfo.flags=0;
                // vkPipelineLayoutCreateInfo.pushConstantRangeCount =1;
                // vkPipelineLayoutCreateInfo.setLayoutCount=0;
                // vkPipelineLayoutCreateInfo.pNext=VK_NULL_HANDLE;
                //            vkPipelineLayoutCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
       


        std::cout << ("using pipeLine with Length: ") << sizeof(SwapChainSupportDetails::swapChainImageViews);
        //nmemFree(vkPipelineLayoutCreateInfo1.address());
        clPPPI(&vkPipelineLayoutCreateInfo, "vkCreatePipelineLayout", &vkLayout);
        //MemSysm.Memsys2.doPointerAllocSafeX(vkPipelineLayoutCreateInfo, Buffers.capabilities.vkCreatePipelineLayout, Buffers.vkLayout);


        VkGraphicsPipelineCreateInfo pipelineInfo={};
                pipelineInfo.sType=VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
                pipelineInfo.stageCount=2;
                pipelineInfo.pStages=shaderStages;
                // pipelineInfo.pNext=VK_NULL_HANDLE;
                pipelineInfo.pVertexInputState=&vkPipelineVertexInputStateCreateInfo;
                pipelineInfo.pInputAssemblyState=&inputAssembly;
                pipelineInfo.pViewportState=&vkViewPortState;
                pipelineInfo.pRasterizationState=&VkPipeLineRasterization;
                pipelineInfo.pMultisampleState=&multisampling;
                // pipelineInfo.pDepthStencilState=&depthStencil;
                pipelineInfo.pColorBlendState=&colorBlending;
//              pipelineInfo      .pDynamicState(null)
                pipelineInfo.layout=vkLayout;
                pipelineInfo.renderPass=renderPass;
                pipelineInfo.subpass=0;
                //    pipelineInfo.basePipelineHandle=VK_NULL_HANDLE;
                // pipelineInfo.basePipelineIndex=-1;
        
       

        //Memsys2.free(entryPoint);
        //todo: WARN: Potnetial Major Breakage
        uint32_t a=1;
        // // vulkan_layer_chassis::CreateGraphicsPipelines
      
                checkCall(vkCreateGraphicsPipelines(device, nullptr, a, &pipelineInfo, nullptr, &graphicsPipeline));
        // clPPPI(&pipelineInfo, "vkCreateGraphicsPipelines", &graphicsPipeline);
//        if (graphicsPipeline == nullptr)
//         {
//                 std::cout << graphicsPipeline << "\n" <<  &graphicsPipeline<< "\n";
//                 throw std::runtime_error("bad Alloctaion!: Handle is NUll!/Null handle!");
//         }
        // Buffers.graphicsPipeline = MemSysm.doPointerAlloc5L(device, pipelineInfo);

        vkDestroyShaderModule(device, vertShaderModule, VK_NULL_HANDLE );
        vkDestroyShaderModule(device, fragShaderModule, VK_NULL_HANDLE );

    }

    inline void createCommandBuffers()
{
    VkCommandBufferAllocateInfo allocateInfo = {};
                allocateInfo.sType=(VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO);
                allocateInfo.commandPool=(commandPool);
                allocateInfo.level=(VK_COMMAND_BUFFER_LEVEL_PRIMARY);
                allocateInfo.commandBufferCount=(commandBuffers.size());
        std::cout<< allocateInfo.commandBufferCount << "Command Buffers"<<"\n";
        // = memPointerBuffer(allocateInfo.address(), allocateInfo.commandBufferCount());
//            MemSysm.Memsys2.free(allocateInfo);
        vkAllocateCommandBuffers(device, &allocateInfo, commandBuffers.data());
        // doPointerAllocS(allocateInfo, capabilities.vkAllocateCommandBuffers, descriptorSets);
        // commandBuffers.put(descriptorSets);
        // descriptorSets.free();

        VkCommandBufferBeginInfo beginInfo1 = {};
                  beginInfo1.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                beginInfo1.flags=(VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);

//            VkRenderPassAttachmentBeginInfo vkRenderPassAttachmentBeginInfo1 = VkRenderPassAttachmentBeginInfo.create(MemSysm.malloc(VkRenderPassAttachmentBeginInfo .SIZEOF))
//                    .sType$Default();
        //.pAttachments(VkUtils2.MemSys.stack.longs(VkUtils2.SwapChainSupportDetails.swapChainImageViews));
         VkRect2D renderArea = {};
                renderArea.offset={0,0};//(set);
                renderArea.extent=SwapChainSupportDetails::swapChainExtent;

       VkClearValue clearValues[2]= {};
        clearValues[0].color={{0.0f, 0.0f, 0.0f, 1.0f}};
        clearValues[1].depthStencil={1.0f, 0};


        // VkClearValue clearColour = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
            

                // VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
             

        VkRenderPassBeginInfo renderPassInfo = {};
              renderPassInfo.sType=(VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO);
              renderPassInfo.pClearValues=clearValues;
              renderPassInfo.clearValueCount=2;
              renderPassInfo.renderPass=(renderPass);
              renderPassInfo.renderArea=renderArea;
                int i=0;
               for (const VkCommandBuffer &commandBuffer : commandBuffers) 
               {
                    //extracted(beginInfo1, renderPassInfo, commandBuffer, i);

                        checkCall(vkBeginCommandBuffer(commandBuffer, &beginInfo1));
        
                        renderPassInfo.framebuffer=(SwapChainSupportDetails::swapChainFramebuffers[i]);

                        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
                        
                        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
                        vkCmdDraw(commandBuffer, 3, 1, 0, 0);
                        
                        vkCmdEndRenderPass(commandBuffer);
                        checkCall(vkEndCommandBuffer(commandBuffer));
                       i++;

                }
}

};