#include "basic_printing.h"

int kill_signal = 0;

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

void basic_printing4 () {
  const char* s = "James Carson";
  int row,col;

  initscr();
  getmaxyx(stdscr,row,col);

  mvprintw(row/2,(col - strlen(s))/2,s);
  mvprintw(row-2,0,"rows: %d, cols: %d",row,col);

  refresh();
  getch();
  endwin();
}

void *print_stuff () {
  int foo = 0;
  int bar = 0;

  while(true) {
    if (kill_signal) {
      pthread_exit(NULL);
    } else {
      mvprintw(0,0,"foo: %d, bar: %d",foo,bar);
      refresh();
      foo += 2;
      bar += 3;
      usleep(100000);
    }
  }
}

void *get_input () {
  getch();
  kill_signal = 1;
  pthread_exit(NULL);
}

void basic_printing5 () {
  pthread_t printing_thread;
  pthread_t input_thread;

  initscr();
  pthread_create( &printing_thread, NULL, print_stuff, NULL );
  pthread_create( &input_thread, NULL, get_input, NULL );
  pthread_join(printing_thread, NULL);
  pthread_join(input_thread, NULL);

  endwin();
}

void basic_printing6 () {
  char *s = "Enter a String: ";
  char *input_string = (char*)malloc(64*sizeof(char));
  int row,col;
  initscr();
  getmaxyx(stdscr,row,col);
  mvprintw(row/2,(col-strlen(s))/2,s);
  getstr(input_string);
  mvprintw(row-2,0,"You enter %s",input_string);
  getch();
  endwin();
}
