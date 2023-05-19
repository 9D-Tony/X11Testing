#!/bin/bash

#if no debug and release folders in directory then create them
if [[ ! -e "debug" ]]; then
    mkdir "debug"
fi

if [[ ! -e "release" ]]; then
    mkdir "release"
fi

#check for arguments, if no arguments then build debug 
#then run application
if [[ -z $1 ]]; then
    if g++ -o debug/mainX11.out X11Main.cpp -lX11 -Wpointer-arith -g;  then
    echo "debug build successful"  && ./debug/mainX11.out;
    fi
    exit 1
fi

if [[ $1 == "release" ]]; then
    if g++ -o release/mainX11.out X11Main.cpp -O2 -lX11 -Wpointer-arith;  then
    echo "release build successful"  && ./release/mainX11.out;
    fi
    exit 1
fi

if [[ $1 == "debug" ]]; then
    if g++ -o debug/mainX11.out X11Main.cpp -lX11 -Wpointer-arith -g;  then
    echo "debug build successful"  && ./debug/mainX11.out;
    fi
    exit 1
fi
