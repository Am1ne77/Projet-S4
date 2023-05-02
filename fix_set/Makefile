# Makefile

CPPFLAGS = 
CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS =

SRC = main.c set.c set.h
OBJ = ${SRC:.c=.o}

main: ${OBJ}
	$(CC) $^ -o main

clean: 
	${RM} main
	${RM} ${OBJ}

