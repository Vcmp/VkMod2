#include "Buffers.hpp"
#include "ShaderSPIRVUtils.hpp"
#include "mat4x.hpp"

#include <iostream>

static constexpr struct PipelineX
{
  static void createGraphicsPipelineLayout();
  static void createCommandBuffers();
  static void createRenderPasses();
  VkFormat    findDepthFormat();

  static constexpr int OFFSETOF_COLOR = 3 * sizeof( float );
  static constexpr int OFFSET_POS     = 0;

  static constexpr int                     OFFSETOF_TEXTCOORDS = ( 3 + 3 ) * sizeof( float );
  static constexpr float                   UNormFlt            = 0.0F;
  static constinit inline VkPipelineLayout vkLayout;
  static constinit inline VkPipeline       graphicsPipeline;
  static constinit inline VkCommandBuffer  commandBuffers[Frames];
} PX;
