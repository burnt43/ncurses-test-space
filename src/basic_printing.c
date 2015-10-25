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

void basic_printing7 () {
  int current_char, row, col;
  FILE *file;
  int y,x;

  file = fopen("./data/file1.jim","r");
  if ( file == NULL ) {
    perror("\033[0;31mcannot open file.\n\033[0;39m");
    exit(1);
  }
  initscr();
  getmaxyx(stdscr,row,col);
  while( (current_char = fgetc(file)) != EOF ) {
    if ( current_char == ']' ) { attroff(A_UNDERLINE); }

    printw("%c",current_char);

    if ( current_char == '[' ) { attron(A_UNDERLINE); }
  }
  getch();
  endwin();
}

typedef struct _linked_list {
  char   *value;
  struct _linked_list *next;
} LINKED_LIST;

LINKED_LIST* linked_list_new() {
  LINKED_LIST *list = (LINKED_LIST*)malloc(sizeof(LINKED_LIST));
  list->value = NULL;
  list->next  = NULL;
  return list;
}

int linked_list_free(LINKED_LIST *list) {
  LINKED_LIST *iterator = list;
  while ( iterator != NULL ) {
    char *p_value       = iterator->value;
    LINKED_LIST *p_next = iterator->next;
    printf("freeing memory for string: %s @ %p\n",p_value,p_value);
    free(p_value);
    printf("freeing memory for linked_list @ %p\n",iterator);
    free(iterator);
    iterator = p_next;
  }
}

LINKED_LIST* linked_list_get_last_element(LINKED_LIST *list) {
  LINKED_LIST *iterator;
  for( iterator = list; iterator->next != NULL; iterator = iterator->next );
  return iterator;
}

void linked_list_print(LINKED_LIST *list) {
  for( LINKED_LIST *iterator; iterator != NULL; iterator = iterator->next ) {
    printf("%s->",iterator->value);
  }
  printf("EOL\n");
}

int linked_list_has_value(LINKED_LIST *list) {
  return list->value != NULL;
}

int linked_list_push(LINKED_LIST *list, char *s) {
  char *allocated_string = (char*)malloc( strlen(s) * sizeof(char) );
  strcpy(allocated_string,s);

  if ( linked_list_has_value(list) ) {
    LINKED_LIST *last_element = linked_list_get_last_element(list);
    LINKED_LIST *new_element  = linked_list_new();
    new_element->value = allocated_string;
    last_element->next = new_element;
  } else {
    list->value = allocated_string;
  }

  return 0;
}

int linked_list_append_list(LINKED_LIST *first_list, LINKED_LIST *second_list) {
  for ( LINKED_LIST *iterator = second_list; iterator != NULL; iterator = iterator->next ) {
    linked_list_push(first_list,iterator->value);
  }
  return 0;
}

int linked_list_length(LINKED_LIST *list) {
  int result = 0;
  if ( linked_list_has_value(list) ) {
    for ( LINKED_LIST *iter = list; iter != NULL; iter = iter->next ) {
      result++;
    }
  } else {
    return 0;
  }
  return result;
}

char** linked_list_as_double_pointer(LINKED_LIST *list) {
  char** result = (char**)malloc( linked_list_length(list) * sizeof(char*) );
  int position  = 0;
  for ( LINKED_LIST *iter = list; iter != NULL; iter = iter->next ) {
    char *s = (char*)malloc(strlen(iter->value) * sizeof(char));
    strcpy(s,iter->value);
    *(result+position) = s;
    position++;
  }
  return result;
}

void demo_function () {
  int  j = 0x006E6F73;
  char x = 'r';
  char y = 'a';
  char z = 'C';
  int  i = 0x2D2D2D00;
  char a = 'm';
  char b = 'i';
  char c = 'J';
  assert( strcmp(&c,"Jim") == 0 );
  assert( strcmp(&c+8,"Carson") == 0 );
}

