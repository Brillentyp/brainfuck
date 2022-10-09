cmake_minimum_required(VERSION 3.24)

project(brainfuck)

# lib 
add_subdirectory(src)

# executable
add_subdirectory(app)

add_subdirectory(tests)

enable_testing()