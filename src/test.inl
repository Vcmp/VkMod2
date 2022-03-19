#pragma once
#include <array>
#include <cinttypes>
#include "Queues.hpp"
#include "21_shader_ubo.frag.txt.inl"
#include "21_shader_ubo.vert.txt.inl"



static struct ShaderSPIRVUtils
{


//ShaderSPIRVUtils(): FragMod(Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &VsMCI2, "vkCreateShaderModule" )), VertMod(Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &VsMCI, "vkCreateShaderModule" )) {};

 const VkShaderModuleCreateInfo VsMCI = {

    .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .codeSize = sizeof(vert),
    .pCode    = vert,
  };

  const VkShaderModuleCreateInfo VsMCI2 = {

    .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .codeSize = sizeof(frag),
    .pCode    = frag,
  };
    VkShaderModule compileShaderFile();
    VkShaderModule compileShaderFile1();
} SPV;
