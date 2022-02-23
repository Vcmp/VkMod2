#pragma once

#include "UniformBufferObject.hpp"

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
  __v8sf __a;
  __v8sf __b;

public:
  constexpr explicit mat4x() : __a( lud( ax ) ), __b( lud( ax + 8 ) ) {}
  constexpr explicit mat4x( const void * a ) : __a( lud( (float *)a ) ), __b( lud( (float *)a + 8 ) ) {}
  // float a[2][8];

  inline constexpr __m256 lud( const float[] ) __attribute__( ( __aligned__( sizeof( __m256 ) ) ) );
  // inline constexpr __m256 __vectorcall lud( const void * a ) __attribute__( ( __aligned__( sizeof( __m256 ) ) ) );
  inline void           domatFMA( mat4x *, __m256 );
  inline constexpr void domatFMA( mat4x & );

  // inline constexpr void __vectorcall loadAligned( float a[16] );
  inline constexpr void __vectorcall loadTmp( const float[] );
  // inline void              loadAligned( mat4x ) __declspec( preserve_most );
  inline constexpr void    loadAligned( const void * a ) __attribute__( ( preserve_most ) );
  inline constexpr void    loadAligned( const mat4x * a ) __attribute__( ( preserve_most ) );
  inline constexpr mat4x * identity();
  inline void              neg();
  inline void              setPerspective( float, float, float, float, bool );
  inline constexpr mat4x   copyOf() __attribute__( ( pure ) );
  inline void              show();
  inline void              permute();
  inline void              doPerspective( float, float, float, float );
  inline void              doLook( float );
  inline void rotateL( float const /* , glm::vec3 const &  */ ) __attribute__( ( __aligned__( 32 ), hot, flatten ) );
  ;
} m4, m5, m6;

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
inline constexpr void mat4x::loadAligned( const mat4x * a )
{
  //_mm_storeu_si128((__m128*)aa, mat4x::a);
  mat4x::__a = a->__a;
  mat4x::__b = a->__b;

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
inline constexpr __m256 mat4x::lud( const float * a )
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
void mat4x::doPerspective( float fovy, float aspect, float zFar, float zNear )
{
  // assert( abs( aspect - std::numeric_limits<float>::epsilon() ) > static_cast<float>( 0 ) );

  float const tanHalfFovy = tan( fovy / static_cast<float>( 2 ) );

  __a[0] = 1 / ( aspect * tanHalfFovy );
  __a[5] = 1 / ( tanHalfFovy );
  __b[2] = zFar / ( zFar - zNear );
  __b[3] = 1;
  __b[6] = -( zFar * zNear ) / ( zFar - zNear );
  m6.doLook( 1 );
}

void mat4x::doLook( float a )
{
  // vec<3, T, Q> const f( normalize( center - eye ) );
  // vec<3, T, Q> const s( normalize( cross( up, f ) ) );
  // vec<3, T, Q> const u( cross( f, s ) );

  // Result[0][0] = s.x;
  // Result[1][0] = s.y;
  // Result[2][0] = s.z;
  // Result[0][1] = u.x;
  // Result[1][1] = u.y;
  __b[1] = 1;
  __a[2] = 2;
  __a[6] = 2;
  __b[3] = 2;
  __b[4] = -( 0.F * 2.F );
  __b[5] = -( 1.F * 2.F );
  __b[6] = -( 2.F * 2.F );
  // return Result;
}

inline void mat4x::rotateL( const float angle /* , const glm::vec3 & v */ )
{
  //   float const a = angle;
  float const c = glm::cos( angle );
  float const s = glm::sin( angle );

  // const float aa[4] = { c, s, -s, c };

  // // loadAligned( &m );

  // const __m128 x = _mm_broadcast_ss( &aa[0] );
  // const __m128 y = _mm_broadcast_ss( &aa[1] );

  // // __m256 z = _mm256_loadu2_m128( &aa[0], &aa[1] );
  // const float  t[4] = { viewproj1[0][0], viewproj1[0][1], viewproj1[0][2], viewproj1[0][3] };
  // const float  r[4] = { viewproj1[1][0], viewproj1[1][1], viewproj1[1][2], viewproj1[1][3] };
  // const __m128 x1   = _mm_broadcast_ss( t );
  // const __m128 y1   = _mm_broadcast_ss( r );
  // __m128       v    = _mm_fmadd_ps( x1, x, _mm_mul_ps( y1, y ) );
  // __m128       v1   = _mm_fmadd_ps( x1, -y, _mm_mul_ps( y1, x ) );

  // __a = _mm256_loadu2_m128( reinterpret_cast<float *>( &v ), reinterpret_cast<float *>( &v1 ) );
  // __a = _mm256_load_ps( ax );
  __m256 xc = _mm256_broadcast_ss( &c );
  __m256 xs = _mm256_broadcast_ss( &s );

  /*
    Oddly using
        __a[4] = m5.__a[4] * -c + m5.__a[0] * s; Reverses the winding order
    comapired TO?Rleative to
    __a[4] = m5.__a[4] * c - m5.__a[0] * s;
  */

  __a[0] = m5.__a[0] * c + m5.__a[4] * s;
  __a[1] = m5.__a[1] * c + m5.__a[5] * s;
  __a[2] = m5.__a[2] * c + m5.__a[6] * s;
  __a[3] = m5.__a[3] * c + m5.__a[7] * s;

  __a[4] = m5.__a[4] - c * m5.__a[0] * s;
  __a[5] = m5.__a[5] - c * m5.__a[1] * s;
  __a[6] = m5.__a[6] - c * m5.__a[2] * s;
  __a[7] = m5.__a[7] - c * m5.__a[3] * s;

  // m5.__a[0] *= m5.__a[0];  __a[0] *= m5.__a[7];
  // m5.__a[1] *= m5.__a[1];   __a[1] *= m5.__a[6];
  // m5.__a[2] *= m5.__a[2];   __a[2] *= m5.__a[5];
  // m5.__a[3] *= m5.__a[3];   __a[3] *= m5.__a[4];
  // m5.__a[4] *= m5.__a[4];   __a[4] *= m5.__a[3];
  // m5.__a[5] *= m5.__a[5];   __a[5] *= m5.__a[2];
  // m5.__a[6] *= m5.__a[6];   __a[6] *= m5.__a[1];
  // m5.__a[7] *= m5.__a[7];   __a[7] *= m5.__a[0];

  _mm256_store_ps( reinterpret_cast<float *>( BuffersX::data ), __a );

  // __a = _mm256_mul_ps( __a; _mm256_broadcast_ss( aa ) );

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

  // const glm::mat2x4 Result{                                       // Rotate.transpos
  //                           viewproj1[0] * c + viewproj1[1] * s,  // + m[2] * Rotate[0][2];
  //                           viewproj1[0] * -s + viewproj1[1] * c
  // };  // + m[2] * Rotate[1][2];
  // Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
  // Result[3] = m[3];

  // loadAligned( &Result );
}