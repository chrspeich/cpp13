cmake_minimum_required (VERSION 2.6)

# Projektname
project(Factory)

# Füge Source-Files hinzu
set(SRC_FILES Fleet.cpp Main.cpp SpaceShipFactory.cpp)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-Wall -Werror -ggdb -std=c++11 -stdlib=libc++ -Wno-unused-private-field")

# Erzeuge Binary
add_executable(Factory ${SRC_FILES})