#include <check.h>
#include <brainfuck/tape.h>
#include <brainfuck/machine.h>
#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1

// These tests are from  http://brainfuck.org/tests.b

START_TEST(machine_tape_size_test)
{
    int flag = 0;
    state *s = create_state(0, 0, create_tape(1, 1));
    int ret = 0;
    char *program = "++++[>++++++<-]>[>+++++>+++++++<<-]>>++++<[[>[[>>+<<-]<]>>>-]>-[>+>+<<-]>]"
                    "+++++[>+++++++<<++>-]>.<<.";
    int64_t ret_code;
    int counter = 0;
    char* inp = "~mlk zyx";
    do{
        ret_code = execute_instruction(s, program);
        if (ret_code >= 0){
            printf("%c", (char) ret_code);
        }
        
        if (ret_code == NEED_INPUT){
            char in;
            if(inp[counter] == '\0') {
                input_end(s);
            }
            input_char(s, inp[counter++]);
        }
        if(ret_code == '#')
            flag = 1;
    } while(ret_code != FINISHED);

    ck_assert_int_eq(flag, 1);
}
END_TEST

Suite *machine_suite(void){
    // (almost) copied from the check tutorial
    Suite *s;
    TCase *tc_core;

    s = suite_create("machine");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, machine_tape_size_test);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void){
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = machine_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