void basic_printing8 () {
  // ASSERTIONS
  LINKED_LIST *test_list = linked_list_new();
  LINKED_LIST *caboose   = linked_list_new();

  assert( test_list->value == NULL );
  assert( test_list->next == NULL );
  assert( linked_list_length(test_list) == 0 );

  linked_list_push(test_list,"foo");
  assert( strcmp(test_list->value,"foo") == 0 );
  assert( test_list->next == NULL );
  assert( strcmp(linked_list_get_last_element(test_list)->value,"foo") == 0 );
  assert( linked_list_get_last_element(test_list)->next == NULL );
  assert( linked_list_length(test_list) == 1 );

  linked_list_push(test_list,"bar");
  assert( strcmp(test_list->value,"foo") == 0 );
  assert( test_list->next != NULL );
  assert( strcmp(linked_list_get_last_element(test_list)->value,"bar") == 0 );
  assert( linked_list_get_last_element(test_list)->next == NULL );
  assert( linked_list_length(test_list) == 2 );

  linked_list_push(caboose,"baz");
  linked_list_append_list(test_list,caboose);
  assert( strcmp(linked_list_get_last_element(test_list)->value,"baz") == 0 );
  assert( linked_list_length(test_list) == 3 );

  char **list_as_double_pointer = linked_list_as_double_pointer(test_list);
  assert( strcmp( (char *)*(list_as_double_pointer+0), "foo" ) == 0 );
  assert( strcmp( (char *)*(list_as_double_pointer+1), "bar" ) == 0 );
  assert( strcmp( (char *)*(list_as_double_pointer+2), "baz" ) == 0 );

  linked_list_free(test_list);
  linked_list_free(caboose);
  free(list_as_double_pointer);

  // REAL STUFF
  LINKED_LIST *list;
  FILE *file;
  char *read_string;
  int max_row,max_col;
  int current_line = 0;
  int read_char;


  initscr();
  noecho();
  keypad(stdscr,TRUE);
  getmaxyx(stdscr,max_row,max_col);

  const int WIDTH = max_col-2;

  list        = linked_list_new();
  file        = fopen("./data/file2.txt","r");
  read_string = (char*)malloc(WIDTH * sizeof(char));

  while ( (read_string = fgets(read_string,WIDTH,file)) != NULL ) {
    linked_list_push(list,read_string);
  }

  char **broken_up_strings = linked_list_as_double_pointer(list);
  const int MAX_LINES      = linked_list_length(list);
  linked_list_free(list);

  while ( true ) {
    int current_row = 0;
    move(0,0);
    for ( int i = current_line; i < current_line+(max_row-5); i++ ) {
      printw("%s",(char*)*(broken_up_strings+i));
      current_row++;
      move(current_row,0);
    }

    refresh();
    read_char = getch();
    if ( read_char == 'q' ) { break; }
    switch (read_char) {
      case KEY_DOWN:
        current_line++;
        break;
      case KEY_UP:
        if ( current_line > 0 ) {
          current_line--;
        }
        break;
    }
  }
  endwin();
}

void basic_printing9() {
  int max_x, max_y;
  initscr();
  start_color();

  getmaxyx(stdscr,max_y,max_x);

  init_pair(1,COLOR_CYAN,COLOR_BLACK);
  init_pair(2,COLOR_RED,COLOR_BLACK);

  for ( int i = 0; i < max_y; i++ ) {
    mvprintw(i,0,"Lorem ipsum dolor sit amet, consectetur adipiscing elit");
    mvchgat(i,10,-1,A_BOLD,(i%2)+1,NULL);

  }
  refresh();
  getch();
  endwin();
}
  
typedef struct simple_menu {
  WINDOW *window;
  char **choices;
  int current_position;
  int num_choices;
} SIMPLE_MENU;

