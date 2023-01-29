# Makefile

CC = gcc -fsanitize=address
CPPFLAGS = -MMD -g
CFLAGS = -Wall -Wextra
LDFLAGS =
LDLIBS =

SRC = main.c vector.c
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

