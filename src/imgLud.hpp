
#pragma once

// using stbi_uc = unsigned char;
struct tstA //Placed in Seperate TU to help gerately allevaite the extremely long Compilation Times induced by the stbi_image_load Header
{
static auto loadImg(int &x, int&y, int&cnls) -> unsigned char*;
static void freeImg(unsigned char*);

};
