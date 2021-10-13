#include <iostream>
#include "auxiliary.hpp"
using namespace std;


void BMMSerial(const vector<int>& ar11, const vector<int>& ar12, const vector<int>& ar21, const vector<int>& ar22 , vector<int>& finalAr1, vector<int>& finalAr2){
    int n1 = ar11.size();
    int n2 = ar21.size();
    int* arr11 = vector2intArr(ar11);
    int* arr12 = vector2intArr(ar12);
    int* arr21 = vector2intArr(ar21);
    int* arr22 = vector2intArr(ar22);
   // finalArr1.push_back(0);
    int* finalArr1 = initArray(n1,0);
    int arr2Sz = arr11[n1-1];
    int* finalArr2 = initArray(arr2Sz, -1);
    
    unsigned int arr2Counter = 0;
    
    for (int i=1; i<n1; i++){
        int dif1 = arr11[i] - arr11[i-1];
       // if (i%500==0)
       //     cout<<"i is "<<i<<endl;
       // finalArr1.push_back(finalArr1[finalArr1.size()-1]);
        finalArr1[i] = finalArr1[i-1];
        
        for (int j=1; j<n2; j++){
            int dif2 = arr21[j] - arr21[j-1];
            unsigned int index1 = 0;
            unsigned int index2 = 0;
            while (true){
                
                if (index1 >= dif1 || index2 >= dif2){
                    break;
                
                } else if(arr12[index1 + arr11[i-1]] > arr22[index2 + arr21[j-1]]){
                    index2++;
                } else if(arr12[index1 + arr11[i-1]] < arr22[index2 + arr21[j-1]]){
                    index1++;
                }else{
                    finalArr1[i]+=1;
                    finalArr2[arr2Counter]=j-1;
                    arr2Counter++;
                    if(arr2Counter == arr2Sz){
                        finalArr2 = expandArr(finalArr2, arr2Sz);
                    }
                    break;
                }
                
            }
        }

    }
    
    delete[] arr11;
    delete[] arr12;
    delete[] arr21;
    delete[] arr22;
    finalArr2 = shrinkArr(finalArr2,arr2Sz);
    //debugging
  //  printIntArr(finalArr1,n1);
  //  printIntArr(finalArr2,arr2Sz);
    //I suppose it's correct
    finalAr1 = intArr2Vector(finalArr1, n1);
    finalAr2 = intArr2Vector(finalArr2, arr2Sz);
}
vector<vector<int>> BMMBlockedParallel(int k, int n, int K, int N1,int N2, const vector<vector<vector<int>>>& arrs1, const vector<vector<vector<int>>>& arrs2){
    
    vector<vector<int>> finalBlockedArr1((n+1)*(n+1));
    vector<vector<int>> finalBlockedArr2((n+1)*(n+1));
    #pragma omp parallel for
    for (int i=0; i<n+1; i++){
        //if(i%500==0)
        cout<<"The i is "<<i<<endl;
        for (int j=0; j<n+1; j++){
            vector<vector<int>> tmp1(k+1);
            vector<vector<int>> tmp2(k+1);
            
            for (int l=0; l<k+1; l++){
                if (arrs1[1][i+(n+1)*l].size() == 0 || arrs2[1][j+(n+1)*l].size() == 0){
                    for (int m =0; m< arrs1[0][i+(n+1)*l].size(); m++){
                        tmp1[l].push_back(0);
                    }
                    
                }else{
                   // cout<<"This is what gets reserved "<<(i+(n+1)*l)<<endl;
                   tmp1[l].reserve(arrs1[0][i+(n+1)*l].size());
                   tmp2[l].reserve(100);
                   
                   BMMSerial(arrs1[0][i+(n+1)*l],arrs1[1][i+(n+1)*l],arrs2[0][j+(n+1)*l],arrs2[1][j+(n+1)*l], tmp1[l], tmp2[l]);
                   
                   
                }
            }
            vector<int> sum1;
            
            for (int m=0; m<arrs1[0][i].size(); m++){
                sum1.push_back(0);
            }
            
            vector<int> sum2;
            for (int l=0; l<k+1; l++){
              //  cout<<"The l is "<<l<<endl;
              //  printVector(tmp1[l]);
              //  printVector(tmp2[l]);
                
                vector<vector<int>> sum = addMatrices(sum1, sum2, tmp1[l], tmp2[l]);
                sum1 = sum[0];
                sum2 = sum[1];
            }
            
            finalBlockedArr1[i + j*(n+1)] = sum1;
            finalBlockedArr2[i + j*(n+1)] = sum2;
            
        }
    }
    
    vector<vector<int>> result = deblockMatrix(n, n, N2, N1, finalBlockedArr1, finalBlockedArr2);
   // printVector(result[0]);
   // printVector(result[1]);
    return result;
    
}
int main(int argc, char *argv[]){
   string filename1;
   string filename2; 
   int k;
   int n;
   if(argc == 5){
        filename1 = argv[1];
        filename2 = argv[2];
        k = atoi(argv[3]);
        n = atoi(argv[4]);
    }
    else{
        cout<<"Wrong parameters given"<<endl;
        return 1;
    }
    int K;
    int N1;
    int N2;
    const vector<vector<int>> mat1 = importFromFile(filename1, CSR, K, N1);
    const vector<vector<int>> mat2 = importFromFile(filename2, CSC, K, N2);
    
    const vector<vector<vector<int>>> pinax1 = blockMatrix(k,n,K, N1 , mat1[0], mat1[1]);
    const vector<vector<vector<int>>> pinax2 = blockMatrix(k,n,K, N2 , mat2[0], mat2[1]);
    auto start = std::chrono::high_resolution_clock::now();
    vector<vector<int>> result = BMMBlockedParallel(k,n,K, N1,N2,pinax1, pinax2);
    saveVector(result[0]);
    saveVector(result[1]);
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); 
    cout<<"Duration "<<duration.count()<<endl;
    
    
    return 0;
}
