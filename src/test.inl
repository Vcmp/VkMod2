
#include <array>
#include <cinttypes>
// #include "VkUtilsXBase.hpp"
#include "21_shader_ubo.frag.inl"
#include "21_shader_ubo.vert.inl"



static constexpr struct ShaderSPIRVUtils
{


//ShaderSPIRVUtils(): FragMod(Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &VsMCI2, "vkCreateShaderModule" )), VertMod(Queues::clPPPI3A<VkShaderModule, PFN_vkCreateShaderModule>( &VsMCI, "vkCreateShaderModule" )) {};

 static constexpr VkShaderModuleCreateInfo VsMCI = {

    .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .codeSize = sizeof(vert),
    .pCode    = vert,
  };

  static constexpr VkShaderModuleCreateInfo VsMCI2 = {

    .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
    .pNext    = VK_NULL_HANDLE,
    .codeSize = sizeof(frag),
    .pCode    = frag,
  };
  VkShaderModule compileShaderFile(const VkShaderModuleCreateInfo& __restrict__);
}  SPV;
