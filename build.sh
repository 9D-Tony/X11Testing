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
    if g++ -o debug/mainX11.out X11Main.cpp -lX11;  then
    echo "debug build Successful"  && ./debug/mainX11.out;
    fi
    exit 1
fi

if [[ $1 -eq "release" ]]; then
    if g++ -o release/mainX11.out X11Main.cpp -O2 -lX11;  then
    echo "release build Successful"  && ./release/mainX11.out;
    fi
    exit 1
fi

if [[ $1 -eq "debug" ]]; then
    if g++ -o debug/mainX11.out X11Main.cpp -lX11;  then
    echo "debug build Successful"  && ./debug/mainX11.out;
    fi
    exit 1
fi
