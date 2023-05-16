#!/bin/bash

if g++ -o build/mainX11.out X11Main.cpp -lX11;  then
    echo "Build Successful"  && ./build/mainX11.out;
fi
