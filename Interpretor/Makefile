#Makefile
CC = gcc

CFLAGS = -Wall -Wextra -g

SRC = main.c ast.c lexer.c parser.c ../Structures/queue.c
OBJ = ${SRC:.c=.o}

main: ${OBJ}

all: main

clean:
	${RM} ${OBJ}
	${RM} queue.o
	${RM} main
#end
