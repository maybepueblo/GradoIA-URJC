cmake_minimum_required(VERSION 3.31)
project(Listas C)

set(CMAKE_C_STANDARD 11)

add_executable(Listas main.c
        tListaEnlazadaSimple.c
        tListaEnlazadaSimple.h
        tElemento.c
        tElemento.h
        tListaEnlazadaInsertFinal.c
        tListaEnlazadaInsertFinal.h
        tListaOrdenada.c
        tListaOrdenada.h
        tListaCabecerayFinal.c
        tListaCabecerayFinal.h
        tListaCircular.c
        tListaCircular.h
        tListaDobEnlace.c
        tListaDobEnlace.h
)
