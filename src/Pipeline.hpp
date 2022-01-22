#pragma once
#include "VkUtilsXBase.hpp"
#include "SwapChainSupportDetails.hpp"

 constexpr int OFFSETOF_COLOR = 3 * sizeof(float);
 constexpr int OFFSET_POS = 0;

 constexpr int OFFSETOF_TEXTCOORDS = (3 + 3) * sizeof(float);

inline namespace PipelineX
{   static VkPipelineLayout vkLayout;
    static VkPipeline graphicsPipeline={};

    static VkImageLayout depthImageView;
    static VkCommandBuffer commandBuffers[3];

    static void createRenderPasses();
    static void createGraphicsPipelineLayout();
    static void createCommandBuffers();

//     static    VkPipelineCache axx;
   
    // VkVertexInputBindingDescription* getVertexInputBindingDescription();
    //static VkVertexInputAttributeDescription*  getAttributeDescriptions();
};




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


inline void PipelineX::createRenderPasses()
    {
        //  int capacity = 2;
        // int abs;

        // VkAttachmentReference VkRenderPasses[capacity];
        // VkRenderPassCreateInfo VkRenderPassesAttach[capacity];
//            if (!depthEnabled)
//            {
//                abs=VK_SUBPASS_EXTERNAL;
//            }
        //else
        // abs = VK_SUBPASS_EXTERNAL;
VkAttachmentReference attachmentsRefs = {};
                attachmentsRefs.attachment=0,
                attachmentsRefs.layout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

       VkAttachmentDescription attachments = {};
                 attachments.format=SwapChainSupportDetails::swapChainImageFormat;
                 attachments.samples=VK_SAMPLE_COUNT_1_BIT;
                 attachments.loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR;
                 attachments.storeOp=VK_ATTACHMENT_STORE_OP_STORE;
                 attachments.stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
                 attachments.stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
                 attachments.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
                 attachments.finalLayout=VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
     


    //     VkAttachmentDescription depthAttachment ={};
    //             attachments.format=Texture::findDepthFormat();
    //             attachments.samples=VK_SAMPLE_COUNT_1_BIT;
    //             attachments.loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR;
    //             attachments.storeOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
    //             attachments.stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    //             attachments.stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE;
    //             attachments.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
    //             attachments.finalLayout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;


        // VkAttachmentReference depthAttachmentRef ={};
        //         attachmentsRefs.attachment=1;
        //         attachmentsRefs.layout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;   
        
        VkSubpassDescription vkSubpassDescriptions={};
                vkSubpassDescriptions.pipelineBindPoint=VK_PIPELINE_BIND_POINT_GRAPHICS;
                vkSubpassDescriptions.colorAttachmentCount=1;
                vkSubpassDescriptions.pColorAttachments=&attachmentsRefs;
                // vkSubpassDescriptions.pDepthStencilAttachment=&depthAttachmentRef;

// const VkAttachmentDescription attDesc[]={attachments, depthAttachment};

        // VkSubpassDependency dependency = {};
        //         dependency.srcSubpass=abs;
        //         dependency.dstSubpass=0;
        //         dependency.srcStageMask=VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
        //         dependency.srcAccessMask=VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
        //         // dependency.dstStageMask=VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
        //         // dependency.dstAccessMask=VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
        //         dependency.dependencyFlags=VK_DEPENDENCY_BY_REGION_BIT;


        VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {};
                vkRenderPassCreateInfo1.sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
                vkRenderPassCreateInfo1.attachmentCount=1;
                vkRenderPassCreateInfo1.pAttachments=&attachments;
                vkRenderPassCreateInfo1.subpassCount=1;
                vkRenderPassCreateInfo1.pSubpasses=&vkSubpassDescriptions;
                // vkRenderPassCreateInfo1.pDependencies=&dependency;
                // vkRenderPassCreateInfo1.dependencyCount=2;
               


        clPPPI(&vkRenderPassCreateInfo1, "vkCreateRenderPass", &SwapChainSupportDetails::renderPass);
        
       

    }

    inline void PipelineX::createGraphicsPipelineLayout()
    {
        //Thankfully Dont; need to worry about compiling the Shader Files AnyMore due to
        std::cout<<("Setting up PipeLine")<< "\n";

          
         
        const VkShaderModule vertShaderModule = ShaderSPIRVUtils::compileShaderFile("shaders/21_shader_ubo.vert.spv");
        const VkShaderModule fragShaderModule = ShaderSPIRVUtils::compileShaderFile("shaders/21_shader_ubo.frag.spv");
        // constexpr char entryPoint[]={"main"};

        VkPipelineShaderStageCreateInfo vertexStage={};
            vertexStage.sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
//                    .sType(VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO)
                vertexStage.stage=VK_SHADER_STAGE_VERTEX_BIT;
                vertexStage.module=vertShaderModule;
                vertexStage.pName="main";
                vertexStage.pNext=VK_NULL_HANDLE;
                
       

        VkPipelineShaderStageCreateInfo fragStage={};
                fragStage.sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                fragStage.stage=VK_SHADER_STAGE_FRAGMENT_BIT;
                fragStage.module=fragShaderModule;
                fragStage.pName="main";
                fragStage.pNext=VK_NULL_HANDLE;
        

       const VkPipelineShaderStageCreateInfo shaderStages[] = {fragStage, vertexStage};

        VkVertexInputBindingDescription ax ={
                        .binding=0,
        //                    .stride(vertices.length/2)
        //                    .stride(vertices.length/VERT_SIZE+1)
                        .stride=32,
                        .inputRate=VK_VERTEX_INPUT_RATE_VERTEX
                };

        VkVertexInputAttributeDescription attributeDescriptions[3];

        // Position
                attributeDescriptions[0]={};
                attributeDescriptions[0].binding=0;
                attributeDescriptions[0].location=0;
                attributeDescriptions[0].format=VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[0].offset=OFFSET_POS;

                // Color
                attributeDescriptions[1]={};
                attributeDescriptions[1].binding=0;
                attributeDescriptions[1].location=1;
                attributeDescriptions[1].format=VK_FORMAT_R32G32B32_SFLOAT;
                attributeDescriptions[1].offset=OFFSETOF_COLOR;

                // Texture coordinates
                attributeDescriptions[2]={};
                attributeDescriptions[2].binding=0;
                attributeDescriptions[2].location=2;
                attributeDescriptions[2].format=VK_FORMAT_R32G32_SFLOAT;
                attributeDescriptions[2].offset=OFFSETOF_TEXTCOORDS;

        VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo={};
                   vkPipelineVertexInputStateCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
                vkPipelineVertexInputStateCreateInfo.pVertexBindingDescriptions=&ax;
        vkPipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions=attributeDescriptions; 
        vkPipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount=0;
        vkPipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount =0;
        vkPipelineVertexInputStateCreateInfo.pNext=VK_NULL_HANDLE;


        VkPipelineInputAssemblyStateCreateInfo inputAssembly={};
                   inputAssembly.sType=VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
                inputAssembly.topology=VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
                inputAssembly.primitiveRestartEnable=VK_FALSE;
                inputAssembly.pNext=VK_NULL_HANDLE;
        /*todo: Fixed Viewport COnstruction/Initilaistaion?Configration: ([Had use wrong Function?method Veowpprt/Stagong function Calls/cfongurations e.g.])
         *(had also used vkViewport instead of VkViewport of Type Buffer which is the atcual correct Obejct/Stage/Steup.veiwport conponnat.consituent
         *
         * (CorretcioN: had actually also used viewportBuffer and not vkViewport(Of type VkViewport.Bufferand not VkViewPort....) in VkPipelineViewportStateCreateInfo as well)
         */
        VkViewport vkViewport{};
                vkViewport.x=0.0F;
                vkViewport.y=0.0F;
                vkViewport.width=static_cast<float>(SwapChainSupportDetails::swapChainExtent.width);
                vkViewport.height=static_cast<float>(SwapChainSupportDetails::swapChainExtent.height);
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
                vkViewPortState.pNext=VK_NULL_HANDLE;


        VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization={};
                   VkPipeLineRasterization.sType=VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
                VkPipeLineRasterization.depthClampEnable=VK_FALSE;
                VkPipeLineRasterization.rasterizerDiscardEnable=VK_FALSE;
                VkPipeLineRasterization.polygonMode=VK_POLYGON_MODE_FILL;
                VkPipeLineRasterization.lineWidth=1.0f;
//                   .cullMode(VK_CULL_MODE_BACK_BIT)
//                   .frontFace(VK_FRONT_FACE_COUNTER_CLOCKWISE)
                VkPipeLineRasterization.depthBiasEnable=VK_FALSE;
                VkPipeLineRasterization.pNext=VK_NULL_HANDLE;

        //todo: actuall need multismapling to Compleet.Initialsie.Construct.Substanciate the renderPipeline corretcly even if Antialsing /AF/MMs are not neeeded......
        VkPipelineMultisampleStateCreateInfo multisampling={};
                   multisampling.sType=VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
                multisampling.sampleShadingEnable=VK_FALSE;
                multisampling.rasterizationSamples=VK_SAMPLE_COUNT_1_BIT;
                multisampling.minSampleShading =1;
                multisampling.pSampleMask = VK_NULL_HANDLE;
		multisampling.alphaToCoverageEnable = VK_FALSE;
		multisampling.alphaToOneEnable = VK_FALSE;


        VkPipelineDepthStencilStateCreateInfo depthStencil={};
                   depthStencil.sType=VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
                depthStencil.depthTestEnable=VK_TRUE;
                depthStencil.depthWriteEnable=VK_TRUE;
                depthStencil.depthCompareOp=VK_COMPARE_OP_LESS;
                depthStencil.depthBoundsTestEnable=VK_FALSE;
//                    .minDepthBounds(0) //Optional
//                    .maxDepthBounds(1) //Optional
                depthStencil.stencilTestEnable=VK_FALSE;


        VkPipelineColorBlendAttachmentState colorBlendAttachment={};
                colorBlendAttachment.colorWriteMask=VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
                //(Actually)Add blending?transparency to be suproted
                colorBlendAttachment.blendEnable=VK_FALSE;
                colorBlendAttachment.srcColorBlendFactor=VK_BLEND_FACTOR_SRC_ALPHA;
//                    .dstColorBlendFactor(VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA);
                colorBlendAttachment.dstColorBlendFactor=VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
//                    .colorBlendOp(VK_BLEND_OP_MAX)

//                    .srcAlphaBlendFactor(VK_BLEND_FACTOR_ONE)
//                    .dstAlphaBlendFactor(VK_BLEND_FACTOR_ZERO)
//                    .alphaBlendOp(VK_BLEND_OP_ADD);

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

        VkPushConstantRange vkPushConstantRange={};
                vkPushConstantRange.offset=0;
                vkPushConstantRange.size=16 * sizeof(float);
                vkPushConstantRange.stageFlags=VK_SHADER_STAGE_VERTEX_BIT;


        VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo={};
                   vkPipelineLayoutCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                vkPipelineLayoutCreateInfo.pPushConstantRanges=&vkPushConstantRange;
                vkPipelineLayoutCreateInfo.pSetLayouts=0;//&UniformBufferObject::descriptorSetLayout;
                vkPipelineLayoutCreateInfo.flags=0;
                vkPipelineLayoutCreateInfo.pushConstantRangeCount =0;
                vkPipelineLayoutCreateInfo.setLayoutCount=0;
                vkPipelineLayoutCreateInfo.pNext=VK_NULL_HANDLE;
                           vkPipelineLayoutCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
       


        std::cout << ("using pipeLine with Length: ") << sizeof(SwapChainSupportDetails::swapChainImageViews);
        //nmemFree(vkPipelineLayoutCreateInfo1.address());
        clPPPI(&vkPipelineLayoutCreateInfo, "vkCreatePipelineLayout", &vkLayout);
        //MemSysm.Memsys2.doPointerAllocSafeX(vkPipelineLayoutCreateInfo, Buffers.capabilities.vkCreatePipelineLayout, Buffers.vkLayout);


        VkGraphicsPipelineCreateInfo pipelineInfo={};
                pipelineInfo.sType=VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
                pipelineInfo.pStages=shaderStages;
                pipelineInfo.pNext=VK_NULL_HANDLE;
                pipelineInfo.stageCount=2;
                pipelineInfo.pVertexInputState=&vkPipelineVertexInputStateCreateInfo;
                pipelineInfo.pInputAssemblyState=&inputAssembly;
                pipelineInfo.pViewportState=&vkViewPortState;
                pipelineInfo.pRasterizationState=&VkPipeLineRasterization;
                pipelineInfo.pMultisampleState=&multisampling;
                pipelineInfo.pDepthStencilState=&depthStencil,
                pipelineInfo.pColorBlendState=&colorBlending;
//              pipelineInfo      .pDynamicState(null)
                pipelineInfo.layout=vkLayout;
                pipelineInfo.renderPass=SwapChainSupportDetails::renderPass;
                pipelineInfo.subpass=0;
                   pipelineInfo.basePipelineHandle=VK_NULL_HANDLE;
                pipelineInfo.basePipelineIndex=-1;
        
       

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

    inline void PipelineX::createCommandBuffers()
{
    VkCommandBufferAllocateInfo allocateInfo = {};
                allocateInfo.sType=(VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO);
                allocateInfo.commandPool=(Queues::commandPool);
                allocateInfo.level=(VK_COMMAND_BUFFER_LEVEL_PRIMARY);
                allocateInfo.commandBufferCount=(sizeof(commandBuffers)/sizeof(VkCommandBuffer));
        std::cout<< allocateInfo.commandBufferCount << "Command Buffers"<<"\n";
        // = memPointerBuffer(allocateInfo.address(), allocateInfo.commandBufferCount());
//            MemSysm.Memsys2.free(allocateInfo);
        vkAllocateCommandBuffers(device, &allocateInfo, PipelineX::commandBuffers);
        // doPointerAllocS(allocateInfo, capabilities.vkAllocateCommandBuffers, descriptorSets);
        // commandBuffers.put(descriptorSets);
        // descriptorSets.free();

        VkCommandBufferBeginInfo beginInfo1 = {};
                  beginInfo1.sType=VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                beginInfo1.flags=0;//(VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);

//            VkRenderPassAttachmentBeginInfo vkRenderPassAttachmentBeginInfo1 = VkRenderPassAttachmentBeginInfo.create(MemSysm.malloc(VkRenderPassAttachmentBeginInfo .SIZEOF))
//                    .sType$Default();
        //.pAttachments(VkUtils2.MemSys.stack.longs(VkUtils2.SwapChainSupportDetails.swapChainImageViews));
        VkRect2D renderArea = {};
                renderArea.offset={0,0};//(set);
                renderArea.extent=(SwapChainSupportDetails::swapChainExtent);


        VkClearValue clearValues[2]={};
                clearValues[0].color.float32[0]=0.0F;
                clearValues[0].color.float32[1]=0.0F;
                clearValues[0].color.float32[2]=0.0F;
                clearValues[0].color.float32[3]=0.0F;
                clearValues[1].depthStencil={1.0f, 0};


        VkRenderPassBeginInfo renderPassInfo = {};
              renderPassInfo.sType=(VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO);
              renderPassInfo.pClearValues=(clearValues);
              renderPassInfo.clearValueCount=(1);
              renderPassInfo.renderPass=(SwapChainSupportDetails::renderPass);
              renderPassInfo.renderArea=(renderArea);
                int i=0;
               for (const VkCommandBuffer &commandBuffer : commandBuffers) 
               {
                    //extracted(beginInfo1, renderPassInfo, commandBuffer, i);

                        vkBeginCommandBuffer(commandBuffer, &beginInfo1);
        
                        renderPassInfo.framebuffer=(SwapChainSupportDetails::swapChainFramebuffers[i]);

                        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
                        {
                        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
                        vkCmdDraw(commandBuffer, 3, 0, 0, 0);
                        }
                        vkCmdEndRenderPass(commandBuffer);
                        vkEndCommandBuffer(commandBuffer);
                       i++;

                }
}

