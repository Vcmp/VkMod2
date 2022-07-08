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
  return (a)?_mm_set_ps(__ab[0+c], __ab[4+c], __ab[8+c], __ab[12+c]) : _mm_set_ps(__ab[0+c], __ab[1+c], __ab[2+c], __ab[3+c]);
}
[[gnu::pure]]auto    mat4x::retCLx2(bool a, uint8_t c)
{
  assert(c<2);
  return (a)?_mm256_set_ps(__ab[0+c], __ab[1+c], __ab[2+c], __ab[3+c], __ab[4+c], __ab[5+c], __ab[6+c], __ab[7+c]):_mm256_set_ps(__ab[0+c], __ab[4+c], __ab[8+c], __ab[12+c], __ab[1+c], __ab[5+c], __ab[9+c], __ab[13+c]);
  
}
[[gnu::pure]]auto    mat4x::t(mat4x a)
{
  std::array<__m128, 4> xyzw;

  for(int i=0;i<4;i++)
  {
    xyzw[i]=a.retCL(false,i)*a.retCL(true,0);
    xyzw[i]*=a.retCL(false,i)*a.retCL(true,1);
    xyzw[i]*=a.retCL(false,i)*a.retCL(true,2);
    xyzw[i]*=a.retCL(false,i)*a.retCL(true,3);
  }

  memcpy(&this->__ab, xyzw.data(), sizeof(xyzw));
  //return x;
  
}
[[gnu::pure]]auto    mat4x::t2(mat4x a)
{
  std::array<__m256, 2> xyzw;

  for(int i=0;i<2;i++)
  {
    xyzw[i]=retCLx2(false, i)*a.retCLx2(true,0);
    xyzw[i]*=retCLx2(false, i)*a.retCLx2(true,1);

  }

  memcpy(&this->__ab, xyzw.data(), sizeof(xyzw));
  //return x;
  
}
