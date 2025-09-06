cmake_minimum_required(VERSION 3.31)
project(Vuelos C)

set(CMAKE_C_STANDARD 11)

add_executable(Vuelos main.c
        tGrafo.c
        tGrafo.h
        tElemento.c
        tElemento.h)
