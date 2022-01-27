
#pragma once

#include "VkUtilsXBase.hpp"
#include <fstream>

inline namespace ShaderSPIRVUtils {
// char shaderNamePath;

// enum ShaderKind
// {
//     VERTEX_SHADER=0,
//     FRAGMENT_SHADER=1
// };
static VkShaderModule compileShaderFile(const char *);
// extern constexpr VkShaderModule createShaderModule(VkDevice, const char*,
// size_t);
}; // namespace ShaderSPIRVUtils
   // typedef ShaderSPIRVUtils SPRIV;

inline std::vector<char> doRead(const char *shaderNamePath1) {
  std::ifstream file(shaderNamePath1, std::ios::ate | std::ios::binary);

  if (!file.is_open()) {
    throw std::runtime_error("failed to open file!");
  }
  size_t fileSize = (size_t)file.tellg();
  std::vector<char> buffer(fileSize);
  file.seekg(0);
  file.read(buffer.data(), fileSize);
  file.close();

  return buffer;
}

inline VkShaderModule
ShaderSPIRVUtils::compileShaderFile(const char *shaderNamePath1) {

  auto axl = doRead(shaderNamePath1);
  // axl[axl.size()-1]=(0x07230203);

  // for(uint32_t a=0;a<axl.size();a++)
  //     std::cout<<axl[a];
  VkShaderModule axx = {};
  VkShaderModuleCreateInfo VsMCI = {};

  VsMCI.codeSize = axl.size();
  VsMCI.pCode = reinterpret_cast<const uint32_t *>(axl.data());
  VsMCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  VsMCI.pNext = VK_NULL_HANDLE;

  clPPPI(&VsMCI, "vkCreateShaderModule", &axx);
  const VkShaderModule axx2 = axx;
  return axx2;
  // clPPPI(&VsMCI, "vkCreateShaderModule", &axx);
  // if (a!=VK_SUCCESS)
  // {
  //     std::cout <<a<<"\n";
  //     throw std::runtime_error("Fail: Bad Shader Module");
  // }
  // return axx;
}
