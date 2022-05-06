#pragma once
#include "Buffers.hpp"
#include "test.inl"
#include "mat4x.hpp"


static constexpr struct PipelineX
{
  static void recCmdBuffers();
  static void recCmdBuffer(int);
  static void createGraphicsPipelineLayout();
  static void createCommandBuffers();
  static void createRenderPasses();
  VkFormat    findDepthFormat();

  static constexpr uint8_t OFFSETOF_COLOR = 3 * sizeof( float );
  static constexpr uint8_t OFFSET_POS     = 0;

  static constexpr uint8_t                     OFFSETOF_TEXTCOORDS = ( 3 + 3 ) * sizeof( float );
  static constexpr float                   UNormFlt            = 0.0F;
  static constinit inline VkPipelineLayout vkLayout;
  static constinit inline VkPipeline       graphicsPipeline;
  static constinit inline VkCommandBuffer  commandBuffers[Frames];
} __attribute__((aligned(64))) PX;


static constexpr struct UniformBufferObject
{
  static constexpr     uint8_t           Sized = ( sizeof( viewproj ) );
  static constinit inline VkDescriptorSet       descriptorSets;
  static constinit inline VkDescriptorSetLayout descriptorSetLayout;
  static constinit inline VkDescriptorPool      descriptorPool;
  static constinit inline VkImageView           textureImageView;
  static constinit inline VkBuffer              uniformBuffers;
  static constinit inline VkDeviceMemory        uniformBuffersMemory;

  static constexpr void createDescriptorSetLayout();
static void createUniformBuffers();
static void createDescriptorPool();
static void createDescriptorSets();
} UBO;