cmake_minimum_required (VERSION 2.6)

# Projektname
project(ASCIILandscape)

# Füge Source-Files hinzu
set(SRC_FILES src/program.cpp)
set(SRC_FILES src/map.cpp ${SRC_FILES})

set(CMAKE_CXX_FLAGS "-Wall -Werror -ggdb")

# Erzeuge Binary
add_executable(BuggyGame ${SRC_FILES})