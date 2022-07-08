#pragma once


/*
 *  Could do an SSE version but in more recent CPU SKUs AVX/AVX2 is much more well supported outside of specific pentium[s] 
    and as many Games/Applicbals also ship with AVX and do not always bother to check for proper/approaote instruction set support anyway 
    SSE is not a Primary/Major perogative or concer at this Point.Stage
*/

// #include <array>
#include "glm/ext/matrix_float4x4.hpp"
#include <cassert>
#include <cstdint>
#include <immintrin.h>

using __float512 [[gnu::vector_size(64)]] = float;



struct [[clang::trivial_abi, clang::vecreturn, gnu::aligned(64)]] mat4x
{
public:
  [[gnu::__const]] __float512 __ab = {1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F };


  [[gnu::hot, gnu::pure]] __m256 lud( const float[] ) const __attribute__( ( __aligned__( sizeof( __m256 ) ) ) );
  [[gnu::hot, gnu::pure, gnu::const, gnu::aligned(64), clang::preserve_all, gnu::regcall]] constexpr auto operator=(auto  &__n) const -> float&;
  [[gnu::hot, gnu::pure, gnu::const, gnu::aligned(64), clang::preserve_all, gnu::regcall]] constexpr __m128 operator[](auto  __n) noexcept;
   constexpr void    toAddress(const __m256* a );
   void    loadAligned( const glm::mat4x4 &a ) __attribute__( ( preserve_most ) );
   void    loadAligned( const mat4x * a ) __attribute__( ( preserve_most ) );
   void    doPerspective( float, float, float, float );
   [[gnu::pure]]constexpr void    identity();
   [[gnu::pure]]constexpr void    zero();
   [[gnu::pure]]auto    retCL(bool, uint8_t a);
   [[gnu::pure]]auto    retCLx2(bool, uint8_t cxl);
   [[gnu::pure]]auto    t(mat4x);
   [[gnu::pure]]auto    t2(mat4x);
   [[gnu::pure]]auto    retR(int c);
   [[gnu::pure]]auto    retC(int r);
   [[gnu::pure]]auto    retR2(uint8_t c);
   [[gnu::pure]]auto    retC2(int r);
  ;
}; 


constexpr __m128 mat4x::operator[](auto __n) noexcept
{
  assert(__n<4);
  {
    __n*=4;
    return __extension__(__m128){__ab[0+__n], __ab[1+__n], __ab[2+__n], __ab[3+__n]};
  } 

}

