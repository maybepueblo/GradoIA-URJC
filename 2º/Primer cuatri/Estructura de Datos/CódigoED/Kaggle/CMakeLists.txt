cmake_minimum_required(VERSION 3.31)
project(Kaggle C)

set(CMAKE_C_STANDARD 11)

add_executable(Kaggle main.c
        tABB.c
        tABB.h
        tElemento.c
        tElemento.h)
