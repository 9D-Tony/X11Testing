#!/bin/bash

if [[ ! -e "build" ]]; then
    mkdir "build"
fi

if g++ -o build/mainX11.out X11Main.cpp -lX11;  then
    echo "Build Successful"  && ./build/mainX11.out;
fi
