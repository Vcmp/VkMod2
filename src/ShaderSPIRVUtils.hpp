
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "Pipeline.hpp"
#include <fcntl.h>
#include <io.h>

inline namespace ShaderSPIRVUtils
{
    // char shaderNamePath;
    
    // enum ShaderKind
    // {
    //     VERTEX_SHADER=0,
    //     FRAGMENT_SHADER=1
    // };
    inline constexpr VkShaderModule compileShaderFile(const VkDevice&, const char*);
    // extern constexpr VkShaderModule createShaderModule(VkDevice, const char*, size_t);
} ;
//typedef ShaderSPIRVUtils SPRIV;

inline extern const VkShaderModuleCreateInfo doRead(const char* shaderNamePath1)
{
    const int fhndl=_sopen(shaderNamePath1, _O_RDONLY | _O_BINARY | _O_SEQUENTIAL, 0x20, 0x0100);
    // if(!file)
    // {
    //     std::runtime_error("Fail:Bad or No ShaderFile!");
    // }
     _lseek(fhndl, 0, SEEK_END);
   const size_t size = _tell(fhndl);
   _lseek(fhndl, 0, SEEK_END);

std::vector<char> x(size);

std::cout<< size << "\n";
   if(_eof(fhndl)==-1)
    {
      
       throw std::runtime_error("Fail:Bad or No ShaderFile!");
    }
     _read(fhndl, x.data(), size);
     std::cout<< x.size() << "\n";
    _flushall();
    _close(fhndl);

    VkShaderModuleCreateInfo VsMCI={};
    {
        VsMCI.codeSize=size,
        VsMCI.pCode=reinterpret_cast<const uint32_t*>(x.data());
        VsMCI.sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        VsMCI.pNext=VK_NULL_HANDLE ;
    }
    return VsMCI;
}


inline constexpr VkShaderModule ShaderSPIRVUtils::compileShaderFile(const VkDevice &device, const char* shaderNamePath1)
{
   
   
    
    VkShaderModule axx;
    VkShaderModuleCreateInfo axl =doRead(shaderNamePath1);
    VkResult a=vkCreateShaderModule(device, &axl, nullptr, &axx);
    if (a!=VK_SUCCESS)
    {
        std::cout <<a<<"\n";
        throw std::runtime_error("Fail: Bad Shader Module");
    }
    return axx;
}

