
#pragma once

#include "Queues.hpp"
#include "test.inl"

struct ShaderSPIRVUtils
{
  static constexpr VkShaderModule compileShaderFile();
  static constexpr VkShaderModule compileShaderFile1();
};

inline constexpr VkShaderModule ShaderSPIRVUtils::compileShaderFile()
{
  const VkShaderModuleCreateInfo VsMCI = {

    .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .codeSize = vert.size(),
    .pCode    = (uint32_t *)( vert.data() ),
  };
  return Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &VsMCI, "vkCreateShaderModule" );
}
inline constexpr VkShaderModule ShaderSPIRVUtils::compileShaderFile1()
{
  // auto axl = doRead( shaderNamePath1 );

  VkShaderModuleCreateInfo VsMCI = {

    .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .codeSize = frag.size(),
    .pCode    = (uint32_t *)( frag.data() ),
  };
  return Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &VsMCI, "vkCreateShaderModule" );
}
