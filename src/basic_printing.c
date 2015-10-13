#include "basic_printing.h"

void basic_printing1 () {
  int ch;

  initscr();
  raw();
  keypad(stdscr,TRUE);
  noecho();

  while ( true ) {
    printw("Type a character. Press x to escape.\n");
    ch = getch();

    if ( ch == 'x' ) {
      printw("Goodbye\n");
      refresh();
      endwin();
      break;
    } else if ( ch == KEY_F(1) ) {
      printw("You pressed F1\n");
    } else {
      printw("The pressed key is ");
      attron(A_BOLD);
      printw("%c\n",ch);
      attroff(A_BOLD);
    }

    refresh();
    endwin();
  }
}

void basic_printing2 () {
  char* s = "INTERNATIONALIZATION";
  int i;
  initscr();
  raw();
  for ( i=0; i < strlen(s); i++ ) {
    int attribute = i % 2 == 0 ? A_BOLD : A_UNDERLINE;
    addch(s[i] | attribute);
  }
  refresh();
  getch();
  endwin();
}

void basic_printing3 () {
  const int LENGTH = 20;
  int row          = 0;
  int column       = 0;

  initscr();
  raw();

  while ( row < LENGTH && column < LENGTH ) {
    mvaddch(row,column,'A');
    refresh();
    row    += 1;
    column += 2;
  }

  getch();
  endwin();
}
