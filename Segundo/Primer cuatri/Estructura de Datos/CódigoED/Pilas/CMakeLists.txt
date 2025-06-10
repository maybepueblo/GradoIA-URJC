cmake_minimum_required(VERSION 3.31)
project(Pilas C)

set(CMAKE_C_STANDARD 11)

add_executable(Pilas main.c
        tPila.c
        tPila.h
        tElemento.c
        tElemento.h)
