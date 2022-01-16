
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdexcept>



#include <stdint.h>



#include <fcntl.h>

#include <io.h>
#include <vulkan/vulkan_core.h>
inline namespace ShaderSPIRVUtils
{
    char shaderNamePath;
    
    // enum ShaderKind
    // {
    //     VERTEX_SHADER=0,
    //     FRAGMENT_SHADER=1
    // };
    static const VkShaderModule compileShaderFile(const VkDevice&, const char*);
    static const VkShaderModule createShaderModule(VkDevice, const char*, size_t);
} ;
//typedef ShaderSPIRVUtils SPRIV;
inline namespace{
inline const VkShaderModuleCreateInfo doRead(const char* shaderNamePath1)
{
    const int fhndl=_sopen(shaderNamePath1, _O_RDONLY | _O_BINARY | _O_SEQUENTIAL, 0x20, 0x0100);
    // if(!file)
    // {
    //     std::runtime_error("Fail:Bad or No ShaderFile!");
    // }
     _lseek(fhndl, 0, SEEK_END);
   const size_t size = _tell(fhndl);
   _lseek(fhndl, 0, SEEK_END);

const char* x[size];

std::cout<< size << "\n";
   if(size<=0||size>=0xFFFF)
    {
      
       throw std::runtime_error("Fail:Bad or No ShaderFile!");
    }
     _read(fhndl, x, size);
    _flushall();
    _close(fhndl);

    VkShaderModuleCreateInfo VsMCI={};
    {
        VsMCI.codeSize=size,
        VsMCI.pCode=reinterpret_cast<const uint32_t*>(x);
        VsMCI.sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        VsMCI.pNext=nullptr;
    }
    return VsMCI;
}
}

inline const VkShaderModule ShaderSPIRVUtils::compileShaderFile(const VkDevice &device, const char* shaderNamePath1)
{
   
   
    
    VkShaderModule axx;
    VkShaderModuleCreateInfo axl =doRead(shaderNamePath1);
    if (vkCreateShaderModule(device, &axl, nullptr, &axx)!=VK_SUCCESS)
        throw std::runtime_error("Fail: Bad Shader Module");
    return axx;
}

