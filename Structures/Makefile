# Makefile

CC = gcc
CPPFLAGS = -MMD -g
CFLAGS = -Wall -Wextra -D _GNU_SOURCE
LDFLAGS =
LDLIBS = -lm

SRC = main.c vector.c dict.c set.c automaton.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}

main: ${OBJ}

-include ${DEP}

.PHONY: clean

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} main

# END