SIMPLE_MENU* simple_menu_create(int height, int width, int pos_y, int pos_x, int num_args, ...) {
  SIMPLE_MENU *result;

  result = (SIMPLE_MENU*)malloc( sizeof(SIMPLE_MENU) );
  result->window  = newwin(height,width,pos_y,pos_x);
  result->choices = (char**)malloc( num_args * sizeof(char*) );
  result->current_position = 0;
  result->num_choices = num_args;

  va_list valist;
  va_start(valist,num_args);
  for ( int i = 0; i < num_args; i++ ) {
    char *tmp = va_arg(valist,char*);
    char *allocated_string = (char*)malloc( strlen(tmp) * sizeof(char) );
    strcpy(allocated_string,tmp);
    *(result->choices + i) = allocated_string;
  }
  va_end(valist);
  return result;
}

char* simple_menu_get_choice(SIMPLE_MENU *self,int choice_num) {
  return *(self->choices + choice_num);
}

void simple_menu_draw(SIMPLE_MENU *self) {
  box(self->window,0,0);
  mvwprintw( self->window, self->current_position + 1, 2, "->" );
  for ( int i = 0; i < self->num_choices; i++ ) {
    mvwprintw(self->window,i+1,5,"%s",simple_menu_get_choice(self,i));
  }
  wrefresh(self->window);
}

void simple_menu_destroy(SIMPLE_MENU *self) {
  //dealloc choice strings
  for ( int i = 0; i < self->num_choices; i++ ) {
    free( *(self->choices + i) );
  }
  free(self->choices);
  wborder(self->window,' ',' ',' ',' ',' ',' ',' ',' ');
  delwin(self->window);
  free(self);
}

void basic_printing10() {
  SIMPLE_MENU *menu;
  
  initscr();
  noecho();
  curs_set(0);
  refresh();

  menu = simple_menu_create(7,20,0,0,3,"James","Edward","Carson");
  simple_menu_draw(menu);

  getch();

  simple_menu_destroy(menu);
  endwin();
}

void some_testing() {
  WINDOW *win;
  win = initscr();
  endwin();

  printf( "NCURSES_SIZE_T: %d\n",sizeof(NCURSES_SIZE_T) );
  printf( "sizeof(bool): %d\n", sizeof(bool) );
  printf( "sizeof(unsigned long): %d\n", sizeof(unsigned long) );
  printf( "sizeof(attr_t): %d\n", sizeof(attr_t) );
  printf( "sizeof(chtype): %d\n", sizeof(chtype) );
  printf( "_cury: %d\n",win->_cury );
  printf( "_curx: %d\n",win->_curx );
  printf( "_maxy: %d\n",win->_maxy );
  printf( "_maxx: %d\n",win->_maxx );
  printf( "_begy: %d\n",win->_begy );
  printf( "_begx: %d\n",win->_begx );
  printf( "_flags: %x\n",win->_flags );
  printf( "_attrs: %x\n",win->_attrs );
  printf( "_bkgd: %x\n",win->_bkgd );
  printf( "_notimeout: %d\n",win->_notimeout );
  printf( "_clear: %d\n",win->_clear );

  assert( *(short*)((char*)win + 0) == win->_cury );
  assert( *(short*)((char*)win + 2) == win->_curx );
  assert( *(short*)((char*)win + 4) == win->_maxy );
  assert( *(short*)((char*)win + 6) == win->_maxx );
  assert( *(short*)((char*)win + 8) == win->_begy );
  assert( *(short*)((char*)win + 10) == win->_begx );
  assert( *(short*)((char*)win + 12) == win->_flags);
  assert( *(unsigned long*)((char*)win + 16) == win->_attrs);
  assert( *(unsigned long*)((char*)win + 24) == win->_bkgd);
  assert( *(bool*)((char*)win + 32) == win->_notimeout);
  assert( *(bool*)((char*)win + 33) == win->_clear);
  assert( *(bool*)((char*)win + 34) == win->_leaveok);

  typedef struct  _foobar {
    char c;
    unsigned long l;
    char d;
  } FOOBAR;

  printf("%d\n",sizeof(FOOBAR));

  FOOBAR foo;
  foo.c = 10;
  foo.l = 10;

  printf("%d\n", *(((char*)&foo)+1) );
}
