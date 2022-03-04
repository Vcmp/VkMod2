
#pragma once

#include "Queues.hpp"
#include "test.hpp"

#include <cstdint>

struct ShaderSPIRVUtils
{
  const VkShaderModule frags;
  const VkShaderModule verts;
  // constexpr ShaderSPIRVUtils() : frags( compileShaderFile() ), verts( compileShaderFile1() ){};
  static constexpr VkShaderModule compileShaderFile();
  static constexpr VkShaderModule compileShaderFile1();
  ~ShaderSPIRVUtils()
  {
    vkDestroyShaderModule( Queues::device, frags, VK_NULL_HANDLE );
    vkDestroyShaderModule( Queues::device, verts, VK_NULL_HANDLE );
  }
};  // namespace ShaderSPIRVUtils

inline constexpr VkShaderModule ShaderSPIRVUtils::compileShaderFile()
{
  // auto axl = doRead( shaderNamePath1 );
  VkShaderModule           axx   = {};
  VkShaderModuleCreateInfo VsMCI = {};

  VsMCI.codeSize = vert.size();
  VsMCI.pCode    = (uint32_t *)( vert.data() );
  VsMCI.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  VsMCI.pNext    = VK_NULL_HANDLE;

  VkUtilsXBase::clPPPI3<PFN_vkCreateShaderModule>( &VsMCI, "vkCreateShaderModule", &axx );
  return axx;
}
inline constexpr VkShaderModule ShaderSPIRVUtils::compileShaderFile1()
{
  // auto axl = doRead( shaderNamePath1 );

  VkShaderModule           axx   = {};
  VkShaderModuleCreateInfo VsMCI = {};

  VsMCI.codeSize = frag.size();
  VsMCI.pCode    = (uint32_t *)( frag.data() );
  VsMCI.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  VsMCI.pNext    = VK_NULL_HANDLE;

  VkUtilsXBase::clPPPI3<PFN_vkCreateShaderModule>( &VsMCI, "vkCreateShaderModule", &axx );
  const VkShaderModule axx2 = axx;
  return axx2;
}
