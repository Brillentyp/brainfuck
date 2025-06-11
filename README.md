This is a simple brainfuck interpreter.
build directions:
  ```
  mkdir build && cd build
  cmake ..
  cmake -build .
  ````
The binary will be located at build/app/brainfuck

Just pass the path to a brainfuck program to the interpreter and enter your input.
You can use -i <your input> to pass your input as an argument instead of stdin.

A good source for some brainfuck programs and a brainfuck reference (in case you want to implement your own interpreter): (https://brainfuck.org/)[https://brainfuck.org/] 
