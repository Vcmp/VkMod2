
#include "VKI.hpp"
// const VkDevice device = VKI.device;


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
        (pHndl)(VKI.device, strct ,nullptr, hndle);
        return *hndle;
    }
    template<typename type>
    constexpr type doPointerAlloc3(auto* strct, auto* hndle)
    {
        type pHndl = nullptr; 
        (hndle)(VKI.device, strct ,nullptr, &pHndl);
        return pHndl;
    }
    template<typename type, typename type2f>
    constexpr type doPointerAlloc3Alt(auto* strct)
    {
        type pHndl = nullptr; 
        (type2f)(VKI.device, strct, &pHndl);
        return pHndl;
    }
    
    template<typename type>
    [[nodiscard]] constexpr auto doPointerAlloc5(auto* __restrict__ strct, auto* hndle) noexcept -> type
    {
        type pHndl; 
        (hndle)(VKI.device, strct, nullptr, &pHndl);
        return pHndl;
    }
    template<typename type>
    constexpr type doPointerAllocSml(auto* strct, /* type* hndle,  */auto pHndl)
    {
        type hndle = nullptr;
        (pHndl)(VKI.device, strct ,nullptr, &hndle);
        return hndle;
    }

    template<typename type>
    constexpr type doPointerAllocX(auto* strct, auto* hndle)
    {
        type pHndl = nullptr; 
        vkCreateGraphicsPipelines(VKI.device, nullptr, 1, strct, nullptr, &pHndl);
        return pHndl;
    }
    
    
}