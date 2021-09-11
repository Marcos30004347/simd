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
    
    // printf("%f %f %f %f\n", b[0], b[1], b[2], b[3]);


    begin = std::chrono::steady_clock::now();
    for(int i = 0; i < 100000; i++)
    {
        b = _mm_add_ps(a, b);
    }
    end = std::chrono::steady_clock::now();
    printf("%lu\n", std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count());
    // printf("%f %f %f %f\n", b[0], b[1], b[2], b[3]);

    return 0;
}