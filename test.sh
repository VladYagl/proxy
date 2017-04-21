#!/bin/bash

cd out

echo
echo
echo Compiling:
cmake ../

echo
echo
echo Making:
make

cd ..

echo
echo
echo Running:

./main

