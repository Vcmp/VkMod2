#pragma once
#include "VKI.hpp"
#include <libloaderapi.h>



constexpr WINBASEAPI HMODULE WINAPI LoadLibraryA1 (LPCSTR lpLibFileName);

// constexpr  auto ta =LoadLibraryA("vulkan-1.dll");

// constexpr auto tst = (PFN_vkGetInstanceProcAddr)(void(*)())vkGetInstanceProcAddr(VkInit::VKI.instance, "vkCreateShaderModule");


inline namespace Vks 
{

    
    //   typedef VkResult ( *callPPPPI )( const void* device, const void * strct, const void *VkAllocationCallbacks, const void *hndle);
    template<typename type, typename handle>
    constexpr auto doPointerAlloc(VkDevice device, auto* strct, type* hndle, handle pHndl) -> type
    {
        (handle(pHndl))(device, strct ,nullptr, hndle);
        return *hndle;
    }
    template<typename type>
    constexpr type doPointerAlloc2(auto* strct, type* hndle, auto pHndl)
    {
        (pHndl)(volkGetLoadedDevice(), strct ,nullptr, hndle);
        return *hndle;
    }
    template<typename type>
    constexpr type doPointerAlloc3(auto* strct, auto* hndle)
    {
        type pHndl = nullptr; 
        (hndle)(volkGetLoadedDevice(), strct ,nullptr, &pHndl);
        return pHndl;
    }
    template<typename type, typename type2f>
    constexpr type doPointerAlloc3Alt(auto* strct)
    {
        type pHndl = nullptr; 
        (type2f)(volkGetLoadedDevice(), strct, &pHndl);
        return pHndl;
    }
    
    template<typename type, typename ... fcn>
    [[nodiscard]] constexpr auto doPointerAlloc5(auto* __restrict__ strct, auto* hndle) noexcept -> type
    {
        type pHndl; 
        hndle(volkGetLoadedDevice(), strct, nullptr, &pHndl);
        return pHndl;
    }
    template<typename type>
    constexpr type doPointerAllocSml(auto* strct, /* type* hndle,  */auto pHndl)
    {
        type hndle = nullptr;
        (pHndl)(volkGetLoadedDevice(), strct ,nullptr, &hndle);
        return hndle;
    }

    template<typename type>
    constexpr type doPointerAllocX(auto* strct)
    {
        type pHndl = nullptr; 
        vkCreateGraphicsPipelines(volkGetLoadedDevice(), nullptr, 1, strct, nullptr, &pHndl);
        return pHndl;
    }
    template<typename type>
    constexpr type doPointerAllocX2(auto* strct)
    {
        type pHndl = nullptr; 
        vkCreateShaderModule(volkGetLoadedDevice(), strct, nullptr, &pHndl);
        return pHndl;
    }
    
    
}