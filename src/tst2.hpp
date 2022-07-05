#include <stb_include.h>
#include <stb_image.h>
#include <vulkan/vulkan_core.h>
#include "memSys.hpp"
#include "VKI.hpp"
#include "Vks.tpp"

struct tst2
{
    VkImage image;
    // VkDeviceMemory memory;
    VkBuffer stagingBuffer;
    VkCommSet commandBufferSets;
    tst2(VkCommandBuffer commandBuffer) : commandBuffer(commandBuffer);
    VkImage setupImagetest(memSys&);
    void transitionImageLayout( VkInit &VKI, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout );
    auto copyImage( VkInit &VKI,  VkExtent3D extent);
    void vkRecImg(VkCommandBuffer commandBuffer);

};