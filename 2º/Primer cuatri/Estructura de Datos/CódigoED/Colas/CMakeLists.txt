cmake_minimum_required(VERSION 3.31)
project(Colas C)

set(CMAKE_C_STANDARD 11)

add_executable(Colas main.c
        tColaPrioridad.c
        tColaPrioridad.h
        tElemento.c
        tElemento.h)
