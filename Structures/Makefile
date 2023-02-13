#Makefile for module: Structures
CC = gcc
CPPFLAGS = -MMD -g
CFLAGS = -Wall -Wextra -D _GNU_SOURCE
LDFLAGS =
LDLIBS = -lm

SRC = main.c vector.c dict.c set.c automaton.c
OBJ = $(addsuffix .o, $(basename $(shell find . -name "*.c")))
OBJDIR = ../libs

all: archive

struct: ${OBJ}
	${CC} ${OBJDIR}/* -o main

archive: setup $(OBJ)
	$(AR) rc ../libs/structures.a $(OBJDIR)/*

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	mv $@ $(OBJDIR)/

setup:
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -rf main
#end
