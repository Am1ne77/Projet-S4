CC=gcc
MAKE=make
CFLAGS=`pkg-config --cflags glib-2.0` `pkg-config --cflags gtk+-3.0` -Wall -Wextra -D _GNU_SOURCE
LDLIBS=-lm `pkg-config --libs glib-2.0` `pkg-config --libs gtk+-3.0`

all: build

build:
	cd Structures && $(MAKE)
	cd Interpretor && $(MAKE)
	cd UI && $(MAKE)
	${CC} ./Structures/obj/* ./Interpretor/obj/* ./UI/obj/* $(CFLAGS) $(LDLIBS) ./UI/main.c -o underperl

clean:
	cd Structures && $(MAKE) clean
	cd Interpretor && $(MAKE) clean
	cd UI && $(MAKE) clean
	${RM} underperl
