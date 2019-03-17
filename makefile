CC      = g++
HEADERS = pch.h argh.h
OBJECTS = main.o os.o processor.o requests.o semver.o temperature.o utils.o

default: cgoggles

%.o: %.c $(HEADERS)
	$(CC) -g -c -Wall -std=c++11 $< -o $@

cgoggles: $(OBJECTS)
	$(CC) -g -Wall -std=c++11 $(OBJECTS) -o $@

clean:
	-rm -f $(OBJECTS)
	-rm -f cgoggles.exe
