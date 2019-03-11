CC    = g++
FLAGS = -g -c -Wall -std=c++11

cgoggles: pch.h.gch argh.h.gch
	$(CC) -g -Wall -std=c++11 -o cgoggles.exe main.cpp

pch.h.gch:
	$(CC) $(FLAGS) pch.h

argh.h.gch: pch.h.gch
	$(CC) $(FLAGS) argh.h
