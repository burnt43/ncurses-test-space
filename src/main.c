#include "hello_world.h"
#include "basic_printing.h"

int main (int argc, char** argv) {

  const int NUM_FUNCTIONS = 12;
  void (*functions[NUM_FUNCTIONS])();
  functions[0] = hello_world;
  functions[1] = basic_printing1;
  functions[2] = basic_printing2;
  functions[3] = basic_printing3;
  functions[4] = basic_printing4;
  functions[5] = basic_printing5;
  functions[6] = basic_printing6;
  functions[7] = basic_printing7;
  functions[8] = basic_printing8;
  functions[9] = basic_printing9;

  functions[10] = basic_printing10;
  functions[11] = some_testing;

  if ( argc == 2 ) {
    functions[atoi(argv[1])]();
  } else {
    printf("\033[0;31musage: ncurses_test_space.o TEST_NUM\n\033[0;39m");
  }

  return 0;
}
