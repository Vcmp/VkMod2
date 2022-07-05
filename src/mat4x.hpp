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

struct [[gnu::aligned(64)]] mat4x
{
public:
  [[gnu::__const]] __m256 __a = {1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F};
  __m256 __b = {0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F };


  [[gnu::hot, gnu::pure]] __m256 lud( const float[] ) const __attribute__( ( __aligned__( sizeof( __m256 ) ) ) );
  [[gnu::hot, gnu::pure, gnu::const, gnu::aligned(64), clang::preserve_all, gnu::regcall]] constexpr auto operator=(auto  &__n) const -> float&;
  [[gnu::hot, gnu::pure, gnu::const, gnu::aligned(64), clang::preserve_all, gnu::regcall]] constexpr auto operator[](auto  __n) const noexcept -> float;
   constexpr void    toAddress(const __m256* a );
   void    loadAligned( const glm::mat4x4 &a ) __attribute__( ( preserve_most ) );
   void    loadAligned( const mat4x * a ) __attribute__( ( preserve_most ) );
   void    doPerspective( float, float, float, float );
   [[gnu::pure]]constexpr void    identity();
   [[gnu::pure]]constexpr void    zero();
  ;
}; 

constexpr auto mat4x::operator=(auto &__n) const -> float&
{
  float ax;
  assert(__n<16);
  if(__n<8) 
  {
    ax = this->__a[__n];
  } 
  else 
  {
   ax = this->__b[__n&7];
  }
  
  return *&ax;
  
}
constexpr auto mat4x::operator[](auto __n) const noexcept -> float
{
  assert(__n<16);
  if(__n<8) 
  {
    return this->__a[__n];
  } 
  else 
  {
   return this->__b[__n&7];
  }
}
constexpr void mat4x::identity()
{
   this->__a = __extension__ (__m256){1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F, 0.0F, 0.0F};
  this-> __b = __extension__ (__m256){0.0F, 0.0F, 1.0F, 0.0F, 0.0F, 0.0F, 0.0F, 1.0F };

}

constexpr void mat4x::zero()
{
   this->__a = _mm256_xor_ps(__a, __a);
  this-> __b = _mm256_xor_ps(__b, __b);

}