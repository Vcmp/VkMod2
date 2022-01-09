
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "src/Queues.hpp"

#include <stdint.h>



#include <stdio.h>
#include <vulkan/vulkan_core.h>
struct ShaderSPIRVUtils
{
    char shaderNamePath;
    
    enum ShaderKind
    {
        VERTEX_SHADER=0,
        FRAGMENT_SHADER=1
    };
    static const char compileShaderFile(const char*,VkShaderModule*);
    static const VkShaderModule createShaderModule(const char*, size_t);
} ;
//typedef ShaderSPIRVUtils SPRIV;


inline const char ShaderSPIRVUtils::compileShaderFile(const char* shaderNamePath1, VkShaderModule* a)
{
   FILE* file = fopen(shaderNamePath1, "rb");
    if(!file)
    {
        std::runtime_error("Fail:Bad or No ShaderFile!");
    }
   size_t size = ftell(file);
   rewind(file);

   if(size==0)
    {
        std::runtime_error("Fail:Bad or No ShaderFile!");
    }

   char x[size];
    fread(x, 1, size, file);
    fclose(file);
   return *x;
}

inline const VkShaderModule ShaderSPIRVUtils::createShaderModule(const char* shadr, size_t ax)
{
    VkShaderModuleCreateInfo a;
    {
        a.codeSize=ax,
        a.pCode=reinterpret_cast<const uint32_t*>(shadr);
        a.sType=VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        a.pNext=nullptr;
        a.flags=0;
    }
    VkShaderModule axx;
    vkCreateShaderModule(device, &a, nullptr, &axx);
    return axx;
}