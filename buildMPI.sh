#!/bin/bash

mpic++ -c  mainOpenMPI.cpp

mpic++ -c  auxiliary.cpp

mpic++  -O3  -o mpiProgram mainOpenMPI.o auxiliary.o

