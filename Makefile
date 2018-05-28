# Makefile for character_sheet

CFLAGS = -std=gnu++11 -O2 -Wall -pedantic

main: main.cpp
	g++ -o main main.cpp $(CFLAGS)

clean:
	rm -rf *.exe* main *.o *.gch
