#ifndef SIMD_RUNTIME
#define SIMD_RUNTIME

static bool support_neon    = false;
static bool support_avx     = false;
static bool support_avx2    = false;
static bool support_avx512  = false;
static bool support_sse     = false;
static bool support_sse2    = false;
static bool support_sse3    = false;
static bool support_ssse3   = false;
static bool support_sse4_1  = false;
static bool support_sse4_2  = false;

void  simd_setup();
void* simd_resolve_addr(const char* name);

// Include Linux specifics
#if defined(__unix__) || defined(__linux__) || defined(_POSIX_VERSION) || (defined(__APPLE__) && defined(TARGET_OS_MAC))
    #include "platforms/linux.hpp"
#endif

// Include Windows specifics
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include "platforms/windows.hpp"
#endif

// Include Android specifics
#if defined(__ANDROID__)
    #include "platforms/android.hpp"
#endif

#include "intrinsics.hpp"

#ifndef simd_func
    #define simd_func
#endif


#endif
