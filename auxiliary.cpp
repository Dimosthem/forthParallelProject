#include "auxiliary.hpp"
vector<vector<int>> importFromFilee(string fileName, Format format){
	int dimension=0;
	bool symmetric = false;
	vector<int> arr1;
	vector<int> arr2;

	arr1.push_back(0);
	ifstream file(fileName);

	if (!file){
		cerr<<"Couldnt open the file"<<endl;
		vector<vector<int>> err;
		return err;
	}

	

	while(true){
		
		string line;
		getline(file, line);
		char s[28] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','p','r','s','t','y','u','w','z','%','-'};
		if (line.find_first_of(s)!=-1)
		{
			if((line.find("symmetric"))<100000 && !symmetric){
				
				symmetric = true;
				cout<<"The matrix you have loaded contains the flag [symmetric]"<<endl;
			}
			continue;    
		}else{
			istringstream stream(line);
			
			string dim;
			stream>>dim;
			cout<<dim<<endl;
			dimension = atoi(dim.c_str());
			cout<<dimension<<endl;
			
			break;
		}
	}
	
	
	vector<vector<int>> pnx(dimension);

	while(file){
		string strValue;
		string strIndex;
		file>>strIndex>>strValue;
		
		int value = atoi(strValue.c_str()) -1;
		int index = atoi(strIndex.c_str()) -1;
		//cout<<index<<" "<<value<<endl;
		if(index==-1 || value==-1){
			break;
		}
		
		pnx[index].push_back(value);

		if(symmetric){
			pnx[value].push_back(index);
		}
	}
	
	for(int i=0; i<dimension; i++){
		int size = pnx[i].size();
		
		if(size>0){
			arr1.push_back(size+arr1[i]);
			for (int j =0; j<size; j++){
				arr2.push_back(pnx[i][j]);
			}
		}else{
			arr1.push_back(arr1[i]);
		}
	}

	
	vector<vector<int>> result;
	result.push_back(arr1);
	result.push_back(arr2);


	return result;
}

vector<vector<int>> importFromFile(string fileName, Format format, int& K, int& N){
	int dimensionX = 0,  dimensionY = 0;
	vector<int> arr1;
	vector<int> arr2; 

	
	arr1.push_back(0);
    ifstream file(fileName);

	if (!file){
		cerr<<"Couldnt open the file"<<endl;
		vector<vector<int>> err;
		return err;
	}

	while (true){
		string line;
		getline(file, line);
		if(line[0]!='%')
		{
			istringstream stream(line);
			string s_r_dim;
			string s_c_dim;
			stream>>s_r_dim;
			stream>>s_c_dim;
			dimensionX = atoi(s_r_dim.c_str());
			dimensionY = atoi(s_c_dim.c_str());
			
			break;
		}
	}
	cout<<"DimensionX: "<<dimensionX<<" DimenstionY: "<<dimensionY<<endl;
	int dim = (format == CSC?dimensionY: dimensionX);
	int dim2 = (format == CSC?dimensionX: dimensionY);
	N = dim;
	K = dim2;
	vector<vector<int>> pnx(dim); 
	while (file)
	{
		string strRow, strColumn; 
		file >> strRow >> strColumn;
		int row = atoi(strRow.c_str()) -1;
		int column = atoi(strColumn.c_str()) -1;
		
		if(row==-1 || column==-1){
			break;
		}
		if (format == CSC)
			pnx[column].push_back(row);
		else
			pnx[row].push_back(column);
	}

	for (int i=0; i<dim; i++){
		int size = pnx[i].size();
		
		if(size>0){
			arr1.push_back(size+arr1[i]);
			for (int j =0; j<size; j++){
				arr2.push_back(pnx[i][j]);
			}
		}else{
			arr1.push_back(arr1[i]);
		}
	}
	vector<vector<int>> result ;
	result.push_back(arr1);
	result.push_back(arr2);
	return result;
}

