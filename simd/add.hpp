#include "runtime.hpp"

#include <stdio.h>

simd_h void add_float4_sse(float* i, float* k, float* j)
{
    #if INC_SSE
    __m128 _i = _mm_loadu_ps(i);
    __m128 _k = _mm_loadu_ps(k);
    __m128 _j = _mm_add_ps(_i, _k);
    _mm_storeu_ps(j, _j);
    #endif
}

simd_h void add_float4_naive(float* i, float* k, float* j)
{
    j[0] = i[0] + k[0]; j[1] = i[1] + k[1]; j[2] = i[2] + k[2]; j[3] = i[3] + k[3];
}

simd_h void add_float8_avx(float* i, float* k, float* j)
{
    #if INC_AVX
    __m256 _i = _mm256_loadu_ps(i);
    __m256 _k = _mm256_loadu_ps(k);
    __m256 _j = _mm256_add_ps(_i, _k);
    _mm256_storeu_ps(j, _j);
    #endif
}

simd_h void add_float8_sse(float* i, float* k, float* j)
{
    #if INC_SSE
    add_float4_sse(i, k, j);
    add_float4_sse(i + 4, k + 4, j + 4);
    #endif
}

simd_h void add_float8_naive(float* i, float* k, float* j)
{
    j[0] = i[0] + k[0]; j[1] = i[1] + k[1]; j[2] = i[2] + k[2]; j[3] = i[3] + k[3];
    j[4] = i[4] + k[4]; j[5] = i[5] + k[5]; j[6] = i[6] + k[6]; j[7] = i[7] + k[7];
}

simd_h void add_float16_avx2(float* i, float* k, float* j)
{
    #if INC_AVX
    __m512 _i = _mm512_loadu_ps(i);
    __m512 _k = _mm512_loadu_ps(k);
    __m512 _j = _mm512_add_ps(_i, _k);
    _mm512_storeu_ps(j, _j);
    #endif
}

simd_h void add_float16_avx(float* i, float* k, float* j)
{
    #if INC_SSE
    add_float8_avx(i, k, j);
    add_float8_avx(i + 8, k + 8, j + 8);
    #endif
}

simd_h void add_float16_sse(float* i, float* k, float* j)
{
    #if INC_SSE
    add_float8_sse(i, k, j);
    add_float8_sse(i + 8, k + 8, j + 8);
    #endif
}

simd_h void add_float16_naive(float* i, float* k, float* j)
{
    j[0] = i[0] + k[0]; j[1] = i[1] + k[1]; j[2] = i[2] + k[2]; j[3] = i[3] + k[3];
    j[4] = i[4] + k[4]; j[5] = i[5] + k[5]; j[6] = i[6] + k[6]; j[7] = i[7] + k[7];
    j[8] = i[8] + k[8]; j[9] = i[9] + k[9]; j[10] = i[10] + k[10]; j[11] = i[11] + k[11];
    j[12] = i[12] + k[12]; j[13] = i[13] + k[13]; j[14] = i[14] + k[14]; j[15] = i[15] + k[15];
}

simd_h void* resolve_add_floatx4()
{
    #if INC_SSE
    if(support_sse) return resolve_addr("add_float4_sse");
    #endif
    
    return (void*)add_float4_naive;
}

simd_h void* resolve_add_floatx8()
{
    #if INC_AVX
    if(support_avx) return resolve_addr("add_float8_avx");
    #endif
 
    #if INC_SSE
    if(support_sse) return resolve_addr("add_float8_sse");
    #endif
 
    return (void*)add_float8_naive;
}

simd_h void* resolve_add_floatx16()
{
    #if INC_AVX2
    if(support_avx2) return resolve_addr("add_float16_avx2");
    #endif
 
    #if INC_AVX
    if(support_avx) return resolve_addr("add_float16_avx");
    #endif
 
    #if INC_SSE
    if(support_sse) return resolve_addr("add_float16_sse");
    #endif
 
    return (void*)add_float16_naive;
}