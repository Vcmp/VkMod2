#pragma once


/*
 *too lazy to do an SSE version as AVX in many cases can allow for the ability to the same steps in half as many stages
 */

#include <immintrin.h>
#include <initializer_list>
static constexpr auto ax= { 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F };

struct mat4x
{
public:
  __m256 __a = lud( ax.begin() );
  __m256 __b = lud( ax.begin() + 8);

  /* constexpr mat4x() : __a(  ), __b(  ) ) {} */
  explicit constexpr  mat4x( auto * a ) : __a( lud( (float *)a ) ), __b( lud( (float *)a + 8 ) ) {}
  //  float a[2][8];

   constexpr __m256 lud( const float[] ) __attribute__( ( __aligned__( sizeof( __m256 ) ) ) );
   void             domatFMA( mat4x * /*b*/, __m256 /*__Trans*/ );
   void             domatFMA( mat4x & /*b*/ );

   constexpr void    toAddress(const __m256* a );
   void    loadTmp( const float[] );
   void    loadAligned( const void * a ) __attribute__( ( preserve_most ) );
   mat4x   loadAlignedA( const void * a ) __attribute__( ( preserve_most ) );
   void    loadAligned( const mat4x * a ) __attribute__( ( preserve_most ) );
   mat4x * identity();
   void    neg();
   void    setPerspective( float, float, float, float, bool );
   mat4x   copyOf() __attribute__( ( pure ) );
   void    show();
   void    permute();
   void    doPerspective( float, float, float, float );
   void    doLook( float );
   void    rotateL( float const & /* , glm::vec3 const &  */ ) __attribute__( ( __aligned__( 32 ), hot, flatten ) );
  ;
} __attribute__((aligned(64)));


/*
 * Note* casting issues usually mostly only occur with the AVX2 instrincis function delcarations  available
 * and while teh AVX counterparts for floats also do not supprot void* they instead supprot *float insetad which is till a great/considerable improvement
 */
 constexpr __m256 mat4x::lud( const float * a )
{
  return *(const __m256 *)( ( ( a ) ) );
}