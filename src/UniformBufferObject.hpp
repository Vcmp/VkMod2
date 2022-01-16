#pragma once

#include "VkUtilsXBase.hpp"



inline namespace UniformBufferObject
{
    extern inline const void createDescriptorSetLayout();
    static VkDescriptorSetLayout descriptorSetLayout;
};

inline const void UniformBufferObject::createDescriptorSetLayout()
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
            vkCreateDescriptorSetLayout(device, &a, VK_NULL_HANDLE, &UniformBufferObject::descriptorSetLayout);
            //return MemSysm.doPointerAllocSafe(a, device.getCapabilities().vkCreateDescriptorSetLayout);
        }
}