#pragma once

#include "Pipeline.hpp"
#include "Queues.hpp"
#include "SwapChainSupportDetails.hpp"
#include "Texture.hpp"
#include "UniformBufferObject.hpp"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

// #include <stdint.h>

static inline const struct VkUtils2
{
  static constinit inline GLFWwindow *   window;
  static constinit inline GLFWmonitor *  monitor;
  static constinit inline VkInstance     vkInstance;
  static const std::vector<const char *> getRequiredExtensions();
  static VKAPI_ATTR VkBool32 VKAPI_CALL  debugCallback( VkDebugUtilsMessageSeverityFlagBitsEXT,
                                                        VkDebugUtilsMessageTypeFlagsEXT,
                                                        const VkDebugUtilsMessengerCallbackDataEXT *,
                                                        void * );

  static VkResult createDebugUtilsMessengerEXT( const VkInstance, const VkDebugUtilsMessengerCreateInfoEXT * );

  static bool isDeviceSuitable( VkPhysicalDevice );
  static void checkDeviceExtensionSupport( VkPhysicalDevice );

  static const VkSurfaceFormatKHR querySwapChainSupport( VkPhysicalDevice );

  typedef VkResult( VKAPI_PTR * PFN_vkCreateDebugUtilsMessengerEXT2 )( VkInstance                                 instance,
                                                                       const VkDebugUtilsMessengerCreateInfoEXT * pCreateInfo,
                                                                       const VkAllocationCallbacks *              pAllocator,
                                                                       const VkDebugUtilsMessengerEXT *           pMessenger );

  //    private static final long[] pDebugMessenger = new long[1];
  //    X(),
  //    Y
  //    KEY(1)
  VkUtils2() __attribute__( ( cold ) )
  {
    extracted();
  }

  static void extracted();
  static void setupWindow();

  static void createInstance();
  static void createSurface();
  static bool checkValidationLayerSupport();

  static void setupDebugMessenger();

  static void pickPhysicalDevice();
  static void createLogicalDevice();
  static void cleanup() __attribute__( ( cold ) );
  ~VkUtils2()
  {
    cleanup();
  }
  // static void createSwapChain();
  // static void createImageViews();
  // static void createPipeLine();
} VKU2;

inline namespace
{}  // namespace

VkFormat PipelineX::findDepthFormat()
{
  constexpr VkFormat formatCandidates[3] = { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT };
  VkFormatProperties props;

  for ( const VkFormat & format : formatCandidates )
  {
    vkGetPhysicalDeviceFormatProperties( Queues::physicalDevice, format, &props );

    const uint32_t i2 = props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;
    if ( i2 == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT /* && VK10.VK_IMAGE_TILING_OPTIMAL == VK_IMAGE_TILING_OPTIMAL*/ )
    {
      return format;
    }
  }

  throw std::runtime_error( "failed to find supported format!" );
}

inline void PipelineX::createRenderPasses()
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
  static constexpr VkAttachmentReference colorAttachmentRef{ .attachment = 0, .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };
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

  VkUtilsXBase::clPPPI3<PFN_vkCreateRenderPass>( &vkRenderPassCreateInfo1, "vkCreateRenderPass", &SwapChainSupportDetails::renderPass );
}

