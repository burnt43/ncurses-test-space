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
    for ( int i = current_line; i < current_line+(max_row-10); i++ ) {
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
