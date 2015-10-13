CC = gcc
CFLAGS = -c
LFLAGS = -lncurses
SRCDIR = src
OBJS = $(SRCDIR)/hello_world.o $(SRCDIR)/basic_printing.o $(SRCDIR)/main.o

ncurses_test_space: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o ncurses_test_space

$(SRCDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) $(SRCDIR)/main.c -o $(SRCDIR)/main.o

$(SRCDIR)/hello_world.o: $(SRCDIR)/hello_world.c $(SRCDIR)/hello_world.h
	$(CC) $(CFLAGS) $(SRCDIR)/hello_world.c -o $(SRCDIR)/hello_world.o

$(SRCDIR)/basic_printing.o: $(SRCDIR)/basic_printing.c $(SRCDIR)/basic_printing.h
	$(CC) $(CFLAGS) $(SRCDIR)/basic_printing.c -o $(SRCDIR)/basic_printing.o

clean:
	rm ./$(SRCDIR)/*.o ./ncurses_test_space
