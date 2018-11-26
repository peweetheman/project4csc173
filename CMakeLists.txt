cmake_minimum_required(VERSION 3.12)
project(untitled C)

set(CMAKE_C_STANDARD 99 CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=c99 -Wall -Werror")

add_executable(untitled main.c RealSQL.h database.h QueryParser.h)