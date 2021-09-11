#ifndef SIMD_LINUX_PLATFORM_H
#define SIMD_LINUX_PLATFORM_H

#if defined(__unix__) || defined(__linux__) || defined(_POSIX_VERSION) || (defined(__APPLE__) && defined(TARGET_OS_MAC))

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#define SIMD_LINUX_PLATFORM 1

#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)

void simd_setup() {
    __builtin_cpu_init ();

    support_neon    = false;
    support_avx     = __builtin_cpu_supports("avx");
    support_avx2    = __builtin_cpu_supports("avx2");
    support_avx512  = __builtin_cpu_supports("avx512f");
    support_sse     = __builtin_cpu_supports("sse");
    support_sse2    = __builtin_cpu_supports("sse2");
    support_sse3    = __builtin_cpu_supports("sse3");
    support_ssse3   = __builtin_cpu_supports("ssse3");
    support_sse4_1  = __builtin_cpu_supports("sse4.1");
    support_sse4_2  = __builtin_cpu_supports("sse4.2");
}

#else

#error Unsuported compiler for the linux platform

#endif

void* simd_resolve_addr(const char* name)
{
    void* addr = dlsym(__null, name);

    if (!addr) { 
        fprintf(stderr, "%s\n", dlerror()); 
        exit (1); 
    };

    return addr;
}

#define simd_func extern "C" __attribute__((visibility("default")))

#endif

#endif