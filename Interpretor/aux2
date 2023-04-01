#Makefile
CC = gcc
CFLAGS = `pkg-config --cflags glib-2.0` -Wall -Wextra -g  #-fsanitize=address

SRC = *.c ../Structures/*.c -lm `pkg-config --libs glib-2.0`

main:
	$(CC) $(CFLAGS)  $(SRC) -L ../libs -l:structures.a
 
all: main

clean:
	${RM} *.o 
	${RM} a.out 
#end
