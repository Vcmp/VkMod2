#include "Queues.hpp"
#include "Buffers.hpp"
#include "Pipeline.hpp"
#include <vulkan/vulkan_core.h>


// //this Code ios extremely Ugly ATm just t get an intial Primtive./Rundimenray.baisc/Makshift/Crude/Limited/ Inhibited/Impelmhetd SetuP Runnign


// void textTemp::doBuffers()
// {
//   //   auto x1 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT );
//   // auto p1 = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
//   // BuffersX::createSetBuffer( p1, VertexTemp, x1, (sizeof(Vktemp)), VertexTempMem );

//   // VkBufferUsageFlagBits x2 = { VK_BUFFER_USAGE_TRANSFER_SRC_BIT };
//   // constexpr auto        p  = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
//   //  BuffersX::createSetBuffer( p, BuffersX::Bufferstaging, x2, (sizeof(Vktemp)), BuffersX::stagingBufferMemory );

//   // textTemp::vkMappedCopy(BuffersX::stagingBufferMemory, (sizeof(Vktemp)), Vktemp, BuffersX::data, VertexTemp);

// }


// void textTemp::vkMappedCopy(VkDeviceMemory &Staging, size_t size, const float* srcVectBuffs, __m256 *data, VkBuffer& Temp)
// {
//   void* autoMemAllocs;
//   vkMapMemory( Queues::device, Staging, 0, size, 0, reinterpret_cast<void**>(&data) );
//   {
//     memcpy(data, srcVectBuffs, size );
//   }
//   vkUnmapMemory( Queues::device, Staging );
//     BuffersX::copyBuffer(Temp, size);
// }

// //Might getaway without need for Addiitonal/Self-Conatined /Dedicated renderpass...
// void textTemp::initPipelineCustom(bool transparency)
// {
//     static constexpr VkViewport vkViewport{ .x = 0.0F, .y = 0.0F, .width = width, .height = height, .minDepth = 0.0F, .maxDepth = 1.0F };

//   static constexpr VkRect2D scissor{ .offset = { 0, 0 }, .extent{ width, height } };

//   constexpr VkPipelineViewportStateCreateInfo vkViewPortState = {
//     .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, .viewportCount = 1, .pViewports = &vkViewport, .scissorCount = 1, .pScissors = &scissor
//   };



//    const VkPipelineShaderStageCreateInfo vertexStage2 = {
//           .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
//           .stage  = VK_SHADER_STAGE_VERTEX_BIT,
//           .module = Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &SPV.VsMCI3temp, "vkCreateShaderModule" ),
//           .pName  = "main",

//         }; 
        
//         const VkPipelineShaderStageCreateInfo fragStage2 = {
//           .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
//           .stage  = VK_SHADER_STAGE_FRAGMENT_BIT,
//           .module = Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &SPV.VsMCI4temp, "vkCreateShaderModule" ),
//           .pName  = "main",

//         }; 

//         vkShaderStages[0]={vertexStage2},
//         vkShaderStages[1]={fragStage2};

// static constexpr VkPipelineColorBlendAttachmentState colorBlendAttachment = {
//     .blendEnable    = VK_FALSE,
//     .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,

//   };

// constexpr VkPipelineColorBlendStateCreateInfo colourBlendState
// {
//     .sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
//     .logicOpEnable   = VK_FALSE,
//     .logicOp         = VK_LOGIC_OP_COPY,
//     .attachmentCount = 1,
//     .pAttachments    = &colorBlendAttachment,
// };

//     static constexpr VkVertexInputAttributeDescription attributeDescriptions[2]{
//     { .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = 0 },
//     { .location = 2, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = 12 },
//     // { .location = 3, .binding = 0, .format = VK_FORMAT_R32G32_SFLOAT, .offset = 0 },
//     // { .location = 4, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = sizeof(float) * 2}
//   };

