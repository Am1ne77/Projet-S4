#Makefile for module: Structures
CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0` -Wall -Wextra -D _GNU_SOURCE
LDLIBS = -L ../libs -l:structures.a

SRC = $(shell find . -name "*.c")
OBJ = $(addsuffix .o, $(basename $(SRC)))

all: setup $(OBJ)

setup:
	mkdir -p obj/

clean:
	rm -rf obj/

%.o: %.c
	$(CC) -c $(CFLAGS) $(LDLIBS) $< -o $@
	mv $@ obj/


#end
