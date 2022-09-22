#include <stdint.h>
typedef uint8_t cell_t;

typedef struct {
    /*
     * This struct represents the tape of the brainfuck turing machine.
     * Memory should be infinite in both directions.
     * The size of the tape arrays will always be a power of two.
     */
    cell_t* positive;
    cell_t* negative;
    uint64_t pos_len;
    uint64_t neg_len;
} tape;

tape* create_tape(uint64_t neg_len, uint64_t pos_len);
cell_t get_tape_cell(tape* t, uint64_t position);
void increment_cell(tape* t, uint64_t position);
void decrement_cell(tape* t, uint64_t position);