//  constexpr VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization = {
//     .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
//     .depthClampEnable        = VK_FALSE,
//     .rasterizerDiscardEnable = VK_FALSE,
//     .polygonMode             = VK_POLYGON_MODE_FILL,
//     .cullMode                = VK_CULL_MODE_NONE,  // WARNING: VERY IMPORTANT!:
//                                                        // Make sure the culling direction is correct
//                                                        // as it applies even to 2DVecs/Fixed
//                                                        // Function Runtime/Evaluated Shaders
//                                                        // with no transforms and with fixed
//                                                        // Const/Pre-Determined Runtime
//                                                        // Variables
//     .frontFace       = VK_FRONT_FACE_COUNTER_CLOCKWISE,
//     .depthBiasEnable = VK_FALSE,
//     .lineWidth       = 1.0F,
//   };

//     constexpr VkPipelineMultisampleStateCreateInfo multisampling = { .sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
//                                                                    .rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT,
//                                                                    .sampleShadingEnable   = VK_FALSE,
//                                                                    .minSampleShading      = 1.0F,
//                                                                    .pSampleMask           = VK_NULL_HANDLE,
//                                                                    .alphaToCoverageEnable = VK_FALSE,
//                                                                    .alphaToOneEnable      = VK_FALSE };


//   static constexpr VkVertexInputBindingDescription VxL2{ 0, (24 ), VK_VERTEX_INPUT_RATE_VERTEX };

  
//   static constexpr VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo = {
//     .sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
//     .vertexBindingDescriptionCount   = 1,
//     .pVertexBindingDescriptions      = &VxL2,
//     .vertexAttributeDescriptionCount = 0,//sizeof( attributeDescriptions ) / sizeof( VkVertexInputAttributeDescription ),
//     // .pVertexAttributeDescriptions    = attributeDescriptions
//   };

//   static constexpr VkPipelineInputAssemblyStateCreateInfo inputAssembly = { .sType    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
//                                                                             .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
//                                                                             .primitiveRestartEnable = VK_FALSE };
//   constexpr VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo = { .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
//                                                                       // .setLayoutCount         = 1,
//                                                                       // .pSetLayouts            = &UniformBufferObject::descriptorSetLayout,
//                                                                       .pushConstantRangeCount = 0,
//                                                                        };

//   // std::cout << ( "using pipeLine with Length: " ) << sizeof( SwapChainSupportDetails::swapChainImageViews );
//   VkPipelineLayout vkLayout;
//   VkUtilsXBase::clPPPI3<PFN_vkCreatePipelineLayout>( &vkPipelineLayoutCreateInfo, "vkCreatePipelineLayout", &vkLayout );

//       VkGraphicsPipelineCreateInfo xx
//      { 
//           .sType      = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
//           .stageCount=1,
//           .pStages = vkShaderStages,
//           .pVertexInputState=&vkPipelineVertexInputStateCreateInfo,
//           .pInputAssemblyState=&inputAssembly,
//           .pViewportState = &vkViewPortState,
//           .pRasterizationState=&VkPipeLineRasterization,
//           .pMultisampleState=&multisampling,
//           .pDepthStencilState=nullptr,
//           .pColorBlendState=&colourBlendState,
//           .layout=vkLayout,
//           .renderPass = tempRenderPass,
//           .basePipelineHandle=x,
//           .basePipelineIndex=0,
//       };

//       vkCreateGraphicsPipelines(Queues::device, nullptr, 1, &xx, nullptr, &x);
// }

// void textTemp::voidrecComBufferSub(int i)
// {

//   vkResetCommandPool(Queues::device, p, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT);

//   beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
//                                                     .flags = ( VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) };

//   renderArea = { .offset = { 0, 0 }, .extent = swapChainExtent};

//   //Check if using Same Imageview is Ok For multiple FraemBuffers.renderPasses e.g. .etc. i.e. .Misc
//   VkRenderPassAttachmentBeginInfo RenderPassAttachments
//   {
//     .sType = VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO,
//     .attachmentCount = 1,
//     .pAttachments = &SwapChainSupportDetails::swapChainImageViews[i]
//   };

