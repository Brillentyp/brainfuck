#include <brainfuck/machine.h>
#include <stdlib.h>

enum commands {
    // > - move the pointer right
    MOVE_POINTER_RIGHT = '>',
    // < - move the pointer left
    MOVE_POINTER_LEFT = '<',
    // + - increment the current cell
    INCREMENT_CELL = '+',
    // - - decrement the current cell
    DECREMENT_CELL = '-',
    // . - output the value of the current cell
    OUTPUT = '.',
    // , - replace the value of the current cell with input
    INPUT = ',',
    // [ - jump to the matching ] instruction if the current value is zero
    JUMP_ZERO = '[',
    // ] - jump to the matching [ instruction if the current value is not zero
    JUMP_NOT_ZERO = ']'
};

void find_next(state* s, char* program, char next, int direction) {
    /**
     *  Find next occurence of the next character and set the pc of the state to
     * the position of the character. direction: -1 if the character should be
     * at a smaller position in the program, 1 else.
     */
    int step = direction >= 0 ? 1 : -1;
    while (program[s->pc] != next)
        s->pc += step;
}

void find_coresponding_jump(state* s, char* program, char c) {
    if(c != JUMP_NOT_ZERO && c != JUMP_ZERO)
        return;
    
    int step = c == JUMP_NOT_ZERO ? 1 : -1;
    char c_count_up = c == JUMP_NOT_ZERO ? JUMP_ZERO : JUMP_NOT_ZERO;
    char c_count_down = c == JUMP_NOT_ZERO ? JUMP_NOT_ZERO : JUMP_ZERO;

    int count = 1;
    while (count != 0){
        s->pc += step;
        if (program[s->pc] == c_count_up){
            count++;
        }
        if (program[s->pc] == c_count_down){
            count--;
        }
    }
    
}

void input_char(state* s, cell_t input) {
    set_cell(s->t, s->ac, input);
}

void input_end(state* s){
    s->pc++;
}

int64_t execute_instruction(state* s, char* program) {
    // Executes a single instruction of the program according to state.
    // Returns -1 if there is no output, otherwise the content of a cell.
    // Returns -2 if input is required. Input may be set via the input function.
    // Returns -3 if the pc reached the end of the program
    // ignores all characters that are not brainfuck instruction

    /*
    
    
    + - increment the current cell
    - - decrement the current cell
    . - output the value of the current cell
    , - replace the value of the current cell with input
    [ - jump to the matching ] instruction if the current value is zero
    ] - jump to the matching [ instruction if the current value is not zero
    */

    int64_t ret = NO_OUTPUT;

    switch (program[s->pc]) {
        case MOVE_POINTER_RIGHT:
            s->ac++;
            break;
        case MOVE_POINTER_LEFT:
            s->ac--;
            break;
        case INCREMENT_CELL:
            increment_cell(s->t, s->ac);
            break;
        case DECREMENT_CELL:
            decrement_cell(s->t, s->ac);
            break;
        case OUTPUT:
            ret = get_tape_cell(s->t, s->ac);
            break;
        case INPUT:
            ret = NEED_INPUT;
            break;
        case JUMP_ZERO:
            // TODO: is more complex. Does have to be the fitting ], not just
            // the next one (idea: save tuples with ac of [])
            if (get_tape_cell(s->t, s->ac) == 0) {
                find_coresponding_jump(s, program, JUMP_NOT_ZERO);
            }
            break;
        case JUMP_NOT_ZERO:
            if (get_tape_cell(s->t, s->ac) != 0) {
                find_coresponding_jump(s, program, JUMP_ZERO);
            }
            break;
        case '\0':
            return FINISHED;
        default:
            break;
    }

    s->pc++;
    return ret;
}

state* create_state(uint64_t pc, int64_t ac, tape* t) {
    state* s = malloc(sizeof(state));
    *s = (state){.ac = ac, .pc = pc, .t = t};
    return s;
}
