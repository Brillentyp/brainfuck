add_executable(tape_tests tape_tests.c)
target_link_libraries(tape_tests check)
target_link_libraries(tape_tests brainfuck_lib)

add_executable(machine_tests machine_tests.c)
target_link_libraries(machine_tests check)
target_link_libraries(machine_tests brainfuck_lib)

target_include_directories(tape_tests PUBLIC ../include)
target_include_directories(machine_tests PUBLIC ../include)

enable_testing()
add_test(NAME tape_tests COMMAND tape_tests)
add_test(NAME machine_tests COMMAND machine_tests)