inline void PipelineX::createGraphicsPipelineLayout()
{
  // Thankfully Dont; need to worry about compiling the Shader Files AnyMore due
  // to teh ability to premptively use the SPRI-V Compielr (e.g.GLSLC) prior to compile time...
  std::cout << ( "Setting up PipeLine" ) << "\n";

  // const VkShaderModule vertShaderModule = ShaderSPIRVUtils::compileShaderFile();
  // const VkShaderModule fragShaderModule = ShaderSPIRVUtils::compileShaderFile1();

  const VkPipelineShaderStageCreateInfo vertexStage = {
    .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
    .stage  = VK_SHADER_STAGE_VERTEX_BIT,
    .module = ShaderSPIRVUtils::compileShaderFile(),
    .pName  = "main",

  };

  const VkPipelineShaderStageCreateInfo fragStage = { .sType  = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                                                      .stage  = VK_SHADER_STAGE_FRAGMENT_BIT,
                                                      .module = ShaderSPIRVUtils::compileShaderFile1(),
                                                      .pName  = "main" };

  const VkPipelineShaderStageCreateInfo shaderStages[2] = { fragStage, vertexStage };

  static constexpr VkVertexInputBindingDescription VxL{ 0, ( 24 ), VK_VERTEX_INPUT_RATE_VERTEX };

  static constexpr VkVertexInputAttributeDescription attributeDescriptions[2]{
    { .location = 0, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = OFFSET_POS },
    { .location = 1, .binding = 0, .format = VK_FORMAT_R32G32B32_SFLOAT, .offset = OFFSETOF_COLOR },

  };

  static constexpr VkPipelineVertexInputStateCreateInfo vkPipelineVertexInputStateCreateInfo = {
    .sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .vertexBindingDescriptionCount   = 1,
    .pVertexBindingDescriptions      = &VxL,
    .vertexAttributeDescriptionCount = sizeof( attributeDescriptions ) / sizeof( VkVertexInputAttributeDescription ),
    .pVertexAttributeDescriptions    = attributeDescriptions
  };

  static constexpr VkPipelineInputAssemblyStateCreateInfo inputAssembly = { .sType    = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
                                                                            .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
                                                                            .primitiveRestartEnable = VK_FALSE };

  static constexpr VkViewport vkViewport{ .x = 0.0F, .y = 0.0F, .width = width, .height = height, .minDepth = UNormFlt, .maxDepth = 1.0F };

  static constexpr VkRect2D scissor{ .offset = { 0, 0 }, .extent{ width, height } };

  constexpr VkPipelineViewportStateCreateInfo vkViewPortState = {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, .viewportCount = 1, .pViewports = &vkViewport, .scissorCount = 1, .pScissors = &scissor
  };

  constexpr VkPipelineRasterizationStateCreateInfo VkPipeLineRasterization = {
    .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .depthClampEnable        = VK_FALSE,
    .rasterizerDiscardEnable = VK_FALSE,
    .polygonMode             = VK_POLYGON_MODE_FILL,
    .cullMode                = VK_CULL_MODE_BACK_BIT,  // WARNING: VERY IMPORTANT!:
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
    .depthCompareOp        = VK_COMPARE_OP_LESS,
    .depthBoundsTestEnable = VK_FALSE,
    .stencilTestEnable     = VK_FALSE,
  };
  static constexpr VkPipelineColorBlendAttachmentState colorBlendAttachment = {
    .blendEnable    = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,

  };
  constexpr VkPipelineColorBlendStateCreateInfo colorBlending = {
    .sType           = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .logicOpEnable   = VK_FALSE,
    .logicOp         = VK_LOGIC_OP_COPY,
    .attachmentCount = 1,
    .pAttachments    = &colorBlendAttachment,

  };

  static constexpr VkPushConstantRange vkPushConstantRange{
    .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
    .offset     = 0,
    .size       = sizeof( mat4x ),
  };

  constexpr VkPipelineLayoutCreateInfo vkPipelineLayoutCreateInfo = { .sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
                                                                      .setLayoutCount         = 1,
                                                                      .pSetLayouts            = &UniformBufferObject::descriptorSetLayout,
                                                                      .pushConstantRangeCount = 1,
                                                                      .pPushConstantRanges    = &vkPushConstantRange };

  std::cout << ( "using pipeLine with Length: " ) << sizeof( SwapChainSupportDetails::swapChainImageViews );
  VkUtilsXBase::clPPPI3<PFN_vkCreatePipelineLayout>( &vkPipelineLayoutCreateInfo, "vkCreatePipelineLayout", &vkLayout );

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
                                                   .renderPass          = renderPass };
  VkUtilsXBase::clPPPJI<PFN_vkCreateGraphicsPipelines>( &pipelineInfo, 1, "vkCreateGraphicsPipelines", &graphicsPipeline );
}

