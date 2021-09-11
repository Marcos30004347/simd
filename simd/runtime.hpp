#ifndef SIMD_RUNTIME
#define SIMD_RUNTIME

// Define Windows
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

#define SIMD_WINDOWS_PLATFORM

#endif

// Define Linux 
#if defined(__unix__) || defined(__linux__) || defined(_POSIX_VERSION) || (defined(__APPLE__) && defined(TARGET_OS_MAC))

#define SIMD_LINUX_PLATFORM

#endif


void* resolve_addr(const char* name);


// Define GCC and Clang static variables 
#if defined(__GNUC__) || defined(__GNUG__) || defined(__clang__)

static bool support_avx     = __builtin_cpu_supports("avx");
static bool support_avx2    = __builtin_cpu_supports("avx2");
static bool support_sse     = __builtin_cpu_supports("sse");
static bool support_sse2    = __builtin_cpu_supports("sse2");
static bool support_sse3    = __builtin_cpu_supports("sse3");
static bool support_ssse3   = __builtin_cpu_supports("ssse3");
static bool support_sse4_1  = __builtin_cpu_supports("sse4.1");
static bool support_sse4_2  = __builtin_cpu_supports("sse4.2");

#ifdef SIMD_LINUX_PLATFORM

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

void* resolve_addr(const char* name)
{
    void* addr = dlsym(__null, name);

    if (!addr) { 
        fprintf(stderr, "%s\n", dlerror()); 
        exit (1); 
    };

    return addr;
}

#endif

#endif


#if defined(_MSC_VER)

#include <windows.h>
#include <iostream>
#include <vector>
#include <bitset>
#include <array>
#include <string>
#include <intrin.h>


class InstructionSet
{
    class InstructionSet_Internal;

public:
    static std::string Vendor() { return CPU_Rep.vendor_; }
    static std::string Brand() { return CPU_Rep.brand_; }

    static bool SSE3() { return CPU_Rep.f_1_ECX_[0]; }
    static bool PCLMULQDQ() { return CPU_Rep.f_1_ECX_[1]; }
    static bool MONITOR() { return CPU_Rep.f_1_ECX_[3]; }
    static bool SSSE3() { return CPU_Rep.f_1_ECX_[9]; }
    static bool FMA() { return CPU_Rep.f_1_ECX_[12]; }
    static bool CMPXCHG16B() { return CPU_Rep.f_1_ECX_[13]; }
    static bool SSE41() { return CPU_Rep.f_1_ECX_[19]; }
    static bool SSE42() { return CPU_Rep.f_1_ECX_[20]; }
    static bool MOVBE() { return CPU_Rep.f_1_ECX_[22]; }
    static bool POPCNT() { return CPU_Rep.f_1_ECX_[23]; }
    static bool AES() { return CPU_Rep.f_1_ECX_[25]; }
    static bool XSAVE() { return CPU_Rep.f_1_ECX_[26]; }
    static bool OSXSAVE() { return CPU_Rep.f_1_ECX_[27]; }
    static bool AVX() { return CPU_Rep.f_1_ECX_[28]; }
    static bool F16C() { return CPU_Rep.f_1_ECX_[29]; }
    static bool RDRAND() { return CPU_Rep.f_1_ECX_[30]; }

    static bool MSR() { return CPU_Rep.f_1_EDX_[5]; }
    static bool CX8() { return CPU_Rep.f_1_EDX_[8]; }
    static bool SEP() { return CPU_Rep.f_1_EDX_[11]; }
    static bool CMOV() { return CPU_Rep.f_1_EDX_[15]; }
    static bool CLFSH() { return CPU_Rep.f_1_EDX_[19]; }
    static bool MMX() { return CPU_Rep.f_1_EDX_[23]; }
    static bool FXSR() { return CPU_Rep.f_1_EDX_[24]; }
    static bool SSE() { return CPU_Rep.f_1_EDX_[25]; }
    static bool SSE2() { return CPU_Rep.f_1_EDX_[26]; }

