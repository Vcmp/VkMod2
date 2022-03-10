#pragma once
#include "VkUtils2.ixx"
#include "renderer2.hpp"

#include <pthread.h>
#include <unistd.h>

#include "Buffers.hpp"

inline constexpr void UniformBufferObject::createDescriptorSetLayout()
  {
    // m5.loadAligned( &viewproj2 );

    {
      constexpr VkDescriptorSetLayoutBinding bindings = {
        .binding = 0, .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, .descriptorCount = 1, .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
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
      VkUtilsXBase::clPPPI3<PFN_vkCreateDescriptorSetLayout>( &a, "vkCreateDescriptorSetLayout", &UniformBufferObject::descriptorSetLayout );
    }
  }

  inline void UniformBufferObject::createUniformBuffers()
  {
    for ( int i = 0; i < 1; i++ )
    {
      BuffersX::createSetBuffer( static_cast<VkMemoryPropertyFlagBits>( VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT ),
                                 UniformBufferObject::uniformBuffers,
                                 VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                                 Sized,
                                 uniformBuffersMemory );
    }
  }

  inline void UniformBufferObject::createDescriptorPool()
  {
    {
      static constexpr VkDescriptorPoolSize poolSize{

        .type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, .descriptorCount = 1

      };

      static constexpr VkDescriptorPoolCreateInfo poolCreateInfo{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, .pNext = nullptr, .maxSets = 1, .poolSizeCount = 1, .pPoolSizes = &poolSize
      };
      ( vkCreateDescriptorPool( Queues::device, &poolCreateInfo, nullptr, &descriptorPool ) );
    }
  }

  inline VkSampler createTextureSampler()
  {
    constexpr VkSamplerCreateInfo samplerInfo{
      .sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
      .magFilter               = VK_FILTER_NEAREST,
      .minFilter               = VK_FILTER_NEAREST,
      .mipmapMode              = VK_SAMPLER_MIPMAP_MODE_NEAREST,
      .addressModeU            = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeV            = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .addressModeW            = VK_SAMPLER_ADDRESS_MODE_REPEAT,
      .mipLodBias              = 0,
      .anisotropyEnable        = false,
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

  inline void UniformBufferObject::createDescriptorSets()
  {
    {
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