inline void PipelineX::createCommandBuffers()
{
  const VkCommandBufferAllocateInfo allocateInfo{ .sType              = ( VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ),
                                                  .commandPool        = ( Queues::commandPool ),
                                                  .level              = ( VK_COMMAND_BUFFER_LEVEL_PRIMARY ),
                                                  .commandBufferCount = sizeof( commandBuffers ) / sizeof( VkCommandBuffer ) };
  std::cout << allocateInfo.commandBufferCount << "Command Buffers"
            << "\n";
  VkUtilsXBase::clPPI3<PFN_vkAllocateCommandBuffers>( &allocateInfo, "vkAllocateCommandBuffers", commandBuffers );

  constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT ) };

  /*   VkRenderPassAttachmentBeginInfo attachmentsbeginInfo{ .sType =
     VK_STRUCTURE_TYPE_RENDER_PASS_ATTACHMENT_BEGIN_INFO, .attachmentCount = 1, .pAttachments =
                                                            &SwapChainSupportDetails::swapChainImageViews[0] };

   */
  constexpr VkRect2D renderArea = { .offset = { 0, 0 }, .extent = SwapChainSupportDetails::swapChainExtent };

  // constexpr VkClearColorValue aa[] = { { { UNormFlt, UNormFlt, UNormFlt, 1.0F } } };
  // // constexpr VkClearDepthStencilValue aaa[] = { { { 0.0F, 1.0F } } };
  // constexpr VkClearValue clearValues = {
  //   .color = { { UNormFlt, UNormFlt, UNormFlt, 1.0F } }
  //   // .depthStencil = { 0.0F, static_cast<uint32_t>( 1.0F ) },
  // };
  constexpr VkClearValue clearValues2[2] = { { .color = { { UNormFlt, UNormFlt, UNormFlt, 1.0F } } }, { .color = { { UNormFlt, UNormFlt, UNormFlt, 1.0F } } } };

  // {
  //   .color        = { UNormFlt, UNormFlt, UNormFlt, 1.0F },
  //   .depthStencil = { 0.0F, static_cast<uint32_t>( 1.0F ) },
  // },

  static VkRenderPassBeginInfo renderPassInfo = {
    .sType           = ( VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO ),
    .renderPass      = ( renderPass ),
    .renderArea      = renderArea,
    .clearValueCount = 2,
    .pClearValues    = clearValues2,
  };
  static uint8_t i = 0;
  vkMapMemory( Queues::device, UniformBufferObject::uniformBuffersMemory, 0, UniformBufferObject::Sized, 0, &BuffersX::data );
  static constexpr VkDeviceSize offsets[] = { 0 };
  m4.loadAligned( &viewproj );  // NoS ure on best order............................................................->
  for ( const VkCommandBuffer & commandBuffer : commandBuffers )
  {
    VkUtilsXBase::clPI<PFN_vkBeginCommandBuffer>( commandBuffer, "vkBeginCommandBuffer", &beginInfo1 );

    renderPassInfo.framebuffer = ( SwapChainSupportDetails::swapChainFramebuffers[i] );

    vkCmdBeginRenderPass( commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE );

    vkCmdBindPipeline( commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline );
    vkCmdBindVertexBuffers( commandBuffer, 0, 1, &BuffersX::vertexBuffer, offsets );
    vkCmdBindIndexBuffer( commandBuffer, BuffersX::indexBuffer, 0, VK_INDEX_TYPE_UINT16 );

    vkCmdBindDescriptorSets( commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vkLayout, 0, 1, &UniformBufferObject::descriptorSets, 0, nullptr );

    __builtin_memcpy_inline( ( BuffersX::data ), ( &m4 ), sizeof( mat4x ) );

    vkCmdDrawIndexed( commandBuffer, ( ( BuffersX::sizedsfIdx ) / 2 ), 1, 0, 0, 0 );

    vkCmdEndRenderPass( commandBuffer );
    VkUtilsXBase::clP<PFN_vkEndCommandBuffer>( commandBuffer, "vkEndCommandBuffer" );
    i++;
  }
}
inline void BuffersX::setupBuffers()
{
  auto x1 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT );
  auto p1 = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( p1, vertexBuffer, x1, sizedsf, vertexBufferMemory );

  VkBufferUsageFlagBits x2 = { VK_BUFFER_USAGE_TRANSFER_SRC_BIT };
  constexpr auto        p  = static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT );
  createSetBuffer( p, Bufferstaging, x2, sizedsf, stagingBufferMemory );

  auto x3 = static_cast<VkBufferUsageFlagBits>( VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT );
  createSetBuffer( VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, x3, sizedsfIdx, indexBufferMemory );

  vkMapMemory( Queues::device, stagingBufferMemory, 0, sizedsf, 0, &data );
  {
    memcpy( data, vectBuf, sizedsf );
  }

  BuffersX::copyBuffer( vertexBuffer, sizedsf );

  {
    memcpy( data, idxBuf, sizedsfIdx );
  }
  vkUnmapMemory( Queues::device, stagingBufferMemory );
  copyBuffer( indexBuffer, sizedsfIdx );
}

