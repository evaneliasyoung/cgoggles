CC    = g++
FLAGS = -g -c -Wall -std=c++11

cgoggles: pch.h.gch argh.h.gch os.o utils.o
	$(CC) -g -Wall -std=c++11 -o cgoggles.exe main.cpp os.o utils.o

os.o:
	$(CC) $(FLAGS) -o os.o os.cpp

utils.o:
	$(CC) $(FLAGS) -o utils.o utils.cpp

pch.h.gch:
	$(CC) $(FLAGS) pch.h

argh.h.gch: pch.h.gch
	$(CC) $(FLAGS) argh.h
