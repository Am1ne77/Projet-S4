# Makefile

CPPFLAGS = 
CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address
LDFLAGS =
LDLIBS =

SRC = set.c main.c
OBJ = ${SRC:.c=.o}

main: ${OBJ}
	$(CC) -fsanitize=address $^ -o main

clean: 
	${RM} main
	${RM} ${OBJ}
