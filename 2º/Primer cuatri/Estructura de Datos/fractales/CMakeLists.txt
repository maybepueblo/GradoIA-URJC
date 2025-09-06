cmake_minimum_required(VERSION 3.29)
project(fractales)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        fractales.c
        fractales.c
        complejos.c
        complejos.h
        Bitmap.h
        Bitmap.c
)

target_link_libraries(fractales.c m)