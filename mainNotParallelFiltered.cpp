#include <iostream>
#include "auxiliary.hpp"
using namespace std;


void BMMSerialF(const vector<int>& ar11, const vector<int>& ar12, const vector<int>& ar21, const vector<int>& ar22 ,const vector<int>& v_f1, const vector<int>& v_f2,  vector<int>& finalAr1, vector<int>& finalAr2){
    int n1 = ar11.size();
    int n2 = ar21.size();
    int* arr11 = vector2intArr(ar11);
    int* arr12 = vector2intArr(ar12);
    int* arr21 = vector2intArr(ar21);
    int* arr22 = vector2intArr(ar22);
    int* f1 = vector2intArr(v_f1);
    int* f2 = vector2intArr(v_f2);
   // finalArr1.push_back(0);
    int* finalArr1 = initArray(n1,0);
    int arr2Sz = arr11[n1-1];
    int* finalArr2 = initArray(arr2Sz, -1);
    
    unsigned int arr2Counter = 0;
    for (int i=1; i<n1; i++){
        if(i%500==0)
            cout<<i<<endl;
        int dif1 = arr11[i] - arr11[i-1];

        int difF = f1[i] - f1[i-1];
        
       // if (i%500==0)
       //     cout<<"i is "<<i<<endl;
       // finalArr1.push_back(finalArr1[finalArr1.size()-1]);
        finalArr1[i] = finalArr1[i-1];
        
        //for (int j=1; j<n2; j++){
        for (int a=0; a<difF; a++){
            int j = f2[a + f1[i-1]] + 1;
            
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
    delete[] f1;
    delete[] f2;
    finalArr2 = shrinkArr(finalArr2,arr2Sz);
    //debugging
  //  printIntArr(finalArr1,n1);
  //  printIntArr(finalArr2,arr2Sz);
    //I suppose it's correct
    finalAr1 = intArr2Vector(finalArr1, n1);
    finalAr2 = intArr2Vector(finalArr2, arr2Sz);
}

int main(int argc, char *argv[]){
   
   
   
   string filename1;
   string filename2; 
   string filename3;
   
   if(argc == 4){
        filename1 = argv[1];
        filename2 = argv[2];
        filename3 = argv[3];
        
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
    const vector<vector<int>> f = importFromFile(filename3, CSR, K, N2);
    auto start = std::chrono::high_resolution_clock::now();
    
    
    vector<int> tmp1;
    vector<int> tmp2;
    BMMSerialF(mat1[0], mat1[1], mat2[0], mat2[1],f[0], f[1], tmp1, tmp2);
    saveVector(tmp1);
    saveVector(tmp2);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); 
    cout<<"Duration "<<duration.count()<<endl;
    //BMMSerial(mat1[0], mat1[1], mat2[0], mat2[1]);
    
    return 0;
}
