
#pragma once

#include "Queues.hpp"
#include "test.inl"

struct ShaderSPIRVUtils
{
  /*   const VkShaderModule frags;
    const VkShaderModule verts;
    constexpr ShaderSPIRVUtils() : frags( compileShaderFile() ), verts( compileShaderFile1() ){};
   */
  static constexpr VkShaderModule compileShaderFile();
  static constexpr VkShaderModule compileShaderFile1();
/*   ~ShaderSPIRVUtils()
  {
    vkDestroyShaderModule( Queues::device, frags, VK_NULL_HANDLE );
    vkDestroyShaderModule( Queues::device, verts, VK_NULL_HANDLE );
  }
 */};  // namespace ShaderSPIRVUtils

inline constexpr VkShaderModule ShaderSPIRVUtils::compileShaderFile()
{
  // auto axl = doRead( shaderNamePath1 );
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
