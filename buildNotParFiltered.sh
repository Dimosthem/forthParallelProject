#!/bin/bash

g++ -c  mainNotParallelFiltered.cpp

g++ -c  auxiliary.cpp

g++  -O3 -o serialProgramFiltered mainNotParallelFiltered.o auxiliary.o

