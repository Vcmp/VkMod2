#pragma once




#include "src/Queues.hpp"
#include "src/SwapChainSupportDetails.hpp"
#include "src/Texture.hpp"
#include "src/Buffers.hpp"
#include "src/UniformBufferObject.hpp"
#include "src/ShaderSPIRVUtils.hpp"
#include <stdint.h>
#include <vulkan/vulkan_core.h>

VkPipeline graphicsPipeline;
VkCommandPool commandPool;

struct Pipeline
{
    static void createRenderPasses();
    static void createGraphicsPipelineLayout();
    static VkShaderModule createShaderModule(char&,  VkShaderModuleCreateInfo&);
    static void createCommandPool();
};


inline void Pipeline::createRenderPasses()
    {
        int capacity = 2;
        VkAttachmentDescription attachments[2];
        VkAttachmentReference attachmentsRefs[2];
        uint32_t abs;
//            if (!depthEnabled)
//            {
//                abs=VK_SUBPASS_EXTERNAL;
//            }
        //else
        abs = VK_SUBPASS_CONTENTS_INLINE;

        attachmentsRefs[0]={
                .attachment=0,
                .layout=VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        };


        attachments[0]={
                .format=swapChainImageFormat.format,
                .samples=VK_SAMPLE_COUNT_1_BIT,
                .loadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .storeOp=VK_ATTACHMENT_STORE_OP_DONT_CARE,
                    .stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                    .stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout=VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout=VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
        };
        VkSubpassDescription vkSubpassDescriptions{
                .pipelineBindPoint=VK_PIPELINE_BIND_POINT_GRAPHICS,
                .colorAttachmentCount=1,
                .pColorAttachments=attachmentsRefs
        };

        attachments[1]={
                .format=findDepthFormat(),
                .samples=VK_SAMPLE_COUNT_1_BIT,
                .loadOp=VK_ATTACHMENT_LOAD_OP_CLEAR,
                .storeOp=VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .stencilLoadOp=VK_ATTACHMENT_LOAD_OP_DONT_CARE,
                .stencilStoreOp=VK_ATTACHMENT_STORE_OP_DONT_CARE,
                .initialLayout=VK_IMAGE_LAYOUT_UNDEFINED,
                .finalLayout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
        };


       attachmentsRefs[1]={
                .attachment=1,
                .layout=VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
        };
        vkSubpassDescriptions.pDepthStencilAttachment= &attachmentsRefs[1];


        VkSubpassDependency dependency ={
                .srcSubpass=abs,
                .dstSubpass=0,
                .srcStageMask=VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
                .srcAccessMask=VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
                .dstStageMask=VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
                .dstAccessMask=VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT,
                .dependencyFlags=VK_DEPENDENCY_BY_REGION_BIT
        };


        VkRenderPassCreateInfo vkRenderPassCreateInfo1;
        vkRenderPassCreateInfo1.sType=VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
                vkRenderPassCreateInfo1.pAttachments=attachments;
                vkRenderPassCreateInfo1.pSubpasses=&vkSubpassDescriptions;
        vkRenderPassCreateInfo1.pDependencies=&dependency;
        vkRenderPassCreateInfo1.dependencyCount=1;

        vkCreateRenderPass(device, &vkRenderPassCreateInfo1, nullptr, &renderPass);
       

    }

 static  VkVertexInputBindingDescription* getVertexInputBindingDescription()
    {
         VkVertexInputBindingDescription a {
                .binding=0,
//                    .stride(vertices.length/2)
//                    .stride(vertices.length/VERT_SIZE+1)
                .stride=32,
                .inputRate=VK_VERTEX_INPUT_RATE_VERTEX
        };
        return &a;
    }

//     static VkVertexInputAttributeDescription*  getAttributeDescriptions()
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
//         VkVertexInputAttributeDescription *texCoordsDescription = attributeDescriptions[2];
//         texCoordsDescription->binding=0;
//         texCoordsDescription->location=2;
//         texCoordsDescription->format=VK_FORMAT_R32G32_SFLOAT;
//         texCoordsDescription->offset=OFFSETOF_TEXTCOORDS;

// //            memFree(attributeDescriptions);