void printVector(const  vector<int> & v){
	for (int i =0; i<v.size(); i++){
		cout<<v[i]<<" ";
	}
	cout<<endl;
}
vector<vector<vector<int>>> blockMatrix(int k, int n, int K, int N,const vector<int>& arr1,const vector<int>& arr2){
	//We are going for the vertical cut first 
	int verticalStep = K/(k+1);
	int horizontalStep = N/(n+1);
	cout<<"Horizontal step is "<<horizontalStep<<endl;
	vector<int> groups(k+1, 0);
	for (int i=1; i<=k; i++){
		groups[i] = i*verticalStep;
	}

	vector<vector<int>> arrs1(k+1);
	vector<vector<int>> arrs2(k+1);

	for(int i=0; i<arr1.size(); i++){
		
		if (i==0){
			for (int j = 0; j<k+1; j++){
				arrs1[j].push_back(0);
			}
			continue;
		}
		else{
			for (int j = 0; j<k+1; j++){
				arrs1[j].push_back(arrs1[j][i-1]);
			}
			int difference = arr1[i] - arr1[i-1];
			
			for (int j=0; j<difference; j++){
				int value = arr2[j + arr1[i-1]];
				
				for (int l = 0; l<groups.size(); l++){
					if (l<groups.size()-1){
						
						if (((value >= groups[l]) && (value < groups[l+1]))){
							
							arrs1[l][i] +=1 ;
							arrs2[l].push_back(value - groups[l]);
							break;
						}
					}
					else {   						//else isnt needed here
						arrs1[l][i] +=1 ;
						arrs2[l].push_back(value - groups[l]);
					}
				}
			}
		}
	}

	//end of the vertical cut
	//start of debugging of vertical cut
	cout<<"Start"<<endl;
	/*for (int j = 0; j<k+1; j++){
		printVector(arrs1[j]);
		printVector(arrs2[j]);
		cout<<endl;
	}	*/
	//end of debugging of the vertical cut

	vector<vector<int>> finalArrs1((k+1)*(n+1));
	vector<vector<int>> finalArrs2((k+1)*(n+1));
	for (int l = 0; l<(k+1)*(n+1); l++){
		finalArrs1[l].push_back(0);
	}
	for ( int i = 0; i < k+1 ; i++){
		
		int prevValue = 0;
		int p  = 0;
		int sub = 0;
		int dif = 0;
		for (int j = 1; j<arrs1[i].size(); j++){
			
			int currentSubArray = (j-1)/horizontalStep;
			
			
				if ( currentSubArray!= prevValue){
					if (p < n){

					
						prevValue = currentSubArray;
						p++;
						dif = arrs1[i][j-1] - sub;
						
						for (int l = 0; l<dif; l++){
							
							
							finalArrs2[p-1 + i*(n+1)].push_back(arrs2[i][l + sub]);
						}
						sub = arrs1[i][j-1];
					}
					
				}
				if ((j == (arrs1[i].size() - 1))){
					
					dif = arrs1[i][j] - sub;
					for (int l = 0; l<dif; l++){
						
						finalArrs2[p + i*(n+1)].push_back(arrs2[i][l + sub]);
					}
				}
				finalArrs1[p + i*(n+1)].push_back(arrs1[i][j] - sub);
				
				
			
		}
	}
	//start of debugging of whole cut
	cout<<"Final Start"<<endl;
/*	for (int j = 0; j<(k+1)*(n+1); j++){
		printVector(finalArrs1[j]);
		printVector(finalArrs2[j]);
		cout<<endl;
	}	*/
	//end of debugging of the whole cut

	vector<vector<vector<int>>> result;
	result.push_back(finalArrs1);
	result.push_back(finalArrs2);
	return result;  //mind that this could slow down the process, I am not sure
}

