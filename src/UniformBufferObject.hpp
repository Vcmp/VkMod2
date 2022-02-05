#pragma once
#define GLM_FORCE_LEFT_HANDED 
#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Buffers.hpp"


   const  glm::mat4 viewproj = glm::perspective(glm::radians(45.0f)*-1, pstrct.width/ (float)pstrct.height, 0.7f, 90.0f)*glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
static inline struct alignas((128)) UBO{
     glm::mat4 model=viewproj;
    //mat4 Trans;
} inline ubo;
static constexpr struct UniformBufferObject 
{

 

static constexpr size_t Sized=(sizeof(ubo));
static inline VkDescriptorSet descriptorSets;
static inline VkDescriptorSetLayout descriptorSetLayout;
static inline VkDescriptorPool descriptorPool;
static inline VkImageView textureImageView;
static inline VkBuffer uniformBuffers;
static inline VkDeviceMemory uniformBuffersMemory;


static void createDescriptorSetLayout() 
{
  {
    static constexpr VkDescriptorSetLayoutBinding bindings = {
        .binding = 0,
          .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
        /* { .binding = 1,
          .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
          .descriptorCount = 1,
          .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT} */
      };
    // samplerLayoutBinding

    static constexpr VkDescriptorSetLayoutCreateInfo a{
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = 1,
        .pBindings = &bindings,

    };
    pstrct.clPPPI(&a, "vkCreateDescriptorSetLayout",
           &UniformBufferObject::descriptorSetLayout);
    // return MemSysm.doPointerAllocSafe(a,
    // device.getCapabilities().vkCreateDescriptorSetLayout);
  }
}

static void createUniformBuffers()
{
   for (int i = 0; i < 1; i++) {

        BuffersX::createSetBuffer((VkMemoryPropertyFlagBits)(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT), uniformBuffers, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, Sized, uniformBuffersMemory);
           
   }
}


static void createDescriptorPool()
    {
        {
            static constexpr VkDescriptorPoolSize poolSize
            {
              
              /* uniformBufferPoolSize */ 
                  .type=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                    .descriptorCount=1

              
            };
//                        .type(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
//                        .descriptorCount(PipeLine.swapChainImages.length);
          
            static constexpr VkDescriptorPoolCreateInfo poolCreateInfo{
            .sType=VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
                    .pNext=nullptr,
                    .maxSets=1,
                    .poolSizeCount=1,
                    .pPoolSizes=&poolSize
            };
            (vkCreateDescriptorPool(pstrct.device, &poolCreateInfo, nullptr, &descriptorPool));
//               descriptorPool=aLong[0];
        }
    }

    static VkSampler createTextureSampler()
    {
        //                    System.out.println(properties.limits());
        constexpr VkSamplerCreateInfo samplerInfo{
                .sType=VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
                .magFilter=VK_FILTER_NEAREST,
                .minFilter=VK_FILTER_NEAREST,
                .mipmapMode=VK_SAMPLER_MIPMAP_MODE_NEAREST,
                .addressModeU=VK_SAMPLER_ADDRESS_MODE_REPEAT,
                .addressModeV=VK_SAMPLER_ADDRESS_MODE_REPEAT,
                .addressModeW=VK_SAMPLER_ADDRESS_MODE_REPEAT,
                .mipLodBias=0,
                .anisotropyEnable=false,
                //                    .maxAnisotropy=properties.limits=).maxSamplerAnisotropy=),
                .compareEnable=false,
                .compareOp=VK_COMPARE_OP_ALWAYS,
                .minLod=0,
                .maxLod=0,
                .borderColor=VK_BORDER_COLOR_INT_OPAQUE_BLACK,
                .unnormalizedCoordinates=false,
        };
        VkSampler sampler = nullptr;
     pstrct.clPPPI(&samplerInfo, "vkCreateSampler", &sampler);
     return sampler;
        //nmemFree(samplerInfo.address());
    }

    static void createDescriptorSets()
    {
        {
            // VkDescriptorSetLayout layouts[Frames];
          //  std::vector<VkDescriptorSetLayout> layouts(1, descriptorSetLayout);

            const VkDescriptorSetAllocateInfo allocInfo{
                .sType=VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
                .pNext=nullptr,
                .descriptorPool=descriptorPool,
                .descriptorSetCount=1,
                    .pSetLayouts=&descriptorSetLayout
            };

            vkAllocateDescriptorSets(pstrct.device, &allocInfo, &descriptorSets);
    
      {
            VkDescriptorBufferInfo bufferInfo{
                    .buffer=uniformBuffers,
                    .offset=0,
                    .range=(Sized)
            };

            // const VkDescriptorImageInfo imageInfo{
            //         .sampler=createTextureSampler(),
            //         .imageView=textureImageView,
            //         .imageLayout=VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            // };

            VkWriteDescriptorSet descriptorWrites{

                  
                       .sType=VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                      .dstSet=descriptorSets,
                      .dstBinding=0,
                            .dstArrayElement=0,
                            .descriptorCount=1,
                            .descriptorType=VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                            .pBufferInfo=&bufferInfo,
                 

                  /*  */
            };
                vkUpdateDescriptorSets(pstrct.device, 1, &descriptorWrites, 0, nullptr);

      }
        }}

            
    


} inline ubos;