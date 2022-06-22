#include <stb_include.h>
#include <stb_image.h>
#include "Vks.tpp"


struct tst2
{
    VkImage image;
    VkDeviceMemory memory;
    VkBuffer buffer;

    void setupImagetest();
};