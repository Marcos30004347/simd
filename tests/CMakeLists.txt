cmake_minimum_required(VERSION 3.10)

include(CTest)

project(add_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

add_executable(add_test add.cpp)

target_link_libraries(add_test simd)

add_test(NAME add_test COMMAND add_test)
