#include "simd/add.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <chrono>

std::chrono::steady_clock::time_point begin;
std::chrono::steady_clock::time_point end;

int main()
{
    simd_setup();
    resolve_add_floatx4();
    
    float4 a = float4_load(1.0, 2.0, 3.0, 4.0);
    float4 b = float4_load(0.0, 0.0, 0.0, 0.0);
    
    begin = std::chrono::steady_clock::now();
    for(int i = 0; i < 100000; i++)
    {
        b = float4_add(a, b);
    }
    end = std::chrono::steady_clock::now();
    printf("%lu\n", std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count());
    printf("%f %f %f %f\n", float4_get(b, 0),float4_get(b, 1), float4_get(b, 2), float4_get(b, 3));
    

    begin = std::chrono::steady_clock::now();
    __m128 _a = _mm_set_ps(1, 2, 3, 4);
    __m128 _b = _mm_set_ps(0, 0, 0, 0);
    for(int i = 0; i < 100000; i++)
    {
        _b = _mm_add_ps(_a, _b);
    }
    end = std::chrono::steady_clock::now();
    printf("%lu\n", std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count());
    printf("%f %f %f %f\n", float4_get(_b, 0),float4_get(_b, 1), float4_get(_b, 2), float4_get(_b, 3));


    begin = std::chrono::steady_clock::now();

    float __a[4] = {1, 2, 3, 4};
    float __b[4] = {0, 0, 0, 0};

    for(int i = 0; i < 100000; i++)
    {
        __b[0] = __a[0] + __b[0];
        __b[1] = __a[1] + __b[1];
        __b[2] = __a[2] + __b[2];
        __b[3] = __a[3] + __b[3];
    }
    
    end = std::chrono::steady_clock::now();
    
    printf("%lu\n", std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count());
    
    printf("%f %f %f %f\n", __b[0], __b[1], __b[2], __b[3]);
    

    return 0;
}