#define STB_IMAGE_IMPLEMENTATION
#include "imgLud.hpp"
#include <stb_image.h>
auto tstA::loadImg(int &x, int&y, int&cnls) -> stbi_uc*
{

    return stbi_load(R"(tst.png)", &x, &y, &cnls, STBI_rgb);
}

void tstA::freeImg(stbi_uc *limg)
{
    stbi_image_free(limg);
}