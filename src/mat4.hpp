#define __SCE__ 1
#define __IMMINTRIN_H 1
#define __FMAINTRIN_H 1
// #define _HAS_CXX20 1
//#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <avxintrin.h>
#include <avx2intrin.h>
#include <fmaintrin.h>
#include <stdint.h>
#include <memory>
/*
    Have to include Pragma Guards Directly as VSCode is Dumb and dosent Know/verify that the Host/Currently Utilsied/Subejtc>Applicable/Accessib;e CPU does and cas in aftc support AVX/AVX2+FMA3 correctly
    * howver this is an issue that mostly effects the Lexical Analysis/IDE Analysis  and Thnakfully therefore  does not effect the compilation process or the executable Bianry in any tanigble or averse way manner or degree pr tanigble edtend or manner or way According to current Knwleadge.Understainding/Ascertainations
    */


//typedef __builtin_ia32_vfmaddps256 _mm256_fmadd_ps  ;

//too lazy to do an SSE version as AVX in many cases can allow for the abilkity to the same steps in half as many stages.steps/procedures/Instructions/Operations e.g. .etc i.e..Misc Visa. versa.
//Might be able to get away withput using amore explict construct arg sets and isntead just implicitly and Automatically intialise the struct iwth a constexpr Identify Maxtrix Struct.Blob/StandIn Instead

struct mat4
{
private:
    static inline constexpr float ax[16] =
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
     };
public:    
    explicit mat4()
    {
         mat4::__a=_mm256_castsi256_ps(lud(ax));
         mat4::__b=_mm256_castsi256_ps(lud(ax+8));
    }

    float a[2][8];
    __m256 __a;
    __m256 __b;
    __m256 __c;
    inline const __m256 lud(const void* a);
    inline void domatFMA(mat4*, __m256);
    inline void domatFMA(mat4*);
    
    inline void loadAligned(float a[16]);
    inline void loadAligned(const void* a);
    inline constexpr mat4* identity();
    inline void neg();
};

inline void mat4::loadAligned(float a[16])
{
    //_mm_storeu_si128((__m128*)aa, mat4::a);
    mat4::__a=_mm256_castsi256_ps(lud(a));
    mat4::__b=_mm256_castsi256_ps(lud(&a+8));

}
inline void mat4::loadAligned(const void* a)
{
    //_mm_storeu_si128((__m128*)aa, mat4::a);
    mat4::__a=_mm256_castsi256_ps(lud(a));
    mat4::__b=_mm256_castsi256_ps(lud(&a+8));
}
//Try to add a translation before Multiplying the matrix as an attempted Optimisation
inline void mat4::domatFMA(mat4 *b, __m256 __Trans)
{
// _mm256_fmadd_ps
    b->__a=__builtin_ia32_vfmaddps256(mat4::__a, b->__a, __Trans);
    b->__b=__builtin_ia32_vfmaddps256(mat4::__b, b->__b, __Trans);

}
inline void mat4::domatFMA(mat4 *b)
{
// _mm256_fmadd_ps
    b->__a=__builtin_ia32_vfmaddps256(mat4::__a, b->__a, __c);
    b->__b=__builtin_ia32_vfmaddps256(mat4::__b, b->__b, __c);

}
//Hide ugly casting syntax for aligned load as un;ike the AVX512 intrinsics provided by intel, man Load/many intrisics Functions do not include Void* by default as an Argument
inline const __m256 mat4::lud(const void* a)
{
    return _mm256_load_si256(reinterpret_cast<const __m256i*>((a)));
}

inline constexpr mat4* mat4::identity()
{
    loadAligned((ax));
    return this;
}

inline void mat4::neg()
{
    __a=_mm256_andnot_si256(__a,__b);
    __b=_mm256_andnot_si256(__b,__a);
}