#include "glm/ext/matrix_float4x4.hpp"
#include "mat4x.hpp"
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
  c&=0x3;
  if (a)
  {
    return __extension__(__m128){__ab[0+c], __ab[4+c], __ab[8+c], __ab[12+c]};
  }
  else
  {
     
       return __extension__(__m128){__ab[0+c], __ab[1+c], __ab[2+c], __ab[3+c]};
     
  }
}
[[gnu::pure]]auto    mat4x::retCLx2(bool a)
{
  if(a)
    return __extension__(__m256){__ab[0], __ab[1], __ab[2], __ab[3], __ab[4], __ab[5], __ab[6], __ab[7]};
  else return __extension__(__m256){__ab[8], __ab[9], __ab[10], __ab[11], __ab[12], __ab[13], __ab[14], __ab[15]};
  
}
[[gnu::pure]]auto    mat4x::t(mat4x a)
{
  std::array<__m128, 4> xyzw;

  for(int i=0;i<4;i++)
  {
    xyzw[i]=this->__ab[i]*a.retCL(true,0);
    xyzw[i]*=this->__ab[i]*a.retCL(true,1);
    xyzw[i]*=this->__ab[i]*a.retCL(true,2);
    xyzw[i]*=this->__ab[i]*a.retCL(true,3);
  }

  memcpy(&this->__ab, xyzw.data(), sizeof(xyzw));
  //return x;
  
}
[[gnu::pure]]auto    mat4x::t2(mat4x a)
{
  std::array<__m128, 4> xyzw;

  for(int i=0;i<4;i++)
  {
    xyzw[i]=retCL(false, i)*a.retCL(true,0);
    xyzw[i]*=retCL(false, i)*a.retCL(true,1);
    xyzw[i]*=retCL(false, i)*a.retCL(true,2);
    xyzw[i]*=retCL(false, i)*a.retCL(true,3);
  }

  memcpy(&this->__ab, xyzw.data(), sizeof(xyzw));
  //return x;
  
}