vector<vector<int>> deblockMatrix(int k, int n, int K, int N, vector<vector<int>>& arrs1, vector<vector<int>>& arrs2){
	int subArraysPerLine = arrs1.size()/(k+1);  // it could be just n+1
	vector<vector<int>> lineArrs1(n+1);
	vector<vector<int>> lineArrs2(n+1);
	int verticalStep = K/(k+1);
	for (int i= 0; i<n+1; i++){         //initialization 
		lineArrs1[i].push_back(0);
	}
	for ( int i = 0 ; i<n+1; i++){
		for (int j = 1; j<arrs1[i].size(); j++){
			
			for (int l=0; l<k+1; l++){
				if (l==0){
					lineArrs1[i].push_back(0);
				}
				
				int position = i + subArraysPerLine * l;
				lineArrs1[i][lineArrs1[i].size() - 1] += arrs1[position][j];
				int dif = arrs1[position][j] - arrs1[position][j - 1];
				for (int m=0; m<dif; m++){
					lineArrs2[i].push_back(arrs2[position][m+arrs1[position][j - 1]] + verticalStep*l);
				}
			}
		}
	}

	//First debugging of horizontal merging 
	/*cout<<"Horizontal Merging debugging"<<endl;
	for (int j = 0; j<(n+1); j++){
		printVector(lineArrs1[j]);
		printVector(lineArrs2[j]);
		cout<<endl;
	}*/
	//end of first debugging
	vector<int> finalArr1;
	finalArr1.push_back(0);
	vector<int> finalArr2;
	int prevNumberOfColumns = 0;
	for (int i =0; i<n+1; i++){
		for (int j=1 ; j < lineArrs1[i].size(); j++){
			finalArr1.push_back(lineArrs1[i][j] + prevNumberOfColumns);
			if(j == lineArrs1[i].size()-1){
				prevNumberOfColumns += lineArrs1[i][j];
			}
		}
		for (int j=0; j < lineArrs2[i].size(); j++){
			finalArr2.push_back(lineArrs2[i][j]);
		}
	}
	//final debugging
	//printVector(finalArr1);
	//printVector(finalArr2);

	vector<vector<int>> result;
	result.push_back(finalArr1);
	result.push_back(finalArr2);
	return result;
}
vector<vector<int>> addMatrices(vector<int>& arr11, vector<int>& arr12, vector<int>& arr21, vector<int>& arr22){
	
	int arr1Size = arr11.size();
	vector<int> finalArr1;
	vector<int> finalArr2; 
	finalArr1.push_back(0);
	for (int i =1; i<arr1Size; i++){
		finalArr1.push_back(finalArr1[finalArr1.size()-1]);  			//we could save time if we pre-allocated memory instead of pushing back
		int index1 = 0;
		int index2 = 0;
		int dif1 = arr11[i] - arr11[i-1];
		int dif2 = arr21[i] - arr21[i-1];
		//cout<<"dif1 "<<dif1<<endl;
		//cout<<"dif2 " <<dif2<<endl;

		while (true){
		//	cout<<"index1 "<<index1<<endl;
		//	cout<<"index2 "<<index2<<endl;
		//	cout<<endl;
			if(index1>=dif1 && index2>=dif2){
				break;
			}
			else if(index1>=dif1){
				finalArr1[i]+=1;
				finalArr2.push_back(arr22[index2 + arr21[i-1]]);
				index2++;
			}
			else if (index2 >= dif2){
				finalArr1[i]+=1;
				finalArr2.push_back(arr12[index1 + arr11[i-1]]);
				index1++;
			}
			else{
				if (arr12[index1 + arr11[i-1]] > arr22[index2 + arr21[i-1]]){
					finalArr1[i] +=1; 
					finalArr2.push_back(arr22[index2 + arr21[i-1]]);
					index2++;
				}
				else if (arr12[index1 + arr11[i-1]] < arr22[index2 + arr21[i-1]]){
					finalArr1[i] +=1; 
					finalArr2.push_back(arr12[index1 + arr11[i-1]]);
					index1++;
				}else{
					finalArr1[i] +=1; 
					finalArr2.push_back(arr12[index1 + arr11[i-1]]);
					index1++;
					index2++;
				}
			}
			
		}
	/*	finalArr1.push_back(arr11[i]+arr21[i]);
		int dif1 = arr11[i] - arr11[i-1];
		int dif2 = arr21[i] - arr21[i-1];
		for(int j=0; j<dif1; j++){
			finalArr2.push_back(arr12[j + arr11[i-1]]); // columns wont be sorted !!
		}
		for(int j=0; j<dif2; j++){
			finalArr2.push_back(arr22[j + arr21[i-1]]); // columns wont be sorted !!
		}*/
	}

	//debugging
	//printVector(finalArr1);
	//printVector(finalArr2);
	vector<vector<int>> result;
	result.push_back(finalArr1);
	result.push_back(finalArr2);
	return result;
}

int* vector2intArr(const vector<int>& arr){
	int* result = new int[arr.size()];
	for (int i=0; i<arr.size(); i++){
		result[i] = arr[i];
	}
	return result;
}
int* initArray(int n, int b){
	int* result = new int[n];
	for (int i=0; i<n; i++){
		result[i] = b;
	}
	return result;
}

