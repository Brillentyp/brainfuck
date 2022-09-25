set(HEADER_LIST "${brainfuck_SOURCE_DIR}/include/brainfuck/machine.h" "${brainfuck_SOURCE_DIR}/include/brainfuck/tape.h")

add_library(lib machine.c tape.c ${HEADER_LIST})

target_include_directories(lib PUBLIC ../include)

