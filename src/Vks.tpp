#pragma once

#include <iostream>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>


constexpr uint16_t width = 1280;
constexpr uint16_t height = 720;
constexpr uint8_t Frames = 8;
constexpr bool checks = true;
constexpr void chkTst(VkResult buh) noexcept
{
  if constexpr(checks)
  {
      switch (buh) 
      {
        case VK_NOT_READY:  std::cout << "VK_NOT_READY" << "\n"; break;
        case VK_TIMEOUT: std::cout << "VK_TIMEOUT" << "\n"; break;
        case VK_EVENT_SET: std::cout << "VK_EVENT_SET" << "\n"; break;
        case VK_EVENT_RESET: std::cout << "VK_EVENT_RESET" << "\n"; break;
        case VK_INCOMPLETE: std::cout << "VK_INCOMPLETE" << "\n"; break;
        case VK_ERROR_OUT_OF_HOST_MEMORY: std::cout << "VK_ERROR_OUT_OF_HOST_MEMORY" << "\n"; break;
        case VK_ERROR_OUT_OF_DEVICE_MEMORY: std::cout << "VK_ERROR_OUT_OF_DEVICE_MEMORY" << "\n"; break;
        case VK_ERROR_INITIALIZATION_FAILED: std::cout << "VK_ERROR_INITIALIZATION_FAILED" << "\n"; break;
        case VK_ERROR_DEVICE_LOST: std::cout << "VK_ERROR_DEVICE_LOST" << "\n"; break;
        case VK_ERROR_MEMORY_MAP_FAILED: std::cout << "VK_ERROR_MEMORY_MAP_FAILED" << "\n"; break;
        case VK_ERROR_LAYER_NOT_PRESENT: std::cout << "VK_ERROR_LAYER_NOT_PRESENT" << "\n"; break;
        case VK_ERROR_EXTENSION_NOT_PRESENT: std::cout << "VK_ERROR_EXTENSION_NOT_PRESENT" << "\n"; break;
        case VK_ERROR_FEATURE_NOT_PRESENT: std::cout << "VK_ERROR_FEATURE_NOT_PRESENT" << "\n"; break;
        case VK_ERROR_INCOMPATIBLE_DRIVER: std::cout << "VK_ERROR_INCOMPATIBLE_DRIVER" << "\n"; break;
        case VK_ERROR_TOO_MANY_OBJECTS: std::cout << "VK_ERROR_TOO_MANY_OBJECTS" << "\n"; break;
        case VK_ERROR_FORMAT_NOT_SUPPORTED: std::cout << "VK_ERROR_FORMAT_NOT_SUPPORTED" << "\n"; break;
        case VK_ERROR_FRAGMENTED_POOL: std::cout << "VK_ERROR_FRAGMENTED_POOL" << "\n"; break;
        case VK_ERROR_UNKNOWN: std::cout << "VK_ERROR_UNKNOWN" << "\n"; break;
        case VK_ERROR_OUT_OF_POOL_MEMORY: std::cout <<"VK_ERROR_OUT_OF_POOL_MEMORY" << "\n"; break;
        case VK_ERROR_INVALID_EXTERNAL_HANDLE: std::cout <<"VK_ERROR_INVALID_EXTERNAL_HANDLE" << "\n"; break;
        case VK_ERROR_FRAGMENTATION: std::cout <<"VK_ERROR_FRAGMENTATION" << "\n"; break;
        case VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS: std::cout <<"VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS" << "\n"; break;
        case VK_PIPELINE_COMPILE_REQUIRED: std::cout <<"VK_PIPELINE_COMPILE_REQUIRED" << "\n"; break;
        case VK_ERROR_SURFACE_LOST_KHR: std::cout <<"VK_ERROR_SURFACE_LOST_KHR" << "\n"; break;
        case VK_ERROR_NATIVE_WINDOW_IN_USE_KHR: std::cout <<"VK_ERROR_NATIVE_WINDOW_IN_USE_KHR" << "\n"; break;
        case VK_SUBOPTIMAL_KHR: std::cout <<"VK_SUBOPTIMAL_KHR" << "\n"; break;
        case VK_ERROR_OUT_OF_DATE_KHR: std::cout <<"VK_ERROR_OUT_OF_DATE_KHR" << "\n"; break;
        case VK_ERROR_INCOMPATIBLE_DISPLAY_KHR: std::cout <<"VK_ERROR_INCOMPATIBLE_DISPLAY_KHR" << "\n"; break;
        case VK_ERROR_VALIDATION_FAILED_EXT: std::cout <<"VK_ERROR_VALIDATION_FAILED_EXT" << "\n"; break;
        case VK_ERROR_INVALID_SHADER_NV: std::cout <<"VK_ERROR_INVALID_SHADER_NV" << "\n"; break;
        case VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT: std::cout <<"VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT" << "\n"; break;
        case VK_ERROR_NOT_PERMITTED_KHR: std::cout <<"VK_ERROR_NOT_PERMITTED_KHR" << "\n"; break;
        case VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT: std::cout <<"VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT" << "\n"; break;
        case VK_THREAD_IDLE_KHR: std::cout <<"VK_THREAD_IDLE_KHR" << "\n"; break;
        case VK_THREAD_DONE_KHR: std::cout <<"VK_THREAD_DONE_KHR" << "\n"; break;
        case VK_OPERATION_DEFERRED_KHR: std::cout <<"VK_OPERATION_DEFERRED_KHR" << "\n"; break;
        case VK_OPERATION_NOT_DEFERRED_KHR: std::cout <<"VK_OPERATION_NOT_DEFERRED_KHR" << "\n"; break;
        case VK_ERROR_COMPRESSION_EXHAUSTED_EXT: std::cout <<"VK_ERROR_COMPRESSION_EXHAUSTED_EXT" << "\n"; break;
      
        default: [[likely]] return;
        // case VK_SUCCESS: { return;}
      }
      [[unlikely]]exit(1);
  }


}

