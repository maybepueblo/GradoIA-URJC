cmake_minimum_required(VERSION 3.31)
project(Dioses C)

set(CMAKE_C_STANDARD 11)

add_executable(Dioses main.c
        tArbolDioses.c
        tArbolDioses.h
        tDios.c
        tDios.h)
