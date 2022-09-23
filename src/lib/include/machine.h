#include <stdint.h>
#include "tape.h"

#define NO_OUTPUT -1
#define NEED_INPUT -2
#define FINISHED -3

typedef struct {
    uint64_t pc;
    int64_t ac;
    tape* t;
} state;

int64_t execute_instruction(state* s, char* program);
void input(state *s, cell_t input);
state* create_state(uint64_t pc, int64_t ac, tape* t);