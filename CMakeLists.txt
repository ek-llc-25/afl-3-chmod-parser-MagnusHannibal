cmake_minimum_required(VERSION 4.0)
project(afl_3_chmod C)

set(CMAKE_C_STANDARD 23)

add_executable(afl_3_chmod main.c
        perms.c
        perms.h)
