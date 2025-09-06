cmake_minimum_required(VERSION 3.29)
project(implementacionesListas C)

set(CMAKE_C_STANDARD 11)

add_executable(implementacionesListas main.c
        tElemento.c
        tElemento.h
        tListaEnlazadaSimple.c
        tListaEnlazadaSimple.h
        tListaOrdenada.c
        tListaOrdenada.h
        tListaCircular.c
        tListaCircular.h
        tListaCircularCabecera.c
        tListaCircularCabecera.h
        tListaDoubleEnlazada.c
        tListaDoubleEnlazada.h
        tListaDoubleEnlazadaPunteroInitEnd.c
        tListaDoubleEnlazadaPunteroInitEnd.h
)
