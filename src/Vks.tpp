#pragma once

#include <iostream>
#include <volk.h>


constexpr uint16_t width = 1280;
constexpr uint16_t height = 720;
constexpr uint8_t Frames = 8;

// constexpr  auto ta =LoadLibraryA("vulkan-1.dll");

// constexpr auto tst = (PFN_vkGetInstanceProcAddr)(void(*)())vkGetInstanceProcAddr(VkInit::VKI.instance, "vkCreateShaderModule");

static union Vks 
{
    static inline VkDevice Device;
    template<typename type, typename ... fcn>
    [[nodiscard]] static constexpr auto doPointerAlloc5(auto* __restrict__ strct, auto* hndle) noexcept -> type
    {
        type pHndl; 
        hndle(Device, strct, nullptr, &pHndl);
        return pHndl;
    }

    template<typename type>
    constexpr type doPointerAllocX(auto* strct) const
    {
        type pHndl = nullptr; 
        vkCreateGraphicsPipelines(Device, nullptr, 1, strct, nullptr, &pHndl);
        return pHndl;
    }
    template<typename type>
    constexpr type doPointerAllocX2(auto* strct) const
    {
        type pHndl = nullptr; 
        vkCreateShaderModule(Device, strct, nullptr, &pHndl);
        return pHndl;
    }
    
    
 } Vks;