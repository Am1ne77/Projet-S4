CC=gcc
MAKE=make
CFLAGS=
LDFLAGS=

all: build

build:
	cd Structures && $(MAKE)
	cd Interpretor && $(MAKE)
	cd replace && $(MAKE)

clean:
	cd Structures && $(MAKE) clean
	cd Interpretor && $(MAKE) clean
	cd replace && $(MAKE) clean
	
