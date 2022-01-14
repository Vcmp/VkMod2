#define __SCE__ 1
#define __IMMINTRIN_H 1
#define __FMAINTRIN_H 1
//#include <immintrin.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include <avxintrin.h>
#include <avx2intrin.h>
#include <fmaintrin.h>
#include <stdint.h>
/*
    Have to include Pragma Guards Directly as VSCode is Dumb and dosent Know/verify that the Host/Currently Utilsied/Subejtc>Applicable/Accessib;e CPU does and cas in aftc support AVX/AVX2+FMA3 correctly
    * howver this is an issue that mostly effects the Lexical Analysis/IDE Analysis  and Thnakfully therefore  does not effect the compilation process or the executable Bianry in any tanigble or averse way manner or degree pr tanigble edtend or manner or way According to current Knwleadge.Understainding/Ascertainations
    */


//typedef __builtin_ia32_vfmaddps256 _mm256_fmadd_ps  ;

//too lazy to do an SSE version as AVX in many cases can allow for the abilkity to the same steps in half as many stages.steps/procedures/Instructions/Operations e.g. .etc i.e..Misc Visa. versa.
struct mat4
{
    explicit mat4(float a[16])
    {
         mat4::__a=_mm256_castsi256_ps(_mm256_load_si256((__m256i*)a));
         mat4::__b=_mm256_castsi256_ps(_mm256_load_si256((__m256i*)a+8));
    }
float a[2][8];
 __m256 __a;
 __m256 __b;
 __m256 __c;
inline void domatFMA(mat4*);
    
    inline void loadAligned(float a[16]);
    inline void loadAligned(mat4* a);
};

inline void mat4::loadAligned(float a[16])
{
    //_mm_storeu_si128((__m128*)aa, mat4::a);
    mat4::__a=_mm256_castsi256_ps(_mm256_load_si256((__m256i*)a));
    mat4::__b=_mm256_castsi256_ps(_mm256_load_si256((__m256i*)a+8));
}
inline void mat4::loadAligned(mat4* a)
{
    //_mm_storeu_si128((__m128*)aa, mat4::a);
    mat4::__a=_mm256_castsi256_ps(_mm256_load_si256((__m256i*)a));
    mat4::__b=_mm256_castsi256_ps(_mm256_load_si256((__m256i*)a+8));
}

inline void mat4::domatFMA(mat4 *b)
{
// _mm256_fmadd_ps
    b->__a=__builtin_ia32_vfmaddps256(mat4::__a, b->__a, mat4::__c);
    b->__b=__builtin_ia32_vfmaddps256(mat4::__b, b->__b, mat4::__c);

}