#!/bin/bash

g++ -c  mainNotParallel.cpp

g++ -c  auxiliary.cpp

g++  -O3 -o serialProgram mainNotParallel.o auxiliary.o

