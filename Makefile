CC=gcc
MAKE=make
CFLAGS=
LDFLAGS=

all: build

build:
	cd Structures && $(MAKE)
	cd Interpretor && $(MAKE)
	cd UI && $(MAKE)

clean:
	cd Structures && $(MAKE) clean
	cd Interpretor && $(MAKE) clean
	cd UI && $(MAKE) clean
	
