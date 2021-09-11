cmake_minimum_required(VERSION 3.10)

include(CTest)

project(add_test)

add_executable(add_test add.cpp)
target_link_libraries(add_test simd)
add_test(NAME add_test COMMAND add_test)
