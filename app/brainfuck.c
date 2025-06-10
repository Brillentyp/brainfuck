/*
 *  This file implements an brainfuck interpreter.
 *  The tape is (as long as resources are available) infinite.
 *  If no more memory can be allocated the program terminates with an error.
 */
#include <brainfuck/machine.h>
#include <brainfuck/tape.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
 #include <fcntl.h>




enum STATUS_CODE {
  NO_PROBLEM = -1,
  INVALID_ARGUMENT = 0,
  NO_PROGRAM,
  MISSING_INPUT,
  TOO_MANY_ARGS,
};

char *error_messages[] = {
    "Invalid Argument",
    "No program provided",
    "No input provided",
    "Too many args",
};

typedef struct args {
  // -h
  bool help;
  // -i
  bool argument_input;
  char *arg_input_str;
  enum STATUS_CODE status_code;
  // only argument not prefixed by -
  char *source_file;
} args;

void print_help(void) {
  char *help = "This is a simple brainfuck interpreter.\n"
               "Just pass the path to a brainfuck program to the interpreter and enter your input.\n"
               "You can use -i <your input> to pass your input as an argument instead of stdin.\n";
   printf("%s", help);
}

args parse_args(char **string_args, int argc) {
  args a = {.help=false, .argument_input = false, .arg_input_str=NULL, .status_code=NO_PROBLEM,.source_file=NULL};
  for (int i = 1; i < argc; i++) {
    char *sa = string_args[i];
    if (sa[0] == '-') {
      if (sa[1] == '\0') {
        a.status_code = INVALID_ARGUMENT;
        return a;
      }
      if (sa[1] == 'h') {
        a.help = true;
      } else if (sa[1] == 'i' && sa[2] == '\0') {
        if (i + 1 < argc) {
          a.argument_input = true;
          a.arg_input_str = string_args[++i];
        } else {
          a.status_code = MISSING_INPUT;
          return a;
        }

      } else {
        a.status_code = INVALID_ARGUMENT;
        return a;
      }
    } else {
      if (a.source_file == NULL) {
        a.source_file = string_args[i];
      } else {
        a.status_code = TOO_MANY_ARGS;
      }
    }
  }
  if(a.source_file == NULL)
    a.status_code = NO_PROGRAM;
  return a;
}

void print_error(enum STATUS_CODE e) {
  if (e == NO_PROBLEM) {
    return;
  }
  fprintf(stderr, "%s\n", error_messages[e]);
}

void handle_input(state *s, char *inp) {
  static int counter = 0;
  if (inp != NULL) {
    if (inp[counter] == '\0') {
      input_end(s);
    }
    input_char(s, inp[counter++]);
  } else {
    int c = fgetc(stdin);
    if(c == EOF || c == '\n'){
      printf("\n");
      input_end(s);
    }
    input_char(s, (cell_t) c);
  }
  
}

int main(int argc, char **argv) {
  if(argc == 1){
    print_help();
    exit(0);
  }
  
  args pa = parse_args(argv, argc);
  if(pa.help){
    print_help();
    exit(0);
  }
  
  if (pa.status_code != NO_PROBLEM) {
    print_error(pa.status_code);
    exit(1);
  }

  char *inp = NULL;
  if (pa.argument_input) {
    inp = pa.arg_input_str;
  }

  int fp = open(pa.source_file, O_RDONLY);
  if(fp < 0){
    fprintf(stderr, "Could not open source file\n");
    exit(1);
  }

  off_t size = lseek(fp, 0, SEEK_END);
  // not necessary for what I am currently doing, but in case I want to something with the fd later
  lseek(fp, 0, SEEK_SET);

  char *program = mmap(NULL, size, PROT_READ , MAP_PRIVATE, fp, 0);
  if(program == MAP_FAILED){
    fprintf(stderr, "Could not read program\n");
    exit(1);
  }
  
  tape *t = create_tape(64, 64);
  state *s = create_state(0, 0, t);
  int64_t ret_code;
  do {
    ret_code = execute_instruction(s, program);
    if (ret_code >= 0) {
      // 10 is a line feed
      if(ret_code == 10){
        printf("\n");
      } else {
        printf("%c", (char) ret_code);
      }
    }

    if (ret_code == NEED_INPUT) {
      handle_input(s, inp);
    }
  } while (ret_code != FINISHED);
  printf("\n");
  fflush(stdout);
}
