/*
 *  This file implements an brainfuck interpreter.
 *  The tape is (as long as resources are available) infinite.
 *  If no more memory can be allocated the program terminates with an error.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "machine.h"
#include "tape.h"

int main() {
    printf("hi\n");
    tape *t = create_tape(64,64);
    state *s = create_state(0,0,t);
    // hello world program
    char *program = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    program = ",[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>++++++++++++++<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>>+++++[<----->-]<<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>++++++++++++++<-[>+<-[>+<-[>+<-[>+<-[>+<-[>++++++++++++++<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>>+++++[<----->-]<<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>+<-[>++++++++++++++<-[>+<-]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]>.[-]<,]";
    printf("%s\n",program);
    int64_t ret_code;
    int counter = 0;
    char* inp = "~mlk zyx";
    do{
        //printf("%c  %d  %d  %d\n", program[s->pc], s->pc, s->ac, get_tape_cell(t, s->ac));
        ret_code = execute_instruction(s, program);
        if (ret_code >= 0){
            printf("%c", ret_code);
        }
        
        if (ret_code == NEED_INPUT){
            char in;
            //scanf(" %c", &input);
            //input(s, in);
            if(inp[counter] == '\0') {
                ret_code = FINISHED;
            }
            input(s, inp[counter++]);
        }
        //printf("   %d  %d  %d\n", s->pc, s->ac, get_tape_cell(t, s->ac));
    } while(ret_code != FINISHED);
}