# The variable CC specifies which compiler will be used.
# (because different unix systems may use different compilers)
CC=gcc

# The variable CFLAGS specifies compiler options
#   -c :    Only compile (don't link)
#   -Wall:  Enable all warnings about lazy / dangerous C programming 
#   -std=c99: Using newer C99 version of C programming language
CFLAGS=-c -Wall -std=c99 -g

# All of the .h header files to use as dependencies
HEADERS=chess.h chess_output.h doubly_linked_list_move_history.h move.h location.h log.h

# All of the object files to produce as intermediary work
OBJECTS=chess.o chess_output.o doubly_linked_list_move_history.o move.o location.o log.c main.o

# The final program to build
EXECUTABLE=run

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)
