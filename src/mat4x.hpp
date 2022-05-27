#pragma once


/*
 *too lazy to do an SSE version as AVX in many cases can allow for the ability to the same steps in half as many stages
 */

// #include <array>
#include "glm/ext/matrix_float4x4.hpp"
#include <immintrin.h>
// constexpr float ax[]= {  };

struct mat4x
{
public:
  __m256 __a = _mm256_set_ps(1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F);
  __m256 __b = _mm256_set_ps(0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F );

  /* constexpr mat4x() : __a(  ), __b(  ) ) {} */
  // constexpr mat4x( const float * a ) : __a( __builtin_shufflevector()  ), __b( _mm256_load_ps(a + 8)  ) {}
  //  float a[2][8];

   __m256 lud( const float[] ) const __attribute__( ( __aligned__( sizeof( __m256 ) ) ) );
  //  void             domatFMA( mat4x * /*b*/, __m256 /*__Trans*/ );
  //  void             domatFMA( mat4x & /*b*/ );

   constexpr void    toAddress(const __m256* a );
  //  void    loadTmp( const float[] );
   void    loadAligned( const glm::mat4x4 &a ) __attribute__( ( preserve_most ) );
  //  mat4x   loadAlignedA( const void * a ) __attribute__( ( preserve_most ) );
   void    loadAligned( const mat4x * a ) __attribute__( ( preserve_most ) );
  //  mat4x * identity();
  //  void    neg();
  //  void    setPerspective( float, float, float, float, bool );
  //  mat4x   copyOf() __attribute__( ( pure ) );
  //  void    show();
  //  void    permute();
   void    doPerspective( float, float, float, float );
  //  void    doLook( float );
  //  void    rotateL( float const & /* , glm::vec3 const &  */ ) __attribute__( ( __aligned__( 32 ), hot, flatten ) );
  ;
} __attribute__((aligned(64)));

