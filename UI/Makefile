#bs gtk+-3.0`Makefile for module: Structures
CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0` `pkg-config --cflags gtk+-3.0` -Wall -Wextra -D _GNU_SOURCE
LDLIBS = -lm `pkg-config --libs glib-2.0` `pkg-config --libs gtk+-3.0`

SRC = $(shell find . -name \*.c -a -not -name main.c)
OBJ = $(addsuffix .o, $(basename $(SRC)))

all: compile

compile: setup
	$(CC) -c $(SRC) $(CFLAGS) $(LDLIBS)
	mv *.o obj/

setup:
	mkdir -p obj/

clean:
	${RM} -rf obj/ main
	${RM} *.o

#end