static struct Vks 
{
    static inline VkDevice Device;
    template<typename type, typename ... fcn>
    [[nodiscard]] static constexpr auto doPointerAlloc5(auto* __restrict__ strct, auto* hndle) noexcept -> type
    {
        type pHndl; 
        chkTst(hndle(Device, strct, nullptr, &pHndl));
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





struct VkCommSet
{
    VkCommandPool commandPool=genCommPool();
    VkCommandBuffer commandBuffer=doGenCommnd(commandPool);
    [[nodiscard]] auto constexpr genCommPool() const -> VkCommandPool;
    [[nodiscard]] auto inline doGenCommnd(VkCommandPool) const -> VkCommandBuffer;
     constexpr void beginSingleTimeCommands();
     constexpr void endSingleTimeCommands(VkQueue queue);
};
 constexpr void VkCommSet::beginSingleTimeCommands()
{
    constexpr VkCommandBufferBeginInfo beginInfo1 = { .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
                                                    .flags = ( VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) };
  vkBeginCommandBuffer(commandBuffer, &beginInfo1);
}
auto VkCommSet::doGenCommnd(VkCommandPool commandPool) const -> VkCommandBuffer
{
  VkCommandBuffer PreTestBuffer;
   const VkCommandBufferAllocateInfo allocateInfo{ .sType              =  VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ,
                                                  .commandPool        =  commandPool ,
                                                  .level              =  VK_COMMAND_BUFFER_LEVEL_PRIMARY ,
                                                  .commandBufferCount = 1};
  std::cout << allocateInfo.commandBufferCount << "Command Buffers"
            << "\n";
  vkAllocateCommandBuffers(Vks::Device, &allocateInfo, &PreTestBuffer );
  return PreTestBuffer;
}
constexpr auto VkCommSet::genCommPool() const -> VkCommandPool
{
 constexpr VkCommandPoolCreateInfo  poolInfo = {
    .sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
    .pNext            = nullptr,
    .flags=VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
    .queueFamilyIndex = 0,
  };
  return Vks::doPointerAlloc5<VkCommandPool>( &poolInfo, vkCreateCommandPool );
 
}

constexpr void VkCommSet::endSingleTimeCommands(VkQueue queue)
{
  vkEndCommandBuffer( commandBuffer );
  const VkSubmitInfo       submitInfo1 = {
          .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO, .pNext = VK_NULL_HANDLE, .commandBufferCount = ( 1 ), .pCommandBuffers = &commandBuffer
  };
//   a = ( a ^ 1 );
  vkQueueSubmit( queue, 1, &submitInfo1, VK_NULL_HANDLE );
  vkQueueWaitIdle( queue );
//   vkResetCommandPool( Vks::Device, ( commandPool2 ), VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT );
}