    static bool FSGSBASE() { return CPU_Rep.f_7_EBX_[0]; }
    static bool BMI1() { return CPU_Rep.f_7_EBX_[3]; }
    static bool HLE() { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[4]; }
    static bool AVX2() { return CPU_Rep.f_7_EBX_[5]; }
    static bool BMI2() { return CPU_Rep.f_7_EBX_[8]; }
    static bool ERMS() { return CPU_Rep.f_7_EBX_[9]; }
    static bool INVPCID() { return CPU_Rep.f_7_EBX_[10]; }
    static bool RTM() { return CPU_Rep.isIntel_ && CPU_Rep.f_7_EBX_[11]; }
    static bool AVX512F() { return CPU_Rep.f_7_EBX_[16]; }
    static bool RDSEED() { return CPU_Rep.f_7_EBX_[18]; }
    static bool ADX() { return CPU_Rep.f_7_EBX_[19]; }
    static bool AVX512PF() { return CPU_Rep.f_7_EBX_[26]; }
    static bool AVX512ER() { return CPU_Rep.f_7_EBX_[27]; }
    static bool AVX512CD() { return CPU_Rep.f_7_EBX_[28]; }
    static bool SHA() { return CPU_Rep.f_7_EBX_[29]; }

    static bool PREFETCHWT1() { return CPU_Rep.f_7_ECX_[0]; }

    static bool LAHF() { return CPU_Rep.f_81_ECX_[0]; }
    static bool LZCNT() { return CPU_Rep.isIntel_ && CPU_Rep.f_81_ECX_[5]; }
    static bool ABM() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[5]; }
    static bool SSE4a() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[6]; }
    static bool XOP() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[11]; }
    static bool TBM() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_ECX_[21]; }

    static bool SYSCALL() { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[11]; }
    static bool MMXEXT() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[22]; }
    static bool RDTSCP() { return CPU_Rep.isIntel_ && CPU_Rep.f_81_EDX_[27]; }
    static bool _3DNOWEXT() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[30]; }
    static bool _3DNOW() { return CPU_Rep.isAMD_ && CPU_Rep.f_81_EDX_[31]; }

private:
    static const InstructionSet_Internal CPU_Rep;

    class InstructionSet_Internal
    {
    public:
        InstructionSet_Internal()
            : nIds_{ 0 },
            nExIds_{ 0 },
            isIntel_{ false },
            isAMD_{ false },
            f_1_ECX_{ 0 },
            f_1_EDX_{ 0 },
            f_7_EBX_{ 0 },
            f_7_ECX_{ 0 },
            f_81_ECX_{ 0 },
            f_81_EDX_{ 0 },
            data_{},
            extdata_{}
        {
            std::array<int, 4> cpui;

            __cpuid(cpui.data(), 0);
            nIds_ = cpui[0];

            for (int i = 0; i <= nIds_; ++i)
            {
                __cpuidex(cpui.data(), i, 0);
                data_.push_back(cpui);
            }

            char vendor[0x20];

            memset(vendor, 0, sizeof(vendor));

            *reinterpret_cast<int*>(vendor) = data_[0][1];
            *reinterpret_cast<int*>(vendor + 4) = data_[0][3];
            *reinterpret_cast<int*>(vendor + 8) = data_[0][2];
            vendor_ = vendor;
            if (vendor_ == "GenuineIntel")
            {
                isIntel_ = true;
            }
            else if (vendor_ == "AuthenticAMD")
            {
                isAMD_ = true;
            }

            if (nIds_ >= 1)
            {
                f_1_ECX_ = data_[1][2];
                f_1_EDX_ = data_[1][3];
            }

            if (nIds_ >= 7)
            {
                f_7_EBX_ = data_[7][1];
                f_7_ECX_ = data_[7][2];
            }

            __cpuid(cpui.data(), 0x80000000);
            nExIds_ = cpui[0];

            char brand[0x40];
            memset(brand, 0, sizeof(brand));

            for (int i = 0x80000000; i <= nExIds_; ++i)
            {
                __cpuidex(cpui.data(), i, 0);
                extdata_.push_back(cpui);
            }

            if (nExIds_ >= 0x80000001)
            {
                f_81_ECX_ = extdata_[1][2];
                f_81_EDX_ = extdata_[1][3];
            }

            if (nExIds_ >= 0x80000004)
            {
                memcpy(brand, extdata_[2].data(), sizeof(cpui));
                memcpy(brand + 16, extdata_[3].data(), sizeof(cpui));
                memcpy(brand + 32, extdata_[4].data(), sizeof(cpui));
                brand_ = brand;
            }
        };

        int nIds_;
        int nExIds_;

        std::string vendor_;
        std::string brand_;

        bool isIntel_;
        bool isAMD_;

        std::bitset<32> f_1_ECX_;
        std::bitset<32> f_1_EDX_;
        std::bitset<32> f_7_EBX_;
        std::bitset<32> f_7_ECX_;
        std::bitset<32> f_81_ECX_;
        std::bitset<32> f_81_EDX_;
        std::vector<std::array<int, 4>> data_;
        std::vector<std::array<int, 4>> extdata_;
    };
};

