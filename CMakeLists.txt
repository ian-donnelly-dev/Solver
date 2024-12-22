cmake_minimum_required(VERSION 3.30)
project(Solver)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-O3 -march=native -funroll-loops -ftree-vectorize -flto)

add_executable(Solver main.cpp)
