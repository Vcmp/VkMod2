#include "glm/ext/matrix_float4x4.hpp"
#include "mat4x.hpp"
#include <cassert>
#include <cstdint>
#include <cwchar>
#include <array>
#include <immintrin.h>
#include <iostream>





/*
 * Note* casting issues usually mostly only occur with the AVX2 instrincis function delcarations  available
 * and while teh AVX counterparts for floats also do not supprot void* they instead supprot *float insetad which is till a great/considerable improvement
 */

[[gnu::pure]]auto    mat4x::retCL(bool a, uint8_t c)
{
  assert(c<4);
}
[[gnu::pure]]auto    mat4x::retCLx2(bool a, uint8_t c)
{
  __float512 axl;
  __m256 aaxlvaxzvw;
  __m256 aaxlvaxzvwzaxwaz;

  auto idxMov={0, 4, 8, 12, 1, 5, 9, 13};
  auto idxMov2=__extension__(__m256){static_cast<float>(a)};

  return a?__builtin_shufflevector(__a, __b, 0, 4, 8, 12, 1, 5, 9, 13):__builtin_shufflevector(__a, __b, 2, 6, 10, 14, 3, 7, 11, 15);
  
}
[[gnu::pure]]auto    mat4x::t(mat4x a)
{
 
  //return x;
  
}
[[gnu::pure]]auto    mat4x::t2(mat4x a)
{
  std::array<__m256, 2> xyzw;
  // std::array<__m256, 2> wzyxq;
  // memcpy(xyzw.data(), &a.__ab, sizeof(mat4x));
  // memcpy(wzyxq.data(), &this->__ab, sizeof(mat4x));

  for(int i=0;i<2;i++)
  {
    xyzw[i]=retCLx2(i, i)*this->__a;
    xyzw[i]*=retCLx2(i, i)*this->__b;

  }

  memcpy(this, xyzw.data(), sizeof(xyzw));
  //return x;
  
}
