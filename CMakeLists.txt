cmake_minimum_required(VERSION 3.24)

project(brainfuck)

add_executable(brainfuck src/brainfuck.c)
target_include_directories(brainfuck PUBLIC src)

include_directories(./src/lib/src)
add_library(lib machine.c tape.c)

target_link_libraries(brainfuck lib)
