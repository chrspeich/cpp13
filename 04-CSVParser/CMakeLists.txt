cmake_minimum_required (VERSION 2.6)

# Projektname
project(CSVParser)

# Füge Source-Files hinzu
set(SRC_FILES parser.cpp program.cpp)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-Wall -Werror -ggdb -std=c++11 -stdlib=libc++")

# Erzeuge Binary
add_executable(CSVParser ${SRC_FILES})