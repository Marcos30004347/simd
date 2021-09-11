#ifndef FLOAT8_H
#define FLOAT8_H

#include "runtime.hpp"

#include "float4.hpp"

#define FLOAT8 1

#if defined(INC_AVX) || defined(INC_AVX2) 

#define FLOAT8_AVX 1

typedef __m256 float8;

float float8_get(__m256 a, int i){
    float ret = 0;

    switch (i)
    {
        case 0:
        {
            ret = _mm_cvtss_f32(_mm256_extractf128_ps(a, 0));
        }
            break;
        case 1: 
        {
            __m128 lo = _mm256_extractf128_ps(a, 0);
            ret = _mm_cvtss_f32(_mm_shuffle_ps(lo, lo, 1));
        }
            break;
        case 2: 
        {
            __m128 lo = _mm256_extractf128_ps(a, 0);
            ret = _mm_cvtss_f32(_mm_movehl_ps(lo, lo));
        }
            break;
        case 3: 
        {
            __m128 lo = _mm256_extractf128_ps(a, 0);                    
            ret = _mm_cvtss_f32(_mm_shuffle_ps(lo, lo, 3));
        }
            break;

        case 4:
        {
            ret = _mm_cvtss_f32(_mm256_extractf128_ps(a, 1));
        }
            break;
        case 5: 
        {
            __m128 hi = _mm256_extractf128_ps(a, 1);
            ret = _mm_cvtss_f32(_mm_shuffle_ps(hi, hi, 1));
        }
            break;
        case 6: 
        {

            __m128 hi = _mm256_extractf128_ps(a, 1);
            ret = _mm_cvtss_f32(_mm_movehl_ps(hi, hi));
        }
            break;
        case 7: 
        {
            __m128 hi = _mm256_extractf128_ps(a, 1);
            ret = _mm_cvtss_f32(_mm_shuffle_ps(hi, hi, 3));
        }
            break;
    }

    return ret;
}

float8 float8_load(float a, float b, float c, float d, float e, float f, float g, float h)
{
    return _mm256_set_ps(a, b, c, d, e, f, g, h);
}

float8 float8_load(float* a)
{
    return _mm256_loadu_ps(a);
}

void float8_store(float8 v, float* a)
{
    _mm256_storeu_ps(a, v);
}

void float8_store(float8 v, float* a, float* b, float* c, float* d, float* e, float *f, float *g, float* h)
{
    *a = float8_get(v, 0);
    *b = float8_get(v, 1);
    *c = float8_get(v, 2);
    *d = float8_get(v, 3);
    *e = float8_get(v, 4);
    *f = float8_get(v, 5);
    *g = float8_get(v, 6);
    *h = float8_get(v, 7);
}

#elif FLOAT4_SSE

#define FLOAT8_SSE 1

typedef struct float8
{
    float4 v[2];
} float8;

float8 float8_load(float a, float b, float c, float d, float e, float f, float g, float h)
{
    float8 v;
    v.v[0] = float4_load(a, b, c, d);
    v.v[1] = float4_load(e, f, g, h);
    return v;
}

float8 float8_load(float* a)
{
    float8 v;
    v.v[0] = float4_load(a);
    v.v[1] = float4_load(a + 4);
    return v;
}

void float8_store(float8 v, float* a)
{
    float4_store(v.v[0], a);
    float4_store(v.v[1], a + 4);
}

void float8_store(float8 v, float* a, float* b, float* c, float* d, float* e, float* f, float* g, float* h)
{
    float4_store(v.v[0], a, b, c, d);
    float4_store(v.v[1], e, f, g, h);
}

#else


#define FLOAT8_NAIVE 1

typedef struct float8
{
    float v[8];
} float8;

#define float8_get(v,i) v.v[i]

float8 float8_load(float a, float b, float c, float d, float e, float f, float g, float h)
{
    float8 v;

    v.v[0] = a;
    v.v[1] = b;
    v.v[2] = c;
    v.v[3] = d;
    v.v[4] = e;
    v.v[5] = f;
    v.v[6] = g;
    v.v[7] = h;

    return v;
}

float8 float8_load(float* a)
{
    float8 v;

    v.v[0] = a[0];
    v.v[1] = a[1];
    v.v[2] = a[2];
    v.v[3] = a[3];
    v.v[4] = a[4];
    v.v[5] = a[5];
    v.v[6] = a[6];
    v.v[7] = a[7];

    return v;
}

void float8_store(float8 v, float* a)
{
    a[0] = v.v[0];
    a[1] = v.v[1];
    a[2] = v.v[2];
    a[3] = v.v[3];
    a[4] = v.v[4];
    a[5] = v.v[5];
    a[6] = v.v[6];
    a[7] = v.v[7];
}

void float8_store(float8 v, float* a, float* b, float* c, float* d, float* e, float* f, float* g, float* h)
{
    *a = v.v[0];
    *b = v.v[1];
    *c = v.v[2];
    *d = v.v[3];
    *e = v.v[4];
    *f = v.v[5];
    *g = v.v[6];
    *h = v.v[7];
}


#endif
#endif