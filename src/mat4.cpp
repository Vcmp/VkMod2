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

//  void mat4x::permute()
// {
//   __m128  x = _mm256_castps256_ps128( __a );
//   __m256d y = _mm256_castps_pd( __b );

//   x[1] = y[1];
//   x[2] = y[2];
// }

//  void mat4x::loadTmp( const float * a )
// {
//   __a = _mm256_load_ps( a );
//   __b = _mm256_load_ps( a + 8 );
// }
//  mat4x mat4x::loadAlignedA( const void * a )
// {
//   mat4x::__a = ( _mm256_load_ps( static_cast<float const *>( a ) ) );
//   mat4x::__b = ( _mm256_load_ps( static_cast<float const *>( a ) + 8 ) );
//   return *this;
// }
 void mat4x::loadAligned( const glm::mat<4,4,float> &a )
{
  // auto aa = { a[0][1], a[0][2], a[0][3], a[2][0], a[2][1], a[2][2], a[2][3]};
  // auto bb = {a[1][0], a[1][1], a[1][2], a[1][3], a[3][0], a[3][1], a[3][2], a[3][3]};
    memcpy(this, &a, sizeof(a));
    
 
  // mat4x::__a = ( *(const __m256 *)aa.begin());
  // mat4x::__b = ( *(const __m256 *)bb.begin());
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


//  mat4x * mat4x::identity()
// {
//   // loadAligned( &( ax ) );
//   return this;
// }

//  void mat4x::neg()
// {
//   __a = _mm256_andnot_ps( __a, __b );
//   __b = _mm256_andnot_ps( __b, __a );
// }

//  mat4x mat4x::copyOf()
// {
//   return *this;
// }

//  void mat4x::show()
// {

//   for (auto zx = { __a, __b };  __m256 v : zx )
//   {
//     printf( "%f | %f | %f | %f \n", v[0], v[0 + 1], v[0 + 2], v[0 + 3] );
//     printf( "%f | %f | %f | %f \n", v[4], v[4 + 1], v[4 + 2], v[4 + 3] );
//   }

//   printf( "\n" );
// }

// Very heavily based from the Java Joml/ C++ GLM Library:
void mat4x::doPerspective( float fovy, float aspect, float zFar, float zNear )
{
  // float const tanHalfFovy = tan( fovy / static_cast<float>( 2 ) );

  // __a[0] = 1 / ( aspect * tanHalfFovy );
  // __a[5] = 1 / ( tanHalfFovy );
  // __b[2] = zFar / ( zFar - zNear );
  // __b[3] = 1;
  // __b[6] = -( zFar * zNear ) / ( zFar - zNear );
  // m6.doLook( 1 );
}

// void mat4x::doLook( float a )
// {
//   __b[1] = 1;
//   __a[2] = 2;
//   __a[6] = 2;
//   __b[3] = 2;
//   __b[4] = -( 0.F * 2.F );
//   __b[5] = -( 1.F * 2.F );
//   __b[6] = -( 2.F * 2.F );
//   // return Result;
// }


   constexpr void     mat4x::toAddress(const __m256* a )
  {
     *(__m256 *)a = __a;
     *(__m256 *)(a+1) = __b;
  }
