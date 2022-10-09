#include <check.h>
#include <brainfuck/tape.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1


int test_1_eq_1(){
    return 1 == 1;
}

START_TEST(test_tape_creation){
    const int neg = 5;
    const int pos = 6;
    tape *t = create_tape(neg, pos);
    ck_assert_int_eq(t->neg_len, neg);
    ck_assert_int_eq(t->pos_len, pos);
    ck_assert(t->negative != NULL);
    ck_assert(t->positive != NULL);
    destroy_tape(t);
}
END_TEST

START_TEST(test_tape_realocation_get_tape_cell){
    tape *t = create_tape(0,0);
    ck_assert_int_eq(0, get_tape_cell(t, 1));
    ck_assert_int_eq(2, t->pos_len);
    ck_assert_int_eq(0, get_tape_cell(t, -7));
    ck_assert_int_eq(8, t->neg_len);
    destroy_tape(t);
}
END_TEST

START_TEST(test_tape_realocation_increment_cell){
    tape *t = create_tape(0,0);
    increment_cell(t, 1);
    ck_assert_int_eq(2, t->pos_len);
    increment_cell(t, -7);
    ck_assert_int_eq(8, t->neg_len);
    destroy_tape(t);
}
END_TEST

START_TEST(test_tape_realocation_decrement_cell){
    tape *t = create_tape(0,0);
    decrement_cell(t, 1);
    ck_assert_int_eq(2, t->pos_len);
    decrement_cell(t, -7);
    ck_assert_int_eq(8, t->neg_len);
    destroy_tape(t);
}
END_TEST

START_TEST(test_tape_realocation_set_cell){
    tape *t = create_tape(0,0);
    set_cell(t, 1, 1);
    ck_assert_int_eq(2, t->pos_len);
    set_cell(t, -7, 23);
    ck_assert_int_eq(8, t->neg_len);
    destroy_tape(t);
}
END_TEST

START_TEST(test_decrement_cell_under_flow){
    tape *t = create_tape(0,0);
    decrement_cell(t, 0);
    ck_assert_int_eq(get_tape_cell(t, 0), 0xFF);
}
END_TEST

START_TEST(test_increment_cell_over_flow){
    const cell_t MAX_VALUE = 0xFF;
    tape *t = create_tape(0,0);
    set_cell(t, 0, MAX_VALUE);
    // sanity check
    ck_assert_int_eq(get_tape_cell(t, 0), MAX_VALUE);
    increment_cell(t, 0);
    ck_assert_int_eq(get_tape_cell(t, 0), 0);
}
END_TEST



Suite *tape_suite(void){
    // (almost) copied from the check tutorial
    Suite *s;
    TCase *tc_core;

    s = suite_create("tape");
    tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_tape_creation);
    tcase_add_test(tc_core, test_tape_realocation_get_tape_cell);
    tcase_add_test(tc_core, test_tape_realocation_increment_cell);
    tcase_add_test(tc_core, test_tape_realocation_decrement_cell);
    tcase_add_test(tc_core, test_tape_realocation_set_cell);

    tcase_add_test(tc_core, test_decrement_cell_under_flow);
    tcase_add_test(tc_core, test_increment_cell_over_flow);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void){
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = tape_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}