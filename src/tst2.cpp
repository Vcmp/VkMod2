#include "tst2.hpp"
#include <vulkan/vulkan_core.h>



void tst2::setupImagetest()
{
    int x;
    int y;
    int cnls;
    auto limg = stbi_load("tst.png", &x, &y, &cnls, 3);

    VkMappedMemoryRange aa;

    VkBufferCreateInfo a 
    {
        .sType=VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size=sizeof(limg),
        .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT,
        .sharingMode=VK_SHARING_MODE_EXCLUSIVE,
    };
}