inline void BuffersX::createSetBuffer(
  VkMemoryPropertyFlagBits properties, VkBuffer & currentBuffer, VkBufferUsageFlagBits usage, size_t sized, VkDeviceMemory & vertexBufferMemory )
{
  const VkBufferCreateInfo allocateInfo = {
    .sType       = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
    .pNext       = nullptr,
    .size        = sized,
    .usage       = usage,
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
  };

  VkUtilsXBase::clPPPI3<PFN_vkCreateBuffer>( &allocateInfo, "vkCreateBuffer", &currentBuffer );

  VkMemoryRequirements memRequirements;
  vkGetBufferMemoryRequirements( Queues::device, currentBuffer, &memRequirements );

  VkMemoryAllocateInfo allocateInfo1 = {
    .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
    .pNext           = nullptr,
    .allocationSize  = memRequirements.size,
    .memoryTypeIndex = findMemoryType( Queues::physicalDevice, memRequirements.memoryTypeBits, properties ),
  };
  //
  VkUtilsXBase::clPPPI3<PFN_vkAllocateMemory>( &allocateInfo1, "vkAllocateMemory", &vertexBufferMemory );

  VkUtilsXBase::checkCall( vkBindBufferMemory( Queues::device, currentBuffer, vertexBufferMemory, 0 ) );
}

inline uint32_t BuffersX::findMemoryType( VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlagBits properties )
{
  VkPhysicalDeviceMemoryProperties memProperties = {};
  vkGetPhysicalDeviceMemoryProperties( physicalDevice, &memProperties );
  for ( uint32_t i = 0; i < memProperties.memoryTypeCount; i++ )
  {
    if ( ( typeFilter & ( 1U << i ) ) != 0 && ( memProperties.memoryTypes[i].propertyFlags & properties ) == properties )
    {
      return i;
    }
  }

  throw std::runtime_error( "Failed to find suitable memory type" );
}

inline void BuffersX::createVkEvents()
{
  VkEventCreateInfo vkEventCreateInfo = {};
  vkEventCreateInfo.sType             = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
  vkEventCreateInfo.pNext             = nullptr;

  VkUtilsXBase::clPPPI3<PFN_vkCreateEvent>( &vkEventCreateInfo, "vkCreateEvent", &vkEvent );
}

inline void BuffersX::copyBuffer( VkBuffer & dst, const size_t sized )
{
  Queues::beginSingleTimeCommands();
  const VkBufferCopy vkBufferCopy{
    .srcOffset = 0,
    .dstOffset = 0,
    .size      = sized,
  };
  vkCmdCopyBuffer( queues.commandBuffer, Bufferstaging, dst, 1, &vkBufferCopy );
  Queues::endSingleTimeCommands();
}