const InstructionSet::InstructionSet_Internal InstructionSet::CPU_Rep;

static bool support_avx     = InstructionSet::AVX();
static bool support_avx2    = InstructionSet::AVX2();
static bool support_sse     = InstructionSet::SSE();
static bool support_sse2    = InstructionSet::SSE2();
static bool support_sse3    = InstructionSet::SSE3();
static bool support_ssse3   = InstructionSet::SSSE3();
static bool support_sse4_1  = InstructionSet::SSE41();
static bool support_sse4_2  = InstructionSet::SSE42();

HMODULE getThisModuleHandle()
{
    HMODULE hModule = NULL;
    ::GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
        GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, 
        (LPCTSTR)getThisModuleHandle, &hModule);

    return hModule;
}

#include <dlfcn.h>

void* resolve_addr(const char* name)
{
    return GetProcAddress(getThisModuleHandle(), name);
}

#endif

#if defined(SIMD_WINDOWS_PLATFORM)

#include <intrin.h>

#elif defined(SIMD_LINUX_PLATFORM)

#include <xmmintrin.h>
#include <emmintrin.h>
#include <pmmintrin.h>
#include <tmmintrin.h>
#include <smmintrin.h>
#include <immintrin.h>

#endif

#if defined(SIMD_WINDOWS_PLATFORM)

#define  simd_h extern "C" __declspec(dllexport)

#elif defined(SIMD_LINUX_PLATFORM)

#define simd_h extern "C" __attribute__((visibility("default")))

#else

#define simd_h

#endif

// #if !defined(INC_SSE) || (defined(USE_SIMD_MACROS) && defined(__SSE__))
// #define INC_SSE 1
// #endif

// #if !defined(INC_SSE2) || (defined(USE_SIMD_MACROS) && defined(__SSE2__))
// #define INC_SSE2 1
// #endif

// #if !defined(INC_SSE) || (defined(USE_SIMD_MACROS) && defined(__SSE3__))
// #define INC_SSE3 1
// #endif

// #if !defined(INC_SSE4_1) || (defined(USE_SIMD_MACROS) && defined(__SSE4_1__))
// #define INC_SSE4_1 1
// #endif

// #if !defined(INC_SSE4_2) || (defined(USE_SIMD_MACROS) && defined(__SSE4_2__))
// #define INC_SSE4_2 1
// #endif

// #if !defined(INC_SSSE3) || (defined(USE_SIMD_MACROS) && defined(__SSSE3__))
// #define INC_SSSE3 1
// #endif

// #if !defined(INC_AVX) || (defined(USE_SIMD_MACROS) && defined(__AVX__))
// #define INC_AVX 1
// #endif

// #if !defined(INC_AVX2) || (defined(USE_SIMD_MACROS) && defined(__AVX2__))
// #define INC_AVX2 1
// #endif

#endif
