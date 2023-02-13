#Makefile for module: Structures
CC = gcc
CFLAGS := -Wall -Wextra

OBJ = $(addsuffix .o, $(basename $(shell find . -name "*.c")))
OBJDIR = ../libs

all: archive

archive: setup $(OBJ)
	$(AR) rc ../libs/structures.a $(OBJDIR)/*

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	mv $@ $(OBJDIR)/

setup:
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
#end
