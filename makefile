CC      = g++
FLAGS   = -std=c++14 -g -Wall
HEADERS = pch.h.gch argh.h.gch
OBJECTS = main.o fs.o fslist.o graphics.o graphicslist.o os.o processor.o chassis.o ram.o ramlist.o requests.o semver.o storage.o storagelist.o system.o temperature.o utils.o

default: cgoggles.exe

%.gch: %.h
	$(CC) $(FLAGS) -c $< -o $@

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

cgoggles.exe: $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $@

cgoggles.distrib.exe: $(OBJECTS)
	$(CC) $(FLAGS) -static-libgcc -static-libstdc++ $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f cgoggles.exe
