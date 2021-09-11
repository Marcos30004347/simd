#include "simd/add.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <chrono>

std::chrono::steady_clock::time_point begin;
std::chrono::steady_clock::time_point end;

static void (*add_f4)(float*, float*, float*);

int main()
{
    add_f4 = (void (*)(float*, float*, float*))resolve_add_floatx4();
    
    float a[4] = { 1.0, 1.0, 1.0, 1.0 };
    float b[4] = { 0.0, 0.0, 0.0, 0.0 };
    
    float c[4] = { 1.0, 1.0, 1.0, 1.0 };
    float d[4] = { 0.0, 0.0, 0.0, 0.0 };
    
    float e[4] = { 1.0, 1.0, 1.0, 1.0 };
    float f[4] = { 0.0, 0.0, 0.0, 0.0 };

    begin = std::chrono::steady_clock::now();
    for(int i = 0; i < 10000000; i++)
    {
        add_float4_naive(a, b, b);
    }

    end = std::chrono::steady_clock::now();
    printf("%lu\n", std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count());
    printf("%f %f %f %f\n", b[0], b[1], b[2], b[3]);

    begin = std::chrono::steady_clock::now();
    for(int i = 0; i < 10000000; i++)
    {
        add_f4(c, d, d);
    }
    end = std::chrono::steady_clock::now();
    printf("%lu\n", std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count());
    printf("%f %f %f %f\n", d[0], d[1], d[2], d[3]);

    begin = std::chrono::steady_clock::now();
    for(int i = 0; i < 10000000; i++)
    {
        __m128 _i = _mm_load_ps(e);
        __m128 _k = _mm_load_ps(f);
        __m128 _j = _mm_add_ps(_i, _k);
        _mm_store_ps(f, _j);
    }
    end = std::chrono::steady_clock::now();
    printf("%lu\n", std::chrono::duration_cast<std::chrono::microseconds> (end - begin).count());
    printf("%f %f %f %f\n", f[0], f[1], f[2], f[3]);

    return 0;
}