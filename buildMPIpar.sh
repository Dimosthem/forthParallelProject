#!/bin/bash

mpic++ -c -fopenmp mainOpenMPIparallel.cpp

mpic++ -c  auxiliary.cpp

mpic++  -O3  -fopenmp -o mpiProgramPar mainOpenMPIparallel.o auxiliary.o

