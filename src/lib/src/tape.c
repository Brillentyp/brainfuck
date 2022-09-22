#include "tape.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: add to_string function.

// macro to get the index for the tape arrays
#define INDEX(position) ((position) >= 0 ? (position) : -((position) + 1))

tape* create_tape(uint64_t neg_len, uint64_t pos_len) {
    // creates tape. Returns NULL on Error
    // calloc initializes memory to 0 (realloc does not though)
    cell_t* arr_neg = calloc(neg_len, sizeof(cell_t));
    cell_t* arr_pos = calloc(neg_len, sizeof(cell_t));

    if (arr_neg == NULL || arr_pos == NULL)
        return NULL;

    tape* ret_tape = malloc(sizeof(tape));
    // compound literals
    *ret_tape = (tape){.positive = arr_pos,
                       .negative = arr_neg,
                       .pos_len = pos_len,
                       .neg_len = neg_len};
}

// TODO: do error handling
cell_t get_tape_cell(tape* t, uint64_t position) {
    check_reallocate(t, position);
    if (position >= 0) {
        return t->positive[INDEX(position)];
    } else {
        return t->negative[INDEX(position)];
    }
}

void increment_cell(tape* t, uint64_t position) {
    check_reallocate(t, position);
    if (position >= 0) {
        t->positive[INDEX(position)]++;
    } else {
        t->negative[INDEX(position)]++;
    }
}

void decrement_cell(tape* t, uint64_t position) {
    check_reallocate(t, position);
    if (position >= 0) {
        t->positive[INDEX(position)]--;
    } else {
        t->negative[INDEX(position)]--;
    }
}

void check_reallocate(tape* t, uint64_t position) {
    /** Checks if the tape needs to be reallocated for the required position.
     *  If the tape needs reallocation it will be reallocated and initialized.
     */
    uint64_t index = position >= 0 ? position : -(position + 1);

    if (position >= 0) {
        if (index >= t->pos_len) {
            uint64_t new_len = (1 << log(index));
            t->positive = realloc_initialize(t->positive, t->pos_len, new_len);
            t->pos_len = new_len;
        }
    } else {
        if (index >= t->neg_len) {
            uint64_t new_len = (1 << log(index));
            t->negative = realloc_initialize(t->negative, t->neg_len, new_len);
            t->neg_len = new_len;
        }
    }
}

cell_t* realloc_initialize(cell_t* array, uint64_t old_len, uint64_t new_len) {
    /** Takes an array of length old_len and reallocates it to length new_len.
     *  All entries between old_len and new_len are initialized to 0.
     *  Returns Pointer to the reallocated array.
     */

    cell_t* new = reallocarray(array, new_len, sizeof(cell_t));
    for (int i = old_len; i < new_len; i++)
        new[i] = 0;
}

uint64_t log_ceil(uint64_t num) {
    int log = 0;
    while ((num >> log) != 0)
        log++;
    return log;
}