int* shrinkArr(int* arr, int& sz){
	int index = sz;
	for (int i =0; i<sz; i++){
		if(arr[i]==-1){
			index = i;
			break;
		}
	}
	if (index == sz){
		return arr;
	}
	int* tmp = new int[index];
	for (int i=0; i<index; i++){
		tmp[i] = arr[i];
	}
	delete[] arr;
	
	sz = index;
	return tmp;
}
vector<int> intArr2Vector(int* arr, int sz){
	vector<int> result(sz);
	for (int i=0; i<sz; i++){
		result[i] = arr[i];
	}
	delete[] arr;
	return result;
}
int* expandArr(int* arr, int& sz){
	int* tmp = initArray(2*sz, -1);
	for (int i=0; i<sz; i++){
		tmp[i] = arr[i];
	}
	delete[] arr;
	sz *=2;
	return tmp;
}
int* vectorVector2intArr(const vector<vector<int>>& arr,int K, int column,int step, int blocksPerColumn,int cellsPerBlockedColumn, int& sz, int& newk, int& newK){
	int end;
	int final_sz=-1;
	if (column*blocksPerColumn + step*blocksPerColumn > arr.size() ){
		end = arr.size();
	//	newk =  (arr.size()/blocksPerColumn)/cellsPerBlockedColumn - 1;
	//	newK = arr.size()/blocksPerColumn + K%cellsPerBlockedColumn;
		newk =  ((arr.size() - column*blocksPerColumn)/blocksPerColumn) - 1;
		newK = ((arr.size() - column*blocksPerColumn)/blocksPerColumn)*cellsPerBlockedColumn + K%cellsPerBlockedColumn;
	}else if(column*blocksPerColumn + step*blocksPerColumn == arr.size()){
		end = column*blocksPerColumn + step*blocksPerColumn;
		newk = step - 1;
		newK = step*cellsPerBlockedColumn + K%cellsPerBlockedColumn;
	}else{
		end = column*blocksPerColumn + step*blocksPerColumn;
		newk = step - 1;
		newK = step*cellsPerBlockedColumn;
	}
	
	for (int i=column*blocksPerColumn; i<end; i++){
		final_sz += arr[i].size() + 1;
		
	}
	
	
	int* result = new int[final_sz];
	
	int counter = 0;
	for (int i=column*blocksPerColumn; i<end; i++){
		for (int j=0; j<arr[i].size(); j++){
			result[counter] = arr[i][j];
			counter++;
		}
		if (i < end-1){
			result[counter] = -1;
			counter++;
		}
	}
	sz = final_sz;
	return result;
}
vector<vector<int>> intArr2VectorVector(int* arr, int sz){
	vector<vector<int>> result;
	int counter=-1;
	
	for (int i =0; i<sz; i++){
		
		if (i==0 || arr[i]==-1){
			
			result.push_back(vector<int>());
			counter++;
			
			if (i==0 &&  arr[i]!=-1){
				result[counter].push_back(arr[i]);
			}
			else if (i==0 &&  arr[i]==-1){
				result.push_back(vector<int>());
				counter++;
			}
			continue;
		}
		
		result[counter].push_back(arr[i]);
		
	}	
	
	delete[] arr;
	return result;
}
void printIntArr(const int* arr, int sz){
	for (int i=0; i<sz; i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int* entireVectorVector2intArr(const vector<vector<int>>& arr, int& sz){
	int final_sz = -1;
	for (int i=0; i< arr.size(); i++){
		final_sz += arr[i].size() + 1;

	}
	sz = final_sz;
	int* res = new int[final_sz];
	int counter =0;
	for (int i=0; i< arr.size(); i++){
		for (int j=0; j< arr[i].size(); j++){
			res[counter] = arr[i][j];
			counter++;
		}
		if(i < arr.size()-1){
			res[counter] = -1;
			counter++;
		}
	}
	return res;
}
ofstream resultFile("resultFile.txt");
void saveVector(const vector<int>& v){
	
	for (int i =0; i<v.size(); i++){
		resultFile<<v[i]<<" ";
		if(i%50==0 && i!=0){
			resultFile<<endl;
		}
	}
	resultFile<<endl;
	resultFile<<endl;
	resultFile<<endl;
}