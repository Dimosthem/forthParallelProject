#!/bin/bash

g++ -c -fopenmp mainParallel.cpp

g++ -c  auxiliary.cpp

g++  -O3 -fopenmp -o  openMPProgram mainParallel.o auxiliary.o

