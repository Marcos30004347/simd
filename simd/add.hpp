#ifndef SIMD_ADD_H
#define SIMD_ADD_H

#include "runtime.hpp"

#include "float4.hpp"
#include "float8.hpp"
#include "float16.hpp"

#include <stdio.h>

float4 (*float4_add)(float4, float4);
float8 (*float8_add)(float8, float8);
float16(*float16_add)(float16, float16);

simd_func float4 float4_add_sse(float4 i, float4 k)
{
    #if FLOAT4_SSE
    return _mm_add_ps(i, k);
    #endif

    // to prevent compile warnings
    return float4_load(0,0,0,0);
}

// extern "C" {

// static float4 (*resolve_float4_add_sse (void)) (float4, float4) 
// {
//     return float4_add_sse; 
// }

// }
// float4 _float4_add(float4, float4) __attribute__ ((ifunc ("resolve_float4_add_sse")));;

simd_func float4 float4_add_naive(float4 i, float4 k)
{
    #if FLOAT4_NAIVE
    
    float4 j;
    
    j.v[0] = i.v[0] + k.v[0];
    j.v[1] = i.v[1] + k.v[1];
    j.v[2] = i.v[2] + k.v[2];
    j.v[3] = i.v[3] + k.v[3];

    return j;
    #endif

    // to prevent compile warnings
    return float4_load(0,0,0,0);
}

simd_func void resolve_add_floatx4()
{
    #if defined(INC_SSE) || defined(INC_SSE2) || \
        defined(INC_SSE3) || defined(INC_SSE4_1) || \
        defined(INC_SSE4_2) || defined(INC_SSSE3)

    if(support_sse) 
    {
        float4_add = (float4 (*)(float4, float4))simd_resolve_addr("float4_add_sse");
        return;
    }
    
    #endif
    
    float4_add = (float4 (*)(float4, float4))float4_add_naive;
}




simd_func float8 float8_add_avx(float8 i, float8 k)
{
    #if FLOAT8_AVX
    return _mm256_add_ps(i, k);
    #endif

    // to prevent compile warnings
    return float8_load(0,0,0,0,0,0,0,0);
}

simd_func float8 float8_add_sse(float8 i, float8 k)
{
    #if FLOAT8_SSE
    
    float8 j;

    j.v[0] = float4_add_sse(i.v[0], k.v[0]);
    j.v[1] = float4_add_sse(i.v[1], k.v[1]);
    
    return j; 
    
    #endif

    // to prevent compile warnings
    return float8_load(0,0,0,0,0,0,0,0);
}

simd_func float8 float8_add_naive(float8 i, float8 k)
{
    #if FLOAT8_NAIVE

    float8 j;

    j.v[0] = i.v[0] + k.v[0];
    j.v[1] = i.v[1] + k.v[1];
    j.v[2] = i.v[2] + k.v[2];
    j.v[3] = i.v[3] + k.v[3];
    j.v[4] = i.v[4] + k.v[4];
    j.v[5] = i.v[5] + k.v[5];
    j.v[6] = i.v[6] + k.v[6];
    j.v[7] = i.v[7] + k.v[7];

    #endif

    // to prevent compile warnings
    return float8_load(0,0,0,0,0,0,0,0);
}

simd_func void resolve_add_floatx8()
{
    #if INC_AVX
    if(support_avx)
    {
        float8_add = (float8 (*)(float8, float8))simd_resolve_addr("float8_add_avx");
        return;
    } 
    #endif
 
    #if INC_SSE
    if(support_sse)
    {
        float8_add = (float8 (*)(float8, float8))simd_resolve_addr("float8_add_sse");
        return;
    } 
    #endif
 
    float8_add = (float8 (*)(float8, float8))float8_add_naive;
}







simd_func float16 float16_add_avx512(float16 i, float16 k)
{
    #if FLOAT16_AVX512

    return _mm512_add_ps(i, k);

    #endif

    // to prevent compile warnings
    return float16_load(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
}

simd_func float16 float16_add_avx(float16 i, float16 k)
{
    #if FLOAT16_AVX

    float16 j;

    j.v[0] = float8_add_avx(i.v[0], k.v[0]);
    j.v[1] = float8_add_avx(i.v[1], k.v[1]);
    
    return j; 

    #endif

    // to prevent compile warnings
    return float16_load(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
}

simd_func float16 float16_add_sse(float16 i, float16 k)
{
    #if FLOAT16_SSE
    
    float16 j;

    j.v[0] = float4_add_sse(i.v[0], k.v[0]);
    j.v[1] = float4_add_sse(i.v[1], k.v[1]);
    j.v[2] = float4_add_sse(i.v[2], k.v[2]);
    j.v[3] = float4_add_sse(i.v[3], k.v[3]);

    return j; 
    
    #endif

    // to prevent compile warnings
    return float16_load(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
}

simd_func float16 float16_add_naive(float16 i, float16 k)
{
    #if FLOAT16_NAIVE
    float8 j;

    j.v[0] = i.v[0] + k.v[0];
    j.v[1] = i.v[1] + k.v[1];
    j.v[2] = i.v[2] + k.v[2];
    j.v[3] = i.v[3] + k.v[3];
    j.v[4] = i.v[4] + k.v[4];
    j.v[5] = i.v[5] + k.v[5];
    j.v[6] = i.v[6] + k.v[6];
    j.v[7] = i.v[7] + k.v[7];
    j.v[8] = i.v[8] + k.v[8];
    j.v[9] = i.v[9] + k.v[9];
    j.v[10] = i.v[10] + k.v[10];
    j.v[11] = i.v[11] + k.v[11];
    j.v[12] = i.v[12] + k.v[12];
    j.v[13] = i.v[13] + k.v[13];
    j.v[14] = i.v[14] + k.v[14];
    j.v[15] = i.v[15] + k.v[15];

    return j;

    #endif

    // to prevent compile warnings
    return float16_load(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);
}

simd_func void resolve_add_floatx16()
{
    #if INC_AVX512
    if(support_avx512) 
    {
        float16_add = (float16 (*)(float16, float16))simd_resolve_addr("float16_add_avx512");
        return;
    }
    #endif
 
    #if INC_AVX
    if(support_avx)
    {
        float16_add = (float16 (*)(float16, float16))("float16_add_avx");
        return;
    }
    #endif
 
    #if INC_SSE
    if(support_sse) 
    {
        float16_add = (float16 (*)(float16, float16))("float16_add_sse");
        return;
    }
    #endif
 
    float16_add = (float16 (*)(float16, float16))float16_add_naive;
}

#endif