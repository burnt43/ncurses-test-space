#include "hello_world.h"

void hello_world () {
  initscr();
  printw("Hello, World\nHit any key to exit\n");
  refresh();
  getch();
  endwin();
}
