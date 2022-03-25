#include "Queues.hpp"
#include "test.inl"

inline namespace 
{
 VkShaderModule FragMod;
 VkShaderModule VertMod;
}

 VkShaderModule ShaderSPIRVUtils::compileShaderFile(const VkShaderModuleCreateInfo& __restrict__ tmp)
{
  // const VkShaderModuleCreateInfo VsMCI = {

  //   .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
  //   .pNext    = VK_NULL_HANDLE,
  //   .codeSize = vert.size(),
  //   .pCode    = (uint32_t *)( vert.data() ),
  // };
  return Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &tmp, "vkCreateShaderModule" );
}
