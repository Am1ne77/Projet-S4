#Makefile
CC = gcc

CFLAGS = -Wall -Wextra -g #-fsanitize=address
SRC = *.c

main:
	$(CC) $(CFLAGS)  $(SRC) -L ../libs -l:structures.a
 
all: main

clean:
	${RM} *.o 
	${RM} a.out 
#end
