#Makefile
CC = gcc 
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -O3 -export-dynamic -g
LDLIBS = `pkg-config --libs gtk+-3.0` 


SRC = *.c
DST = main

main: 
	$(CC) $(SRC) $(CFLAGS) $(LDLIBS) -lm -o $(DST)

clean:
	${RM} $(DST)
	${RM} *.o

#end
