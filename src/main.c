#include "hello_world.h"
#include "basic_printing.h"

int main (int argc, char** argv) {
  const int NUM_FUNCTIONS = 4;
  void (*functions[NUM_FUNCTIONS])();
  functions[0] = hello_world;
  functions[1] = basic_printing1;
  functions[2] = basic_printing2;
  functions[3] = basic_printing3;

  if ( argc == 2 ) {
    functions[atoi(argv[1])]();
  } else {
    printf("\033[0;31musage: ncurses_test_space.o TEST_NUM\n\033[0;39m");
  }
  return 0;
}
