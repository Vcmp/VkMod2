#pragma once


#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <vector>
#include <vulkan/vulkan_core.h>
#include "Buffers.hpp"

inline namespace Texture 
{
    extern VkImage vkImage;
    extern VkDeviceMemory vkAllocMemory;
    static void createTextureImage();
    static VkFormat findDepthFormat();
    static void createDepthResources();
    static void createImage(uint32_t, uint32_t, VkFormat, int);
    static void transitionImageLayout(int, VkImageLayout, VkImageLayout);
    static void createImageView(int, VkImageAspectFlagBits, VkImageLayout);
};






    inline void Texture::createTextureImage()
    {
        const char a[] = ("/shaders/terrain.png");
        std::cout<<(a);
       
       
        const int fhndl=_sopen(a, _O_RDONLY | _O_BINARY | _O_SEQUENTIAL, 0x20, 0x0100);
    // if(!file)
    // {
    //     std::runtime_error("Fail:Bad or No ShaderFile!");
    // }
     _lseek(fhndl, 0, SEEK_END);
   const size_t size = _tell(fhndl);
   _lseek(fhndl, 0, SEEK_END);

        uint8_t pixels[size];

    std::cout<< size << "\n";
   if(_eof(fhndl)==-1)
    {
      
       throw std::runtime_error("Fail:Bad or No ShaderFile!");
    }
     _read(fhndl, pixels, size);
     std::cout<< pixels << "\n";
    _flushall();
    _close(fhndl);
       


        size_t imageSize = size * 3;

        if (pixels == nullptr) {
            throw std::runtime_error("No Image!");
        }

        VkBuffer stagingBufferImg = {0};
        Buffers::setBuffer(VK_BUFFER_USAGE_TRANSFER_SRC_BIT, imageSize, stagingBufferImg);
        VkDeviceMemory stagingBufferMemoryImg = {0};
        Buffers::createBuffer(stagingBufferImg, stagingBufferMemoryImg);


        // vkMapMemory(device, stagingBufferMemoryImg, 0, imageSize, 0, MemSysm.address);
        {
            //                        memByteBuffer(getHandle(), imageSize).put(pixels);
        //    memcpy((pixels), MemSysm.getHandle(), imageSize);
        }
        vkUnmapMemory(device, stagingBufferMemoryImg);
        // STBImage.stbi_image_free(pixels);

        Texture::createImage(1024, 1024,
                VK_FORMAT_R8G8B8A8_SRGB,
                VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT
        );


        // copyBufferToImage(stagingBufferImg, 1024, 1024);
        Texture::transitionImageLayout(VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    }

    inline void Texture::createImage(uint32_t width, uint32_t height, VkFormat format, int usage)
    {
        VkImageCreateInfo imageInfo = {};
                imageInfo.sType=VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
                imageInfo.imageType=VK_IMAGE_TYPE_2D;
        imageInfo.extent.width=width;
                 imageInfo.extent.height=height;
                 imageInfo.extent.depth=1;
        imageInfo.mipLevels=1;
                imageInfo.arrayLayers=1;
                imageInfo.format=format;
                imageInfo.tiling=VK_IMAGE_TILING_OPTIMAL;
                imageInfo.initialLayout=VK_IMAGE_LAYOUT_UNDEFINED;
                imageInfo.usage=usage;
                imageInfo.samples=VK_SAMPLE_COUNT_1_BIT;
                imageInfo.sharingMode=VK_SHARING_MODE_EXCLUSIVE;
       
        vkCreateImage(device, &imageInfo, VK_NULL_HANDLE, &Texture::vkImage);
        VkMemoryDedicatedRequirementsKHR img2 ={};

        VkMemoryRequirements2 memRequirements = {};
        vkGetImageMemoryRequirements(device, Texture::vkImage, &memRequirements.memoryRequirements);

        VkMemoryAllocateInfo allocInfo = {};
                allocInfo.sType=VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                //    allocInfo.pNext=vkMemoryDedicatedAllocateInfoKHR;
                allocInfo.allocationSize=memRequirements.memoryRequirements.size;
                allocInfo.memoryTypeIndex=Buffers::findMemoryType(physicalDevice, memRequirements.memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

        if (img2.prefersDedicatedAllocation || img2.requiresDedicatedAllocation) {
            std::cout<<("Using Dedicated Memory Allocation")<<"\n";
            VkMemoryDedicatedAllocateInfo dedicatedAllocateInfoKHR = {};
            dedicatedAllocateInfoKHR.sType=VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
                    dedicatedAllocateInfoKHR.image=Texture::vkImage;

            allocInfo.pNext=&dedicatedAllocateInfoKHR;
        }

      
        vkAllocateMemory(device, &allocInfo, VK_NULL_HANDLE, &Texture::vkAllocMemory);

        vkBindImageMemory(device, Texture::vkImage, Texture::vkAllocMemory, 0);
    }



    static void Texture::transitionImageLayout(int format, VkImageLayout oldLayout, VkImageLayout newLayout)
    {
        VkCommandBuffer commandBuffer= Buffers::beginSingleTimeCommands();

        VkImageMemoryBarrier barrier = {
                .sType=VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
                .pNext=VK_NULL_HANDLE,
                .oldLayout=oldLayout,
                .newLayout=(newLayout),
                .srcQueueFamilyIndex=(VK_IMAGE_LAYOUT_UNDEFINED),
                .dstQueueFamilyIndex=(VK_IMAGE_LAYOUT_UNDEFINED),
                .image=(Texture::vkImage),
        barrier.subresourceRange={
                .aspectMask=static_cast<VkImageAspectFlags>((format)),
                .baseMipLevel=(0),
                .levelCount=(1),
                .baseArrayLayer=(0),
                .layerCount=(1)},
                };
//            membarrier=barrier.address0();
        if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {


            if (format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT) {
                barrier.subresourceRange.aspectMask=(
                        barrier.subresourceRange.aspectMask | VK_IMAGE_ASPECT_STENCIL_BIT);
            }

        }

        VkPipelineStageFlags sourceStage;
         VkPipelineStageFlags destinationStage;
        switch (oldLayout) {
            case VK_IMAGE_LAYOUT_UNDEFINED: { barrier.srcAccessMask=(VK_ACCESS_NONE_KHR);break;};
            case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL: {barrier.srcAccessMask=VK_ACCESS_TRANSFER_WRITE_BIT;break;};
            default: throw std::runtime_error("Unsupported layout transition");
        }
        switch (newLayout) {
            case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL: {
                barrier.subresourceRange.aspectMask=(VK_IMAGE_ASPECT_DEPTH_BIT);

                barrier.dstAccessMask=(VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT);
                sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
                destinationStage = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
                break;
            }
            case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL: {
                barrier.subresourceRange.aspectMask=(VK_IMAGE_ASPECT_COLOR_BIT);

                barrier.dstAccessMask=(VK_ACCESS_SHADER_READ_BIT);
                sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
                destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
                break;
            }
            default:throw std::runtime_error("Unsupported layout transition");
        }
       
        vkCmdPipelineBarrier(
                commandBuffer,
                sourceStage /* TODO */, destinationStage /* TODO */, 0,
                0,
                VK_NULL_HANDLE,
                0,
                VK_NULL_HANDLE,1,&barrier);
        Buffers::endSingleTimeCommands(commandBuffer);


    }