//         return attributeDescriptions;
//     }

    inline void Pipeline::createGraphicsPipelineLayout()
    {
        std::cout<<("Setting up PipeLine")<< "\n";

        const char vertShaderSPIRV = ShaderSPIRVUtils::compileShaderFile("shaders/21_shader_ubo.vert.spv", nullptr);
         const char fragShaderSPIRV = ShaderSPIRVUtils::compileShaderFile("shaders/21_shader_ubo.frag.spv", nullptr);

        const VkShaderModule vertShaderModule = ShaderSPIRVUtils::createShaderModule(&vertShaderSPIRV, sizeof(vertShaderSPIRV));
        const VkShaderModule fragShaderModule = ShaderSPIRVUtils::createShaderModule(&fragShaderSPIRV, sizeof(fragShaderSPIRV));

        constexpr char entryPoint[]={"main"};

        VkPipelineShaderStageCreateInfo shaderStages[2];

        shaderStages[0]={
            .sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, 
            .pNext=nullptr,
//                    .sType(VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO)
                .stage=VK_SHADER_STAGE_VERTEX_BIT,
                .module=vertShaderModule,
                .pName=entryPoint
                
        };

        shaderStages[1]={
                .sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                .stage=VK_SHADER_STAGE_FRAGMENT_BIT,
                .module=fragShaderModule,
                .pName=entryPoint
        };


        VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo;
                   vkPipelineVertexInputStateCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
                vkPipelineVertexInputStateCreateInfo.pVertexBindingDescriptions=getVertexInputBindingDescription();
        // vkPipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions= getAttributeDescriptions();
        // VkPipelineVertexInputStateCreateInfo.nvertexAttributeDescriptionCount=3;


        VkPipelineInputAssemblyStateCreateInfo inputAssembly;
                   inputAssembly.sType=VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
                inputAssembly.topology=VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
                inputAssembly.primitiveRestartEnable=false;
        /*todo: Fixed Viewport COnstruction/Initilaistaion?Configration: ([Had use wrong Function?method Veowpprt/Stagong function Calls/cfongurations e.g.])
         *(had also used vkViewport instead of VkViewport of Type Buffer which is the atcual correct Obejct/Stage/Steup.veiwport conponnat.consituent
         *
         * (CorretcioN: had actually also used viewportBuffer and not vkViewport(Of type VkViewport.Bufferand not VkViewPort....) in VkPipelineViewportStateCreateInfo as well)
         */
        VkViewport vkViewport{
                .x=0.0F,
                .y=0.0F,
                .width=static_cast<float>(swapChainExtent.width),
                .height=static_cast<float>(swapChainExtent.height),
                .minDepth=0.0F,
                .maxDepth=1.0F
        };

        VkRect2D scissor{
//                    .offset(vkOffset2D ->vkViewport.y()) //todo: not sure if correct Offset
                .offset=set,
                .extent=swapChainExtent
        };

        VkPipelineViewportStateCreateInfo vkViewPortState;
                   vkViewPortState.sType=VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
                vkViewPortState.pViewports=&vkViewport;
//                    .pScissors(vkrect2DBuffer);
                vkViewPortState.pScissors=&scissor;


        VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization;
                   VkPipeLineRasterization.sType=VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
                VkPipeLineRasterization.depthClampEnable=false;
                VkPipeLineRasterization.rasterizerDiscardEnable=false;
                VkPipeLineRasterization.polygonMode=VK_POLYGON_MODE_FILL;
                VkPipeLineRasterization.lineWidth=1.0f;
//                   .cullMode(VK_CULL_MODE_BACK_BIT)
//                   .frontFace(VK_FRONT_FACE_COUNTER_CLOCKWISE)
                VkPipeLineRasterization.depthBiasEnable=false;

        //todo: actuall need multismapling to Compleet.Initialsie.Construct.Substanciate the renderPipeline corretcly even if Antialsing /AF/MMs are not neeeded......
        VkPipelineMultisampleStateCreateInfo multisampling;
                   multisampling.sType=VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
                multisampling.sampleShadingEnable=false;
                multisampling.rasterizationSamples=VK_SAMPLE_COUNT_1_BIT;
//                    .alphaToOneEnable(false)
//                    .alphaToCoverageEnable(false);


        VkPipelineDepthStencilStateCreateInfo depthStencil;
                   depthStencil.sType=VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
                depthStencil.depthTestEnable=true;
                depthStencil.depthWriteEnable=true;
                depthStencil.depthCompareOp=VK_COMPARE_OP_LESS;
                depthStencil.depthBoundsTestEnable=false;
//                    .minDepthBounds(0) //Optional
//                    .maxDepthBounds(1) //Optional
                depthStencil.stencilTestEnable=false;


        VkPipelineColorBlendAttachmentState colorBlendAttachment;
                colorBlendAttachment.colorWriteMask=VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
                //(Actually)Add blending?transparency to be suproted
                colorBlendAttachment.blendEnable=true;
                colorBlendAttachment.srcColorBlendFactor=VK_BLEND_FACTOR_SRC_ALPHA;
//                    .dstColorBlendFactor(VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA);
                colorBlendAttachment.dstColorBlendFactor=VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
//                    .colorBlendOp(VK_BLEND_OP_MAX)

//                    .srcAlphaBlendFactor(VK_BLEND_FACTOR_ONE)
//                    .dstAlphaBlendFactor(VK_BLEND_FACTOR_ZERO)
//                    .alphaBlendOp(VK_BLEND_OP_ADD);

        // float blendConstants[]={0.0f, 0.0f, 0.0f, 0.0f};
        VkPipelineColorBlendStateCreateInfo colorBlending;
                   colorBlending.sType=VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
                colorBlending.logicOpEnable=false;
                colorBlending.logicOp=VK_LOGIC_OP_COPY;
                colorBlending.pAttachments=&colorBlendAttachment;
                colorBlending.blendConstants[0]=0.0f;
                colorBlending.blendConstants[1]=0.0f;
                colorBlending.blendConstants[2]=0.0f;
                colorBlending.blendConstants[3]=0.0f;
//            memFree(colorBlendAttachment);

        VkPushConstantRange vkPushConstantRange;
                vkPushConstantRange.offset=0;
                vkPushConstantRange.size=16 * sizeof(float);
                vkPushConstantRange.stageFlags=VK_SHADER_STAGE_VERTEX_BIT;
        VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo;
                   vkPipelineLayoutCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                vkPipelineLayoutCreateInfo.pPushConstantRanges=&vkPushConstantRange;
                vkPipelineLayoutCreateInfo.pSetLayouts=&UniformBufferObject::descriptorSetLayout;
        //                    .sType(VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO)
       


        std::cout << ("using pipeLine with Length: ") << sizeof(swapChainImagesViews);
        //nmemFree(vkPipelineLayoutCreateInfo1.address());
        vkCreatePipelineLayout(device, &vkPipelineLayoutCreateInfo, nullptr, &vkLayout);
        //MemSysm.Memsys2.doPointerAllocSafeX(vkPipelineLayoutCreateInfo, Buffers.capabilities.vkCreatePipelineLayout, Buffers.vkLayout);


        VkGraphicsPipelineCreateInfo pipelineInfo{
//                    .sType(VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO)
                .pStages=shaderStages,
                .pVertexInputState=&vkPipelineVertexInputStateCreateInfo,
                .pInputAssemblyState=&inputAssembly,
                .pViewportState=&vkViewPortState,
                .pRasterizationState=&VkPipeLineRasterization,
                .pMultisampleState=&multisampling,
                .pDepthStencilState=&depthStencil,
                .pColorBlendState=&colorBlending,
//                    .pDynamicState(null)
                .layout=vkLayout,
                .renderPass=renderPass,
                .subpass=0,
//                    .basePipelineHandle(VK_NULL_HANDLE)
                .basePipelineIndex=-1
        };
       

        //Memsys2.free(entryPoint);

        vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline);
        // Buffers.graphicsPipeline = MemSysm.doPointerAlloc5L(device, pipelineInfo);

        vkDestroyShaderModule(device, vertShaderModule, nullptr);
        vkDestroyShaderModule(device, fragShaderModule, nullptr);

    }

     inline VkShaderModule createShaderModule(char& spirvCode, VkShaderModuleCreateInfo* pShaderCreateInfo) {

        {
            VkShaderModule a = nullptr;
            vkCreateShaderModule(device, pShaderCreateInfo, nullptr, &a);
            return a;
        }
    }

    inline void Pipeline::createCommandPool()
    {
        VkCommandPoolCreateInfo poolInfo={};
                poolInfo.queueFamilyIndex=graphicsFamily;
                poolInfo.flags=0;
        //Memsys2.free(poolInfo);
        vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
    }