#!/bin/bash

FLAGS="--std=c++14 -g -Wall -Wno-unknown-pragmas"
HEADERS=(pch.h.gch argh.h.gch)
OBJECTS=(main.o fs.o fslist.o graphics.o graphicslist.o os.o processor.o requests.o semver.o storage.o storagelist.o temperature.o utils.o)

function join { local IFS="$1"; shift; echo "$*"; }

function compile { g++-8 $FLAGS -c $1 -o $2; }

function compileX { g++-8 $FLAGS $1 -o $2; }

if [ -z "$1" ]; then
    for i in ${HEADERS[@]}; do
        if [ ! -f $i ]; then
            echo "c++14    -c ${i//.h.gch/.h}"
            compile ${i//.h.gch/.h} $i
        fi
    done

    for i in ${OBJECTS[@]}; do
        echo "c++14    -c ${i//.o/.cpp}"
        compile ${i//.o/.cpp} $i
    done

    echo "c++14       cgoggles.exe"
    compileX "$(join " " ${OBJECTS[@]})" cgoggles.exe
    chmod 755 cgoggles.exe
elif [ "$1" == "clean" ]; then
    rm *.o
    rm *.gch
fi
