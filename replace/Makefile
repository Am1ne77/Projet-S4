#bs gtk+-3.0`Makefile for module: Structures
CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk+-3.0` -Wall -Wextra -D _GNU_SOURCE -g
LDLIBS = -lm `pkg-config --libs glib-2.0` `pkg-config --libs gtk+-3.0`

SRC = $(shell find . -name "*.c")
OBJ = $(addsuffix .o, $(basename $(SRC)))

all: compile

compile: setup
	$(CC) -c $(SRC) $(CFLAGS) $(LDLIBS)
	mv *.o obj/

setup:
	mkdir -p obj/

clean:
	rm -rf obj/

#end

