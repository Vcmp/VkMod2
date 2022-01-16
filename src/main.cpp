#include "GLFW/glfw3.h"
// #include "mat4.hpp"
#include "VkUtils2.hpp"


// using namespace VkU2;
bool a = true;
//    private static boolean aa;

    int main()
    {
        // float laa[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        // mat4 m4;
        //  float laaa[16]={1};
        // mat4 m45;
        // m45.loadAligned(laaa);
        // m4.identity()->domatFMA(&m45);
      //  VkUtils2.extracted();
        //System.gc();

//            int i = 0;
		VkUtils2::extracted();
        // SwapChainSupportDetails::createSwapChain();
        // SwapChainSupportDetails::createImageViews();
        // Pipeline::createRenderPasses();
        // Pipeline::createGraphicsPipelineLayout();
        // Pipeline::createCommandPool();

        int aa=0;
        while (!glfwWindowShouldClose((window)))
        {


            //renderer2.Renderer2.drawFrame();
			// extracted();

            glfwPollEvents();
			// printf("%i \n", aa);
			aa++;

        }
        a=false;

        //VkUtils2.cleanup();
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    //todo: Wake from callBack...
    

inline void VkUtils2::createSwapChain()
{
            VkSurfaceFormatKHR surfaceFormat =  VkUtils2::querySwapChainSupport(physicalDevice);
        
            VkExtent2D extent = SwapChainSupportDetails::chooseSwapExtent(*window);
            uint32_t imageCount= (SwapChainSupportDetails::capabilities.minImageCount + 1);

            if (SwapChainSupportDetails::capabilities.maxImageCount > 0 && imageCount > SwapChainSupportDetails::capabilities.maxImageCount) {
                imageCount = SwapChainSupportDetails::capabilities.maxImageCount;
            }

            std::cout<<"ImageCount: "<<imageCount<<"\n";

            VkSwapchainCreateInfoKHR createInfo={};

                    createInfo.sType=VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
                    createInfo.surface=Queues::surface;

                    // Image settings
                    createInfo.minImageCount=imageCount;
                    createInfo.imageFormat=surfaceFormat.format;//=&surfaceFormat; //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!
                    createInfo.imageColorSpace=surfaceFormat.colorSpace;
                    createInfo.imageExtent=extent;
                    createInfo.imageArrayLayers=1;
                    createInfo.imageUsage=SwapChainSupportDetails::capabilities.supportedUsageFlags;
                    createInfo.pNext=nullptr;

                    createInfo.imageSharingMode=VK_SHARING_MODE_EXCLUSIVE;
                    // createInfo.queueFamilyIndexCount=0;
                    // createInfo.pQueueFamilyIndices= nullptr;
        
                    createInfo.preTransform=SwapChainSupportDetails::capabilities.currentTransform;
                    createInfo.compositeAlpha=VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
                    createInfo.presentMode=VK_PRESENT_MODE_IMMEDIATE_KHR;
                    createInfo.clipped=true;

                    createInfo.oldSwapchain=VK_NULL_HANDLE;
                    std::cout << device<<"\n";

            // vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain);
            // auto xx=PFN_vkVoidFunction(swapChain);
            clPPPI(&createInfo, "vkCreateSwapchainKHR", &swapChain); //BUGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG!
           ;


            checkCall(vkGetSwapchainImagesKHR(device, swapChain, &imageCount, pSwapchainImages));

            SwapChainSupportDetails::swapChainImageFormat =surfaceFormat;
            SwapChainSupportDetails::swapChainExtent = extent;
        
}

// inline void Texture::createDepthResources()
//     {
//           VkFormat depthFormat = findDepthFormat();
//         Texture::createImage(SwapChainSupportDetails::swapChainExtent.width, SwapChainSupportDetails::swapChainExtent.height,
//                 depthFormat,
//                 VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
//         );


//         createImageView(depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, Buffers::depthImageView);
//         transitionImageLayout(depthFormat,
//                 VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
//     }

    inline void Pipeline::createGraphicsPipelineLayout()
    {
        //Thankfully Dont; need to worry about compiling the Shader Files AnyMore due to
        std::cout<<("Setting up PipeLine")<< "\n";

        const VkShaderModule vertShaderModule = ShaderSPIRVUtils::compileShaderFile(device, "shaders/21_shader_ubo.vert.spv");
        const VkShaderModule fragShaderModule = ShaderSPIRVUtils::compileShaderFile(device, "shaders/21_shader_ubo.frag.spv");

        constexpr char entryPoint[]={"main"};

        VkPipelineShaderStageCreateInfo vertexStage={};
            vertexStage.sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            vertexStage.pNext=VK_NULL_HANDLE;
//                    .sType(VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO)
                vertexStage.stage=VK_SHADER_STAGE_VERTEX_BIT;
                vertexStage.module=vertShaderModule;
                vertexStage.pName=entryPoint;
                
       

        VkPipelineShaderStageCreateInfo fragStage={};
                fragStage.sType=VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                fragStage.pNext=VK_NULL_HANDLE;
                fragStage.stage=VK_SHADER_STAGE_FRAGMENT_BIT;
                fragStage.module=fragShaderModule;
                fragStage.pName=entryPoint;
        

        const VkPipelineShaderStageCreateInfo shaderStages[] = {vertexStage, fragStage};

        VkVertexInputBindingDescription a ={
                        .binding=0,
        //                    .stride(vertices.length/2)
        //                    .stride(vertices.length/VERT_SIZE+1)
                        .stride=32,
                        .inputRate=VK_VERTEX_INPUT_RATE_VERTEX
                };

        VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo={};
                   vkPipelineVertexInputStateCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
                vkPipelineVertexInputStateCreateInfo.pVertexBindingDescriptions=&a;
        // vkPipelineVertexInputStateCreateInfo.pVertexAttributeDescriptions= getAttributeDescriptions();
        // VkPipelineVertexInputStateCreateInfo.nvertexAttributeDescriptionCount=3;


        VkPipelineInputAssemblyStateCreateInfo inputAssembly={};
                   inputAssembly.sType=VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
                inputAssembly.topology=VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
                inputAssembly.primitiveRestartEnable=VK_FALSE;
        /*todo: Fixed Viewport COnstruction/Initilaistaion?Configration: ([Had use wrong Function?method Veowpprt/Stagong function Calls/cfongurations e.g.])
         *(had also used vkViewport instead of VkViewport of Type Buffer which is the atcual correct Obejct/Stage/Steup.veiwport conponnat.consituent
         *
         * (CorretcioN: had actually also used viewportBuffer and not vkViewport(Of type VkViewport.Bufferand not VkViewPort....) in VkPipelineViewportStateCreateInfo as well)
         */
        VkViewport vkViewport{
                .x=0.0F,
                .y=0.0F,
                .width=static_cast<float>(SwapChainSupportDetails::swapChainExtent.width),
                .height=static_cast<float>(SwapChainSupportDetails::swapChainExtent.height),
                .minDepth=0.0F,
                .maxDepth=1.0F
        };

        VkRect2D scissor{
//                    .offset(vkOffset2D ->vkViewport.y()) //todo: not sure if correct Offset
                .offset=Buffers::set,
                .extent=SwapChainSupportDetails::swapChainExtent
        };

        VkPipelineViewportStateCreateInfo vkViewPortState={};
                   vkViewPortState.sType=VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
                vkViewPortState.viewportCount=1;
                vkViewPortState.pViewports=&vkViewport;
//                    .pScissors(vkrect2DBuffer);
                vkViewPortState.scissorCount=1;
                vkViewPortState.pScissors=&scissor;


        VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization={};
                   VkPipeLineRasterization.sType=VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
                VkPipeLineRasterization.depthClampEnable=VK_FALSE;
                VkPipeLineRasterization.rasterizerDiscardEnable=VK_FALSE;
                VkPipeLineRasterization.polygonMode=VK_POLYGON_MODE_FILL;
                VkPipeLineRasterization.lineWidth=1.0f;
//                   .cullMode(VK_CULL_MODE_BACK_BIT)
//                   .frontFace(VK_FRONT_FACE_COUNTER_CLOCKWISE)
                VkPipeLineRasterization.depthBiasEnable=VK_FALSE;

        //todo: actuall need multismapling to Compleet.Initialsie.Construct.Substanciate the renderPipeline corretcly even if Antialsing /AF/MMs are not neeeded......
        VkPipelineMultisampleStateCreateInfo multisampling={};
                   multisampling.sType=VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
                multisampling.sampleShadingEnable=VK_FALSE;
                multisampling.rasterizationSamples=VK_SAMPLE_COUNT_1_BIT;
//                    .alphaToOneEnable(false)
//                    .alphaToCoverageEnable(false);


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
                colorBlendAttachment.blendEnable=VK_TRUE;
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
                colorBlending.blendConstants[0]=0.0f;
                colorBlending.blendConstants[1]=0.0f;
                colorBlending.blendConstants[2]=0.0f;
                colorBlending.blendConstants[3]=0.0f;
//            memFree(colorBlendAttachment);

        VkPushConstantRange vkPushConstantRange={};
                vkPushConstantRange.offset=0;
                vkPushConstantRange.size=16 * sizeof(float);
                vkPushConstantRange.stageFlags=VK_SHADER_STAGE_VERTEX_BIT;
        VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo;
                   vkPipelineLayoutCreateInfo.sType=VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                vkPipelineLayoutCreateInfo.pPushConstantRanges=&vkPushConstantRange;
                vkPipelineLayoutCreateInfo.pSetLayouts=&UniformBufferObject::descriptorSetLayout;
        //                    .sType(VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO)
       


        std::cout << ("using pipeLine with Length: ") << sizeof(SwapChainSupportDetails::swapChainImageViews);
        //nmemFree(vkPipelineLayoutCreateInfo1.address());
        vkCreatePipelineLayout(device, &vkPipelineLayoutCreateInfo, nullptr, &Buffers::vkLayout);
        //MemSysm.Memsys2.doPointerAllocSafeX(vkPipelineLayoutCreateInfo, Buffers.capabilities.vkCreatePipelineLayout, Buffers.vkLayout);


        VkGraphicsPipelineCreateInfo pipelineInfo{
                .sType=VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                .pStages=shaderStages,
                .stageCount=2,
                .pVertexInputState=&vkPipelineVertexInputStateCreateInfo,
                .pInputAssemblyState=&inputAssembly,
                .pViewportState=&vkViewPortState,
                .pRasterizationState=&VkPipeLineRasterization,
                .pMultisampleState=&multisampling,
                .pDepthStencilState=&depthStencil,
                .pColorBlendState=&colorBlending,
//                    .pDynamicState(null)
                .layout=Buffers::vkLayout,
                .renderPass=SwapChainSupportDetails::renderPass,
                .subpass=0,
//                    .basePipelineHandle(VK_NULL_HANDLE)
                .basePipelineIndex=-1
        };
       

        //Memsys2.free(entryPoint);

        vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline);
        // Buffers.graphicsPipeline = MemSysm.doPointerAlloc5L(device, pipelineInfo);

        vkDestroyShaderModule(device, vertShaderModule, VK_NULL_HANDLE );
        vkDestroyShaderModule(device, fragShaderModule, VK_NULL_HANDLE );

    }

    inline void UniformBufferObject::createDescriptorSetLayout()
{
     {
            VkDescriptorSetLayoutBinding bindings[]={
                   VkDescriptorSetLayoutBinding{
                    .binding=0,
                    .descriptorCount=1,
                    .descriptorType=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                    .stageFlags=VK_SHADER_STAGE_VERTEX_BIT
                   },

                 VkDescriptorSetLayoutBinding{
                    .binding=1,
                    .descriptorCount=1,
                    .descriptorType=VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                    //                         .pImmutableSamplers(null)
                    .stageFlags=VK_SHADER_STAGE_FRAGMENT_BIT
                    }
            };
            //samplerLayoutBinding
         


            VkDescriptorSetLayoutCreateInfo a{
                    .sType=VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
                    .pBindings=bindings,
                    
            };
            clPPPI(&a, "vkCreateDescriptorSetLayout", &UniformBufferObject::descriptorSetLayout);
            //return MemSysm.doPointerAllocSafe(a, device.getCapabilities().vkCreateDescriptorSetLayout);
        }
}