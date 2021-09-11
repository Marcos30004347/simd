#ifndef SIMD_ANDROID_PLATFORM_H
#define SIMD_ANDROID_PLATFORM_H

#if defined(__ANDROID__)

#define SIMD_ANDROID_PLATFORM 1

#include <cpu-features.h>

void simd_setup()
{
    support_neon    = android_getCpuFeatures() & ANDROID_CPU_ARM_FEATURE_NEON);
    support_avx     = false;
    support_avx2    = false;
    support_avx512  = false;
    support_sse     = false;
    support_sse2    = false;
    support_sse3    = false;
    support_ssse3   = false;
    support_sse4_1  = false;
    support_sse4_2  = false;
}

#endif
#endif
