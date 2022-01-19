
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "VkUtilsXBase.hpp"
#include <fcntl.h>
#include <io.h>

inline namespace ShaderSPIRVUtils {
// char shaderNamePath;

// enum ShaderKind
// {
//     VERTEX_SHADER=0,
//     FRAGMENT_SHADER=1
// };
inline const void compileShaderFile(const char *, VkShaderModule &);
// extern constexpr VkShaderModule createShaderModule(VkDevice, const char*,
// size_t);
}; // namespace ShaderSPIRVUtils
// typedef ShaderSPIRVUtils SPRIV;

inline const std::vector<char> doRead(const char *shaderNamePath1) {
  const int fhndl =
      _sopen(shaderNamePath1, _O_RDONLY | _O_BINARY | _O_SEQUENTIAL, 0x40,
             0x0100 | 0x0080);
  // if(!file)
  // {
  //     std::runtime_error("Fail:Bad or No ShaderFile!");
  // }
  _lseek(fhndl, 0, SEEK_END);
  const size_t size = _tell(fhndl);
  _lseek(fhndl, 0, SEEK_END);

  std::vector<char> x(size);

  std::cout << size << "\n";
  if (_eof(fhndl) == -1) {

    throw std::runtime_error("Fail:Bad or No ShaderFile!");
  }
  _read(fhndl, x.data(), size);
  std::cout << x.size() << "\n";
  // _flushall();
  _close(fhndl);
  return x;
}

inline const void
ShaderSPIRVUtils::compileShaderFile(const char *shaderNamePath1,
                                    VkShaderModule &axx) {

  auto axl = doRead(shaderNamePath1);
  // axl[axl.size()-1]=(0x07230203);

  // for(uint32_t a=0;a<axl.size();a++)
  //     std::cout<<axl[a];

  VkShaderModuleCreateInfo VsMCI = {};

  VsMCI.codeSize = axl.size();
  VsMCI.pCode = reinterpret_cast<const uint32_t *>(axl.data());
  VsMCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  VsMCI.pNext = VK_NULL_HANDLE;

  vkCreateShaderModule(device, &VsMCI, nullptr, &axx);
  // clPPPI(&VsMCI, "vkCreateShaderModule", &axx);
  // if (a!=VK_SUCCESS)
  // {
  //     std::cout <<a<<"\n";
  //     throw std::runtime_error("Fail: Bad Shader Module");
  // }
  // return axx;
}
