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
        .sharingMode=VK_SHARING_MODE_EXCLUSIVE,
        // .usage
    };
}