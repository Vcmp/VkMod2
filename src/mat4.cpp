#include "glm/ext/matrix_float4x4.hpp"
#include "mat4x.hpp"
#include <cwchar>





/*
 * Note* casting issues usually mostly only occur with the AVX2 instrincis function delcarations  available
 * and while teh AVX counterparts for floats also do not supprot void* they instead supprot *float insetad which is till a great/considerable improvement
 */
 auto mat4x::lud( const float * a ) const -> __m256
{
  return *(const __m256 *)( ( ( a ) ) );
}


 void mat4x::loadAligned( const glm::mat<4,4,float> &a )
{
    memcpy(this, &a, sizeof(a));
    
 
}
 void mat4x::loadAligned( const mat4x * a )
{
  mat4x::__a = a->__a;
  mat4x::__b = a->__b;
}
// Try to add a translation before Multiplying the matrix as an attempted Optimisation
//  void mat4x::domatFMA( mat4x * b, __m256 __Trans )
// {
//   // _mm256_fmadd_ps
//   __a[8] *= __Trans[8];
//   b->__a = __builtin_ia32_vfmaddps256( mat4x::__a, b->__a, __Trans );
//   b->__b = __builtin_ia32_vfmaddps256( mat4x::__b, b->__b, __Trans );
// }
// /*
//  * Might be useful to exploit the 'Pure' attribute to by 'reusing' the last
//  * results if passed by pointer?refernce as it effectivley allows the state of the Matrix to be '"reset"'

//  */
//  void mat4x::domatFMA( mat4x & b )
// {
//   // _mm256_fmadd_ps
//   __a = _mm256_mul_ps( __a, b.__a );
//   __b = _mm256_mul_ps( __b, b.__b );
// }






   constexpr void     mat4x::toAddress(const __m256* a )
  {
     *(__m256 *)a = __a;
     *(__m256 *)(a+1) = __b;
  }
