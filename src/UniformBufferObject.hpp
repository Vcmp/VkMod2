#pragma once
#define GLM_FORCE_LEFT_HANDED
#include "Buffers.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "mat4x.hpp"

inline namespace
{
  static const glm::mat4 pers =
    glm::perspectiveLH_ZO( glm::radians( 45.0f ) * -1, width / static_cast<float>( height ), 1.7f, 90.0f );
  static const glm::mat4 look =
    glm::lookAtLH( glm::vec3( 2.0f, 2.0f, 2.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3( 0.0f, 0.0f, 1.0f ) );

  static const glm::mat4 viewproj = pers * look;
  static const mat4x     viewproj2( &viewproj );

};  // namespace

// static inline struct alignas( ( 64 ) ) UBO
// {
//   glm::mat4 model = viewproj;
//   // mat4 Trans;
// } ubo;
struct UniformBufferObject
{
  static constinit const size_t       Sized = ( sizeof( viewproj ) );
  static inline VkDescriptorSet       descriptorSets;
  static inline VkDescriptorSetLayout descriptorSetLayout;
  static inline VkDescriptorPool      descriptorPool;
  static inline VkImageView           textureImageView;
  static inline VkBuffer              uniformBuffers;
  static inline VkDeviceMemory        uniformBuffersMemory;

  static constexpr void createDescriptorSetLayout()
  {
    // m5.loadAligned( &viewproj2 );

    {
      constexpr VkDescriptorSetLayoutBinding bindings = {
        .binding         = 0,
        .descriptorType  = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1,
        .stageFlags      = VK_SHADER_STAGE_VERTEX_BIT,
        /* { .binding = 1,
          .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT} */
      };
      // samplerLayoutBinding

      const VkDescriptorSetLayoutCreateInfo a{
        .sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings    = &bindings,

      };
      VkUtilsXBase::clPPPI3<PFN_vkCreateDescriptorSetLayout>(
        &a, "vkCreateDescriptorSetLayout", &UniformBufferObject::descriptorSetLayout );
      // return MemSysm.doPointerAllocSafe(a,
      // device.getCapabilities().vkCreateDescriptorSetLayout);
    }
  }

  static void createUniformBuffers()
  {
    for ( int i = 0; i < 1; i++ )
    {
      BuffersX::createSetBuffer( static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                                                        VK_MEMORY_PROPERTY_HOST_COHERENT_BIT ),
                                 uniformBuffers,
                                 VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                 Sized,
                                 uniformBuffersMemory );
    }
  }

  static void createDescriptorPool()
  {
    {
      static constexpr VkDescriptorPoolSize poolSize{

        /* uniformBufferPoolSize */
        .type            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .descriptorCount = 1

      };
      //                        .type(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
      //                        .descriptorCount(PipeLine.swapChainImages.length);

      static constexpr VkDescriptorPoolCreateInfo poolCreateInfo{ .sType =
                                                                    VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                                                                  .pNext         = nullptr,
                                                                  .maxSets       = 1,
                                                                  .poolSizeCount = 1,
                                                                  .pPoolSizes    = &poolSize };
      ( vkCreateDescriptorPool( Queues::device, &poolCreateInfo, nullptr, &descriptorPool ) );
      //               descriptorPool=aLong[0];
    }
  }

  static VkSampler createTextureSampler()
  {
    //                    System.out.println(properties.limits());
    constexpr VkSamplerCreateInfo samplerInfo{
      .sType            = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
      .magFilter        = VK_FILTER_NEAREST,
      .minFilter        = VK_FILTER_NEAREST,
      .mipmapMode       = VK_SAMPLER_MIPMAP_MODE_NEAREST,
      .addressModeU     = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeV     = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeW     = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .mipLodBias       = 0,
      .anisotropyEnable = false,
      //                    .maxAnisotropy=properties.limits=).maxSamplerAnisotropy=),
      .compareEnable           = false,
      .compareOp               = VK_COMPARE_OP_ALWAYS,
      .minLod                  = 0,
      .maxLod                  = 0,
      .borderColor             = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
      .unnormalizedCoordinates = false,
    };
    VkSampler sampler = nullptr;
    VkUtilsXBase::clPPPI3<PFN_vkCreateSampler>( &samplerInfo, "vkCreateSampler", &sampler );
    return sampler;
    // nmemFree(samplerInfo.address());
  }

  static void createDescriptorSets()
  {
    {
      // VkDescriptorSetLayout layouts[Frames];
      //  std::vector<VkDescriptorSetLayout> layouts(1, descriptorSetLayout);

      const VkDescriptorSetAllocateInfo allocInfo{ .sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                                                   .pNext              = nullptr,
                                                   .descriptorPool     = descriptorPool,
                                                   .descriptorSetCount = 1,
                                                   .pSetLayouts        = &descriptorSetLayout };

      vkAllocateDescriptorSets( Queues::device, &allocInfo, &descriptorSets );

      {
        VkDescriptorBufferInfo bufferInfo{ .buffer = uniformBuffers, .offset = 0, .range = ( Sized ) };

        // const VkDescriptorImageInfo imageInfo{
        //         .sampler=createTextureSampler(),
        //         .imageView=textureImageView,
        //         .imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        // };

        VkWriteDescriptorSet descriptorWrites{

          .sType           = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
          .dstSet          = descriptorSets,
          .dstBinding      = 0,
          .dstArrayElement = 0,
          .descriptorCount = 1,
          .descriptorType  = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
          .pBufferInfo     = &bufferInfo,

          /*  */
        };
        vkUpdateDescriptorSets( Queues::device, 1, &descriptorWrites, 0, nullptr );
      }
    }
  }
};