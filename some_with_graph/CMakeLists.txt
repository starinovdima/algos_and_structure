cmake_minimum_required(VERSION 3.17)
project(lab5 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab5 main.c func.c)
add_executable(chernovik chernovik.c)
add_executable(dop dop.c func_dop.c)