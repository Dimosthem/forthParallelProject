#ifndef AUXIILARY
#define AUXILIARY
#include <array>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>
#include <cstddef>        // std::size_t
#include <stdlib.h>
#include<iostream>
#include <omp.h>
//#include <sys/resource.h>
#include <bits/stdc++.h>
using namespace std;



enum Format {CSC, CSR};
vector<vector<int>> importFromFile(string fileName, Format format, int& K, int& N);
vector<vector<vector<int>>> blockMatrix(int k, int n, int K, int N,const vector<int>& arr1, const vector<int>& arr2);
vector<vector<int>> deblockMatrix(int k, int n, int K, int N, vector<vector<int>>& arrs1, vector<vector<int>>& arrs2);
vector<vector<int>> addMatrices(vector<int>& arr11, vector<int>& arr12, vector<int>& arr21, vector<int>& arr22);
int* vector2intArr(const vector<int>& arr);
int* initArray(int n, int b);
int* shrinkArr(int* arr, int& sz);
vector<int> intArr2Vector(int* arr, int sz);
int* expandArr(int* arr, int& sz);
int* vectorVector2intArr(const vector<vector<int>>& arr,int K, int column,int step, int blocksPerColumn, int cellsPerBlockedColumn, int& sz, int& newk, int& newK);
vector<vector<int>> intArr2VectorVector(int* arr, int sz);
void printVector(const vector<int>& v);
void printIntArr(const int* arr, int sz);
int* entireVectorVector2intArr(const vector<vector<int>>& arr, int& sz);
void saveVector(const vector<int>& v);
#endif