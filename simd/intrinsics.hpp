#ifndef SIMD_INTRINSICS_H
#define SIMD_INTRINSICS_H

#if defined(INC_SSE) || defined(__SSE__)
    #define INC_SSE 1
    #if defined(SIMD_WINDOWS_PLATFORM)
        #include <intrin.h>
    #else 
        #include <x86intrin.h>
    #endif
#endif

#if defined(INC_SSE2) || defined(__SSE2__)
    #define INC_SSE2 1
    #if defined(SIMD_WINDOWS_PLATFORM)
        #include <intrin.h>
    #elif defined(SIMD_LINUX_PLATFORM)
        #include <x86intrin.h>
    #endif
#endif

#if defined(INC_SSE3) || defined(__SSE3__)
    #define INC_SSE3 1
    #if defined(SIMD_WINDOWS_PLATFORM)
        #include <intrin.h>
    #elif defined(SIMD_LINUX_PLATFORM)
        #include <x86intrin.h>
    #endif
#endif

#if defined(INC_SSE4_1) || defined(__SSE4_1__)
    #define INC_SSE4_1 1
    #if defined(SIMD_WINDOWS_PLATFORM)
        #include <intrin.h>
    #elif defined(SIMD_LINUX_PLATFORM)
        #include <x86intrin.h>
    #endif
#endif

#if defined(INC_SSE4_2) || defined(__SSE4_2__)
    #define INC_SSE4_2 1
    #if defined(SIMD_WINDOWS_PLATFORM)
        #include <intrin.h>
    #elif defined(SIMD_LINUX_PLATFORM)
        #include <x86intrin.h>
    #endif
#endif

#if defined(INC_SSSE3) || defined(__SSSE3__)
    #define INC_SSSE3 1
    #if defined(SIMD_WINDOWS_PLATFORM)
        #include <intrin.h>
    #elif defined(SIMD_LINUX_PLATFORM)
        #include <x86intrin.h>
    #endif

#endif

#if defined(INC_AVX) || defined(__AVX__)
    #define INC_AVX 1
    #if defined(SIMD_WINDOWS_PLATFORM)
        #include <intrin.h>
    #elif defined(SIMD_LINUX_PLATFORM)
        #include <x86intrin.h>
    #endif

#endif

#if defined(INC_AVX2) || defined(__AVX2__)
    #define INC_AVX2 1
    #if defined(SIMD_WINDOWS_PLATFORM)
        #include <intrin.h>
    #elif defined(SIMD_LINUX_PLATFORM)
        #include <x86intrin.h>
    #endif
#endif


#if defined(INC_AVX512) || defined(__AVX512__)
    #define INC_AVX512 1
    #if defined(SIMD_WINDOWS_PLATFORM)
        #include <intrin.h>
    #elif defined(SIMD_LINUX_PLATFORM)
        #include <x86intrin.h>
    #endif
#endif

#if defined(INC_NEON) || defined(__ARM_NEON__)
    #define INC_NEON 1
    #include <arm_neon.h>
#endif

#endif
