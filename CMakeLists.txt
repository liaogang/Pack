cmake_minimum_required(VERSION 3.21)
project(Pack C)

set(CMAKE_C_STANDARD 99)

add_executable(Pack main.c Pack.c Pack2.c)
