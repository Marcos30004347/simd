#ifndef FLOAT16_H
#define FLOAT16_H

#include "runtime.hpp"

#include "float4.hpp"
#include "float8.hpp"

#define FLOAT16 1

#if defined(INC_AVX512)

#define FLOAT16_AVX512 1

#define float16_get(v,i) _mm512_cvtss_f32(_mm512_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, i)))

typedef __m512 float16;

float16 float16_load(
    float a, float b, float c, float d, float e, float f, float g, float h,
    float i, float j, float k, float l, float m, float n, float o, float p
)
{
    return _mm512_set_ps(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
}

float16 float16_load(float* a)
{
    return _mm512_loadu_ps(a);
}

void float16_store(float16 v, float* a)
{
    _mm512_storeu_ps(a, v);
}

void float16_store(
    float16 v, 
    float* a, float* b, float* c, float* d, float* e, float *f, float *g, float* h,
    float* i, float* j, float* k, float* l, float* m, float *n, float *o, float* p
)
{
    *a = float16_get(v, 0);
    *b = float16_get(v, 1);
    *c = float16_get(v, 2);
    *d = float16_get(v, 3);
    *e = float16_get(v, 4);
    *f = float16_get(v, 5);
    *g = float16_get(v, 6);
    *h = float16_get(v, 7);
    *i = float16_get(v, 8);
    *j = float16_get(v, 9);
    *k = float16_get(v, 10);
    *l = float16_get(v, 11);
    *m = float16_get(v, 12);
    *n = float16_get(v, 13);
    *o = float16_get(v, 14);
    *p = float16_get(v, 15);
}

#elif FLOAT8_AVX

#define FLOAT16_AVX 1

typedef struct float16
{
    float8 v[2];
} float16;


float16 float16_load(
    float a, float b, float c, float d, float e, float f, float g, float h,
    float i, float j, float k, float l, float m, float n, float o, float p
)
{
    float16 v;
    v.v[0] = float8_load(a, b, c, d, e, f, g, h);
    v.v[1] = float8_load(i, j, k, l, m, n, o, p);
    return v;
}

float16 float16_load(float* a)
{
    float16 j;
    j.v[0] = float8_load(a);
    j.v[1] = float8_load(a + 8);
    return j;
}

void float16_store(float16 v, float* a)
{
    float8_store(v.v[0], a);
    float8_store(v.v[1], a + 8);
}

void float16_store(
    float16 v, 
    float* a, float* b, float* c, float* d, float* e, float *f, float *g, float* h,
    float* i, float* j, float* k, float* l, float* m, float *n, float *o, float* p
)
{
    float8_store(v.v[0], a, b, c, d, e, f, g, h);
    float8_store(v.v[1], i, j, k, l, m, n, o, p);
}


#elif FLOAT4_SSE

#define FLOAT16_SSE 1

typedef struct float16
{
    float4 v[4];
} float16;


float16 float16_load(
    float a, float b, float c, float d, float e, float f, float g, float h,
    float i, float j, float k, float l, float m, float n, float o, float p
)
{
    float16 v;

    v.v[0] = float4_load(a, b, c, d);
    v.v[1] = float4_load(e, f, g, h);
    v.v[2] = float4_load(i, j, k, l);
    v.v[3] = float4_load(m, n, o, p);

    return v;
}

float16 float16_load(float* a)
{
    float16 v;
    
    v.v[0] = float4_load(a);
    v.v[1] = float4_load(a + 4);
    v.v[2] = float4_load(a + 8);
    v.v[3] = float4_load(a + 12);
    
    return v;
}

void float16_store(float16 v, float* a)
{
    float4_store(v.v[0], a);
    float4_store(v.v[1], a + 4);
    float4_store(v.v[1], a + 8);
    float4_store(v.v[1], a + 12);
}

void float16_store(
    float16 v, 
    float* a, float* b, float* c, float* d, float* e, float *f, float *g, float* h,
    float* i, float* j, float* k, float* l, float* m, float *n, float *o, float* p
)
{
    float4_store(v.v[0], a, b, c, d);
    float4_store(v.v[1], e, f, g, h);
    float4_store(v.v[2], i, j, k, l);
    float4_store(v.v[3], m, n, o, p);
}

#else

#define FLOAT16_NAIVE 1

typedef struct float16
{
    float v[16];
} float16;

#define float16_get(v,i) v.v[i]

float8 float16_load(
    float a, float b, float c, float d, float e, float f, float g, float h,
    float i, float j, float k, float l, float m, float n, float o, float p
)
{
    float16 v;

    v.v[0] = a;
    v.v[1] = b;
    v.v[2] = c;
    v.v[3] = d;
    v.v[4] = e;
    v.v[5] = f;
    v.v[6] = g;
    v.v[7] = h;
    v.v[8] = i;
    v.v[9] = j;
    v.v[10] = k;
    v.v[11] = l;
    v.v[12] = m;
    v.v[13] = n;
    v.v[14] = o;
    v.v[15] = p;

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
    v.v[8] = a[8];
    v.v[9] = a[9];
    v.v[10] = a[10];
    v.v[11] = a[11];
    v.v[12] = a[12];
    v.v[13] = a[13];
    v.v[14] = a[14];
    v.v[15] = a[15];

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
    a[8] = v.v[8];
    a[9] = v.v[9];
    a[10] = v.v[10];
    a[11] = v.v[11];
    a[12] = v.v[12];
    a[13] = v.v[13];
    a[14] = v.v[14];
    a[15] = v.v[15];
}

void float8_store(
    float8 v, 
    float* a, float* b, float* c, float* d, float* e, float *f, float *g, float* h,
    float* i, float* j, float* k, float* l, float* m, float *n, float *o, float* p
)
{
    *a = v.v[0];
    *b = v.v[1];
    *c = v.v[2];
    *d = v.v[3];
    *e = v.v[4];
    *f = v.v[5];
    *g = v.v[6];
    *h = v.v[7];
    *i = v.v[8];
    *j = v.v[9];
    *k = v.v[10];
    *l = v.v[11];
    *m = v.v[12];
    *n = v.v[13];
    *o = v.v[14];
    *p = v.v[15];
}

#endif

#endif