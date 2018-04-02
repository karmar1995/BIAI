cmake_minimum_required(VERSION 3.9)
project(BIAI)

set(CMAKE_CXX_STANDARD 11)

add_executable(BIAI main.cpp Chromosome.cpp Chromosome.h IGeneticOperator.cpp IGeneticOperator.h)