cmake_minimum_required(VERSION 3.10)

project(simd)

add_library(simd INTERFACE)

target_include_directories(simd INTERFACE .)
target_link_libraries(simd INTERFACE ${CMAKE_DL_LIBS})

set(CMAKE_EXE_LINKER_FLAGS "-Wl,-export-dynamic")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

# Enable simd extensions for clang
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    add_definitions(-DINC_SSE=1)
    target_compile_options(simd INTERFACE -msse)

    add_definitions(-DINC_SSE2=1)
    target_compile_options(simd INTERFACE -msse2) 
    
    add_definitions(-DINC_SSSE3=1)
    target_compile_options(simd INTERFACE -msse3)
    
    add_definitions(-DINC_SSE4_1=1)
    target_compile_options(simd INTERFACE -msse4.1)

    add_definitions(-DINC_SSE4_2=1)
    target_compile_options(simd INTERFACE -msse4.2)
    
    add_definitions(-DINC_AVX=1)
    target_compile_options(simd INTERFACE -mavx)
    
    add_definitions(-DINC_AVX2=1)
    target_compile_options(simd INTERFACE -mavx2)
    
    add_definitions(-DINC_AVX512=1)
    target_compile_options(simd INTERFACE -mavx512f)
endif()

# Enable simd extensions for gcc
if("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    add_definitions(-DINC_SSE=1)
    target_compile_options(simd INTERFACE -msse)

    add_definitions(-DINC_SSE2=1)
    target_compile_options(simd INTERFACE -msse2) 

    add_definitions(-DINC_SSSE3=1)
    target_compile_options(simd INTERFACE -msse3)

    add_definitions(-DINC_SSE4_1=1)
    target_compile_options(simd INTERFACE -msse4.1)

    add_definitions(-DINC_SSE4_2=1)
    target_compile_options(simd INTERFACE -msse4.2)

    add_definitions(-DINC_AVX=1)
    target_compile_options(simd INTERFACE -mavx)

    add_definitions(-DINC_AVX2=1)
    target_compile_options(simd INTERFACE -mavx2)

    add_definitions(-DINC_AVX512=1)
    target_compile_options(simd INTERFACE -mavx512f)
endif()

# Enable simd extensions for MSVC
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    add_definitions(-DINC_SSE=1)
    target_compile_options(simd INTERFACE /arch:SSE)

    add_definitions(-DINC_SSE2=1)
    target_compile_options(simd INTERFACE /arch:SSE2)

    add_definitions(-DINC_SSSE3=1)
    target_compile_options(simd INTERFACE /arch:SSSE3)

    add_definitions(-DINC_SSE4_1=1)
    target_compile_options(simd INTERFACE /arch:SSSE4.1)

    add_definitions(-DINC_SSE4_2=1)
    target_compile_options(simd INTERFACE /arch:SSSE4.2)

    add_definitions(-DINC_AVX=1)
    target_compile_options(simd INTERFACE /arch:AVX)

    add_definitions(-DINC_AVX2=1)
    target_compile_options(simd INTERFACE /arch:AVX2)

    add_definitions(-DINC_AVX512=1)
    target_compile_options(simd INTERFACE /arch:AVX512)
endif()

# Enable simd extensions for Emscripten
if("${CMAKE_SYSTEM_NAME}" MATCHES "Emscripten")
    target_compile_options(simd INTERFACE -msimd128)
endif()


enable_testing()
add_subdirectory(tests)
