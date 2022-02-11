#pragma once

#include "glm/ext/matrix_float2x2.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float4.hpp"
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
  inline void              rotateL( glm::mat4 const, float const /* , glm::vec3 const &  */ );
} m4;  //, m5, m6;

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
  // float s = glm::sin( ang );
  // float c = glm::sin( sin + ( glm::pi<float>() * 0.5F ) );
  //__a       = _mm256_mul_ps( __a, __b );

  // float const a = ang;
  // float const c = cos( a );
  // float const s = sin( a );

  // float axis[3] = { 0, 0, 1 };
  // float temp[3] = { 0, 0, ( 1 - c * axis[2] ) };

  // m6.__a[0] = c + temp[0] * axis[0];
  // m6.__a[1] = temp[0] * axis[1] + s * axis[2];
  // m6.__a[2] = temp[0] * axis[2] - s * axis[1];

  // m6.__a[4] = temp[1] * axis[0] - s * axis[2];
  // m6.__a[5] = c + temp[1] * axis[1];
  // m6.__a[6] = temp[1] * axis[2] + s * axis[0];

  // m6.__b[0] = temp[2] * axis[0] + s * axis[1];
  // m6.__b[1] = temp[2] * axis[1] - s * axis[0];
  // m6.__b[2] = c + temp[2] * axis[2];

  // m4.__a[0] = m5.__a[0] * m6.__a[0] + m5.__a[4] * m6.__a[1] + m5.__b[0] * m6.__a[2];
  // m4.__a[1] = m5.__a[0] * m6.__a[4] + m5.__a[4] * m6.__a[5] + m5.__b[0] * m6.__a[3];
  // m4.__a[2] = m5.__a[0] * m6.__b[0] + m5.__a[4] * m6.__b[1] + m5.__b[0] * m6.__b[2];
  // m4.__a[3] = m5.__b[4];
  // return m4.__a;
}

inline void mat4x::rotateL( const glm::mat4 m, const float angle /* , const glm::vec3 & v */ )
{
  //   float const a = angle;
  float const c = glm::cos( angle );
  float const s = glm::sin( angle );

  // constexpr glm::vec3 axis = { 0, 0, 1 };
  // glm::vec3           temp( ( float( 1 ) - c ) * axis );

  // glm::mat2 Rotate;
  // Rotate[0][0] = c;
  // Rotate[0][1] = s;
  // // Rotate[0][2] = 0;

  // Rotate[1][0] = -s;
  // Rotate[1][1] = c;
  // Rotate[1][2] = 0;

  // Rotate[2][0] = 0;
  // Rotate[2][1] = 0;
  // Rotate[2][2] = c + temp[2];

  const glm::vec4 Result[2]{                       // Rotate.transpos
                             m[0] * c + m[1] * s,  // + m[2] * Rotate[0][2];
                             m[0] * -s + m[1] * c
  };  // + m[2] * Rotate[1][2];
  // Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
  // Result[3] = m[3];

  loadAligned( &Result );
}