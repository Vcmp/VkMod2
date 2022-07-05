#pragma once

#include <vulkan/vulkan_core.h>
#include "memSys.hpp"

#include "Vks.tpp"

static constexpr VkImageSubresourceLayers subresource = {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
	    .mipLevel = 0,
	    .baseArrayLayer = 0,
	    .layerCount = 1,
        };


struct tst2
{
    VkQueue GraphicsQueue2;
    VkImage image;
    // VkDeviceMemory memory;
    VkBuffer stagingBuffer;
    VkCommSet commandBufferSets;
    explicit tst2(VkQueue queue, VkCommSet commandBufferSets, memSys &memSys) : GraphicsQueue2(queue), commandBufferSets(commandBufferSets), image(setupImagetest(memSys)){};
    VkImage setupImagetest(memSys&);
    void transitionImageLayout( VkQueue transferQueue, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout );
    auto copyBufToImg( VkBuffer buffer, VkImage image, VkExtent3D extent);
    auto copyImgToBuf( VkExtent3D extent);
    void vkRecImg(VkImageLayout srcImageLayout, VkImageLayout dstImageLayout);

};