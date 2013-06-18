cmake_minimum_required (VERSION 2.6)

# Projektname
project(Profiler)

# Füge Source-Files hinzu
set(SRC_FILES demo.cpp)
set(SRC_FILES profiler.cpp ${SRC_FILES})
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-Wall -Werror -ggdb -std=c++11 -stdlib=libc++")

# Erzeuge Binary
add_executable(ProfilingDemo ${SRC_FILES})