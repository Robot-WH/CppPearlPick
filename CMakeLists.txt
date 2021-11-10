cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

PROJECT(CppPearlPick)
set(CMAKE_CXX_STANDARD 14)
set(Cpp_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_BUILD_TYPE Debug)

find_package(Boost REQUIRED COMPONENTS filesystem system thread)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${Cpp_ROOT}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${Cpp_ROOT}/build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Cpp_ROOT}/build/bin)

add_subdirectory(src)