#pragma once

#include "glm/ext/scalar_constants.hpp"
#include "glm/trigonometric.hpp"

#include <cstdio>
#include <immintrin.h>

/*too lazy to do an SSE version as AVX in many cases can allow for the abilkity to the same steps in half as many stages
 e.g. Might be able to get away withput using amore explict construct arg sets and isntead just implicitly and
 Automatically intialise the struct iwth a constexpr Identify Maxtrix Struct.Blob/StandIn Instead _read(int _FileHandle,
 void *_DstBuf, unsigned int _MaxCharCount)
*/
static inline constexpr float ax[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
inline static struct __attribute__( ( __vector_size__( 64 ), __aligned__( 64 ) ) ) mat4x
{
private:
  //__m256 __ab[2];
  __m256 __a;
  __m256 __b;

public:
  constexpr explicit mat4x() : __a( lud( ax ) ), __b( lud( ax + 8 ) ) {}
  // float a[2][8];

  inline constexpr __m256 __vectorcall lud( const float[] ) __attribute__( ( __aligned__( sizeof( __m256 ) ) ) );
  // inline constexpr __m256 __vectorcall lud( const void * a ) __attribute__( ( __aligned__( sizeof( __m256 ) ) ) );
  inline void           domatFMA( mat4x *, __m256 );
  inline constexpr void domatFMA( mat4x & );

  // inline constexpr void __vectorcall loadAligned( float a[16] );
  inline constexpr void __vectorcall loadTmp( const float[] );
  // inline void              loadAligned( mat4x ) __declspec( preserve_most );
  inline constexpr void    loadAligned( const void * a ) __attribute__( ( preserve_most ) );
  inline constexpr mat4x * identity();
  inline void              neg();
  inline void              setPerspective( float, float, float, float, bool );
  inline constexpr mat4x   copyOf() __attribute__( ( pure ) );
  inline void              show();
  inline void              permute();
  inline void              doRot( float );
} m4;

// inline constexpr void __vectorcall mat4x::loadAligned( float a[16] )
// {
//   //_mm_storeu_si128((__m128*)aa, mat4x::a);
//   __a = ( lud( a ) );
//   __b = ( lud( &a + 8 ) );
// }

inline void mat4x::permute()
{
  __m128  x = _mm256_castps256_ps128( __a );
  __m256d y = _mm256_castps_pd( __b );

  x[1] = y[1];
  x[2] = y[2];
}

inline constexpr void mat4x::loadTmp( const float * a )
{
  //_mm_storeu_si128((__m128*)aa, mat4x::a);
  __a = _mm256_load_ps( a );
  __b = _mm256_load_ps( a + 8 );
}
inline constexpr void mat4x::loadAligned( const void * a )
{
  //_mm_storeu_si128((__m128*)aa, mat4x::a);
  mat4x::__a = ( _mm256_load_ps( static_cast<float const *>( a ) ) );
  mat4x::__b = ( _mm256_load_ps( static_cast<float const *>( a ) + 8 ) );

  // __a = _mm256_andnot_ps( __b, __a );
  // __b[4]     = 1.0F;
  // __b[5]     = 1.0F;
  // __b[7] += 10.0F;
}
// inline void mat4x::loadAligned( mat4x b )
// {
//   //_mm_storeu_si128((__m128*)aa, mat4x::a);
//   __a = b.__a;
//   __b = b.__b;

//   // __a = _mm256_andnot_ps( __b, __a );
//   // __b[4]     = 1.0F;
//   // __b[5]     = 1.0F;
//   // __b[7] += 10.0F;
// }
// Try to add a translation before Multiplying the matrix as an attempted Optimisation
inline void mat4x::domatFMA( mat4x * b, __m256 __Trans )
{
  // _mm256_fmadd_ps
  __a[8] *= __Trans[8];
  b->__a = __builtin_ia32_vfmaddps256( mat4x::__a, b->__a, __Trans );
  b->__b = __builtin_ia32_vfmaddps256( mat4x::__b, b->__b, __Trans );
}
/*
 * Might be useful to retain teh expected side-effetcs.bugs.oversoght.ineicincpted efeftcs of Pure by reusing the last
 * resuls if passed by pointer?refernce as it effectivley allows the state of the Matrix to be '"reset"' between each
 * isteal. Mul.Operation>Modifictaion>Writeing to
 */
inline constexpr void mat4x::domatFMA( mat4x & b )
{
  // _mm256_fmadd_ps
  __a = _mm256_mul_ps( __a, b.__a );
  __b = _mm256_mul_ps( __b, b.__b );
}
// Hide ugly casting syntax for aligned load as unlike the AVX512 intrinsics provided by intel, man Load/many intrisics
// Functions do not include Void* by default as an Argument
inline constexpr __m256 __vectorcall mat4x::lud( const float * a )
{
  return _mm256_load_ps( ( ( a ) ) );
}

inline constexpr mat4x * mat4x::identity()
{
  loadAligned( ( ax ) );
  return this;
}

inline void mat4x::neg()
{
  __a = _mm256_andnot_ps( __a, __b );
  __b = _mm256_andnot_ps( __b, __a );
}
// Very heavily based from the Java Joml Library:
//  void setPerspective(float fovy, float aspect, float zNear, float zFar, bool zZeroToOne)
//  {

// }

inline constexpr mat4x mat4x::copyOf()
{
  return *this;
}

inline void mat4x::show()
{
  __m256 zx[2] = { __a, __b };

  for ( __m256 v : zx )
  {
    printf( "%f | %f | %f | %f \n", v[0], v[0 + 1], v[0 + 2], v[0 + 3] );
    printf( "%f | %f | %f | %f \n", v[4], v[4 + 1], v[4 + 2], v[4 + 3] );
  }

  printf( "\n" );
}

// Very heavily based from the Java Joml Library:
void mat4x::doRot( float ang )
{
  float sin = glm::sin( ang );
  float cos = glm::sin( sin + ( glm::pi<float>() * 0.5F ) );
  //__a       = _mm256_mul_ps( __a, __b );

  __a[0] = std::fma( __a[0], cos, sin );
  __a[1] = std::fma( __a[1], cos, -cos );
  // __a[2] = std::fma( __a[7], sin, 0 );
  // __a[3] = std::fma( __a[3], cos, __a[7] );
  //           __a[1](std::fma(a2, cos, v1 * sin))
  __a[4] = std::fma( __a[1], -sin, cos );
  __a[5] = std::fma( __a[2], -sin, cos );
  __a[6] = std::fma( __a[2], -sin, __a[2] * cos );
  __a[7] = std::fma( __a[3], -sin, __a[3] * cos );
  // __a[4] = cos;
  // __a[0] = -sin;
  // __a[5] = sin;
  // __a[1] = cos;
  //__a[6] = 0;
}