#!/bin/sh
set -e

#Create/clean out
mkdir -p build
rm -rf build/*

#Generate build files
cd build
cmake -G "Unix Makefiles" ..

#MAKE!
cmake --build . --target opene2140 -- -j 2