//   static VkRenderPassBeginInfo renderPassInfo = {
//     .sType           = ( VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),
//     .pNext = &RenderPassAttachments,
//     .renderPass      = ( tempRenderPass ),
//     .framebuffer     = tempFramebuffers[i],
//     .renderArea      = renderArea,
//     // .clearValueCount = 1,
//     // .pClearValues    = &clearValues2,
//   };

//     offsets[0] = { 0 };

//     vkBeginCommandBuffer(comBuffer, &beginInfo1);

//     vkCmdBeginRenderPass(comBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

//     vkCmdBindPipeline(comBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,x );
//     vkCmdBindVertexBuffers(comBuffer, 0, 1, &BuffersX::vertexBuffer, offsets );
//     vkCmdBindIndexBuffer(comBuffer, BuffersX::indexBuffer, 0, VK_INDEX_TYPE_UINT16 );

     


//     vkCmdDrawIndexed( comBuffer, ( ( BuffersX::sizedsfIdx ) / 2 ), 1, 0, 0, 0 );


//     vkCmdEndRenderPass( comBuffer );
//     VkUtilsXBase::clP<PFN_vkEndCommandBuffer>( comBuffer, "vkEndCommandBuffer" );




    
// }

// void textTemp::genFrameBuffers()
// {
    
//     static constexpr VkFramebufferAttachmentImageInfo FramebufferAttachmentImage
//     {
//       .sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENT_IMAGE_INFO,
//       .pNext=nullptr,
//       .usage=VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT+1, //Possible Driver Bug Setting the Usage to 0x11 instead of 0x10 on the SwapChain Image Usage Flag...
//       .width= swapChainExtent.width,
//       .height= swapChainExtent.height,
//       .layerCount=1,
//       .viewFormatCount=1,
//       .pViewFormats=&swapChainImageFormat.format,
//     };

//     // VkFramebufferAttachmentImageInfo atts[3]={FramebufferAttachmentImage, FramebufferAttachmentImage, FramebufferAttachmentImage};
//     constexpr VkFramebufferAttachmentsCreateInfo FramebufferAttachments
//     {
//       .sType=VK_STRUCTURE_TYPE_FRAMEBUFFER_ATTACHMENTS_CREATE_INFO,
//       .pNext=nullptr,
//       .attachmentImageInfoCount=1,
//       .pAttachmentImageInfos=&FramebufferAttachmentImage,
//     };
    
//     VkFramebufferCreateInfo framebufferCreateInfo = {};
//     framebufferCreateInfo.sType                   = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
//     framebufferCreateInfo.pNext                   = &FramebufferAttachments,
//     framebufferCreateInfo.flags                   = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT;
//     framebufferCreateInfo.renderPass              = tempRenderPass;
//     framebufferCreateInfo.width                   = swapChainExtent.width;
//     framebufferCreateInfo.height                  = swapChainExtent.height;
//     framebufferCreateInfo.layers                  = 1;
//     framebufferCreateInfo.attachmentCount         = 1;
//     framebufferCreateInfo.pAttachments            = nullptr;


//     for (  size_t i =0; i< Frames; i++ )
//     {
//       // framebufferCreateInfo.pAttachments = &swapChainImageViews[i];

//       VkUtilsXBase::clPPPI3<PFN_vkCreateFramebuffer>( &framebufferCreateInfo, "vkCreateFramebuffer", &tempFramebuffers[i] );
//     }
//     // return tempFramebuffers;
// }


// VkRenderPass textTemp::genRenderPass()
// {
//   static const VkAttachmentDescription colorAttachment{
//     .format         = VK_FORMAT_B8G8R8A8_SRGB,  // SwapChainSupportDetails::swapChainImageFormat,
//     .samples        = VK_SAMPLE_COUNT_1_BIT,
//     .loadOp         = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
//     .storeOp        = VK_ATTACHMENT_STORE_OP_STORE,
//     .stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
//     .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
//     .initialLayout  = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, //--->!!!
//     .finalLayout    = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
//   };
//   //?Check Attahcment isn;t Wrong
//   static constexpr VkAttachmentReference colorAttachmentRef{ .attachment = 0, .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
//   static constexpr VkSubpassDescription  subpass{ .pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS,
//                                                   .colorAttachmentCount = 1,
//                                                   .pColorAttachments    = &colorAttachmentRef };

