CC      = g++
FLAGS   = --std=c++14 -g -Wall
HEADERS = pch.h.gch argh.h.gch
OBJECTS = main.o fs.o fslist.o graphics.o graphicslist.o os.o processor.o requests.o semver.o storage.o storagelist.o temperature.o utils.o

default: cgoggles

%.gch: %.h
	$(CC) $(FLAGS) -c $< -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

cgoggles: $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f cgoggles.exe
