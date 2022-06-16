#pragma once


/*
 *  Could do an SSE version but in mroe recent CPU SKUs AVX/AVX2 is much mroe well supported auto of specici pentium[s] 
    and a smany Games/Applicbals also ship with AVX and do not always botehr to check for proper/approaote instruction set support anyway 
    SSE is not a Primary/Major perogative or concer at this Point.Stage
*/

// #include <array>
#include "glm/ext/matrix_float4x4.hpp"
#include <immintrin.h>

struct [[gnu::aligned(64)]] mat4x
{
public:
  __m256 __a = _mm256_set_ps(1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F);
  __m256 __b = _mm256_set_ps(0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F );


   __m256 lud( const float[] ) const __attribute__( ( __aligned__( sizeof( __m256 ) ) ) );

   constexpr void    toAddress(const __m256* a );
   void    loadAligned( const glm::mat4x4 &a ) __attribute__( ( preserve_most ) );
   void    loadAligned( const mat4x * a ) __attribute__( ( preserve_most ) );
   void    doPerspective( float, float, float, float );
  ;
}; 