//   static constexpr VkSubpassDependency  VkSubpassDependency
//   {
//     .srcSubpass=VK_SUBPASS_EXTERNAL,
//     .dstSubpass=0,
//     .srcStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
//     .dstStageMask=VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
//     .srcAccessMask=0,
//     .dstAccessMask=VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT

//   };

//   constexpr VkRenderPassCreateInfo vkRenderPassCreateInfo1 = {
//     .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
//     //   .flags=VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT,
//     .attachmentCount = 1,
//     .pAttachments    = &colorAttachment,
//     .subpassCount    = 1,
//     .pSubpasses      = &subpass,
//     .dependencyCount=1,
//     .pDependencies=&VkSubpassDependency
//   };

//   VkUtilsXBase::clPPPI3<PFN_vkCreateRenderPass>( &vkRenderPassCreateInfo1, "vkCreateRenderPass", &tempRenderPass );
//   return tempRenderPass;
// }


// /* //Images "buffered" into Imageviews...
// void textTemp::genImageViews()
//   {
//     std::cout << ( "Creating Image Views" ) << "\n";
//     int i = 0;
//     for ( const VkImage & swapchainImage : tempImages )
//     {
//       VkImageViewCreateInfo createInfo = {};
//       createInfo.sType                 = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;

//       createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
//       createInfo.format   = swapChainImageFormat.format;

//       //     createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
//       // createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
//       // createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
//       //     createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

//       createInfo.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
//       createInfo.subresourceRange.baseMipLevel   = 0;
//       createInfo.subresourceRange.levelCount     = 1;
//       createInfo.subresourceRange.baseArrayLayer = 0;
//       createInfo.subresourceRange.layerCount     = 1;

//       createInfo.image = swapchainImage;

//       VkUtilsXBase::clPPPI3<PFN_vkCreateImageView>( &createInfo, "vkCreateImageView", &tempImageViews[i++] );
//     }
//   }
// void textTemp::genImages()
// {
//   std::cout << "ImageCount: " << imageCount << "\n";

//     const uint32_t aa[] = { Queues::graphicsFamily, Queues::transferFamily };
//     ;

//     const VkSwapchainCreateInfoKHR createInfo{

//       .sType   = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
//       .pNext   = nullptr,
//       .surface = Queues::surface,

//       // Image settings
//       .minImageCount    = imageCount,
//       .imageFormat      = swapChainImageFormat.format,
//       .imageColorSpace  = swapChainImageFormat.colorSpace,
//       .imageExtent      = swapChainExtent,
//       .imageArrayLayers = 1,
//       .imageUsage       = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT+1,

//       // if (graphicsFamily != presentFamily) {
//       .imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE,
//       .queueFamilyIndexCount = 1,
//       .pQueueFamilyIndices   = &aa[0],
//       // } else {
//       // .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
//       // .queueFamilyIndexCount = 0; // Optiona,
//       // .pQueueFamilyIndices = nullptr; // Optiona,
//       // }

//       .preTransform   = SwapChainSupportDetails::capabilities.currentTransform,
//       .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
//       .presentMode    = presentMode,
//       .clipped        = true,

//       .oldSwapchain = VK_NULL_HANDLE
//     };
//     std::cout << Queues::device << "\n";

//     VkUtilsXBase::clPPPI3<PFN_vkCreateSwapchainKHR>( &createInfo, "vkCreateSwapchainKHR", &swapChain );
//     VkUtilsXBase::checkCall( vkGetSwapchainImagesKHR( Queues::device, swapChain, &imageCount, tempImages ) );
// } */