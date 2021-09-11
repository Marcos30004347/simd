#ifndef FLOAT_4_H
#define FLOAT_4_H

#include "runtime.hpp"

#define FLOAT4 1

#if defined(INC_SSE) || defined(INC_SSE2) || defined(INC_SSE3) || defined(INC_SSE4_1) || defined(INC_SSE4_2) || defined(INC_SSSE3)

#define FLOAT4_SSE 1

#define float4_get(v,i) _mm_cvtss_f32(_mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, i)))

typedef __m128 float4;

float4 float4_load(float a, float b, float c, float d)
{
    return _mm_set_ps(a, b, c, d);
}

float4 float4_load(float* a)
{
    return _mm_loadu_ps(a);
}

void float4_store(float4 v, float* a)
{
    _mm_storeu_ps(a, v);
}

void float4_store(float4 v, float* a, float* b, float* c, float* d)
{
    *a = float4_get(v, 0);
    *b = float4_get(v, 1);
    *c = float4_get(v, 2);
    *d = float4_get(v, 3);
}

#else

#define FLOAT4_NAIVE 1

typedef struct float4
{
    float v[4];
} float4;

#define float4_get(v,i) v.v[i]

float4 float4_load(float a, float b, float c, float d)
{
    float4 v;

    v.v[0] = a;
    v.v[1] = b;
    v.v[2] = c;
    v.v[3] = d;

    return v;
}

float4 float4_load(float* a)
{
    float4 v;

    v.v[0] = a[0];
    v.v[1] = a[1];
    v.v[2] = a[2];
    v.v[3] = a[3];

    return v;
}

void float4_store(float4 v, float* a)
{
    a[0] = v.v[0];
    a[1] = v.v[1];
    a[2] = v.v[2];
    a[3] = v.v[3];
}

void float4_stroe(float4 v, float* a, float* b, float* c, float* d)
{
    *a = v.v[0];
    *b = v.v[1];
    *c = v.v[2];
    *d = v.v[3];
}

#endif

#endif