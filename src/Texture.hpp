#pragma once


#include "src/Queues.hpp"
#include <stdexcept>
#include <vulkan/vulkan_core.h>
struct Texture
{
    static void createTextureImage();
};



static VkFormat findDepthFormat()
    {
        VkFormat formatCandidates[3]={VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT};
        VkFormatProperties props;

        for (VkFormat format : formatCandidates) {

           
            vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &props);

            const int i2 = props.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT;
            if (i2 == VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT/* && VK10.VK_IMAGE_TILING_OPTIMAL == VK_IMAGE_TILING_OPTIMAL*/) {
                return format;
            }
        }

        std::runtime_error("failed to find supported format!");
    }


    // inline void createTextureImage()
    // {
    //     const char a[] = ("/shaders/terrain.png");
    //     std::cout<<(a);
       
        
    //     int[] pWidth = {0};
    //     int[] pHeight = {0};
    //     int[] pChannels = {0};
    //     void* pixels = STBImage.stbi_load(filename, pWidth, pHeight, pChannels, STBImage.STBI_rgb_alpha);


    //     int imageSize = pWidth[0] * pHeight[0] * pChannels[0];

    //     if (pixels == null) {
    //         throw new RuntimeException("No Image!");
    //     }

    //     long[] stagingBufferImg = {0};
    //     Buffers.setBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT, imageSize, stagingBufferImg);
    //     long[] stagingBufferMemoryImg = {0};
    //     Buffers.createBuffer(stagingBufferImg, stagingBufferMemoryImg);


    //     nvkMapMemory(device, stagingBufferMemoryImg[0], 0, imageSize, 0, MemSysm.address);
    //     {
    //         //                        memByteBuffer(getHandle(), imageSize).put(pixels);
    //        memcpy((pixels), MemSysm.getHandle(), imageSize);
    //     }
    //     vkUnmapMemory(device, stagingBufferMemoryImg[0]);
    //     STBImage.stbi_image_free(pixels);

    //     createImage(pWidth[0], pHeight[0],
    //             VK_FORMAT_R8G8B8A8_SRGB,
    //             VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT
    //     );


    //     copyBufferToImage(stagingBufferImg, pWidth[0], pHeight[0]);
    //     transitionImageLayout(VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    // }