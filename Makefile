CC=g++
CFLAGS=-c -std=c++11 -Wall -fopenmp
LFLAGS=-lSDL2 -fopenmp

all: main.o cvisualizer.o cfield.o
	$(CC) $(LFLAGS) cvisualizer.o cfield.o main.o -o life
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
cvisualizer.o: cvisualizer.cpp
	$(CC) $(CFLAGS) cvisualizer.cpp
cfield.o: cfield.cpp
	$(CC) $(CFLAGS) cfield.cpp
clean:
	rm *.o life
