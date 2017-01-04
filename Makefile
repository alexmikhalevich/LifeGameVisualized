CC=g++
CFLAGS=-c -std=c++11 -Wall
LFLAGS=-lSDL2

all: main.o cvisualizer.o cfield.o
	$(CC) $(LFLAGS) cview.o cfield.o main.o clogic.o -o life
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
cvisualizer.o: cvisualizer.cpp
	$(CC) $(CFLAGS) cvisualizer.cpp
cfield.o: cfield.cpp
	$(CC) $(CFLAGS) cfield.cpp
clean:
	rm *.o life
