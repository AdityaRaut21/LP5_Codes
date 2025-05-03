#include<iostream>
#include<omp.h>
#include<vector>

using namespace std;

void BubbleSort(vector<int>& arr){
	int n= arr.size();
	for(int i=0;i<n;i++){
		for(int j=0 ; j<n-i-1 ;j++){
			if(arr[j]>arr[j+1]){
				swap(arr[j],arr[j+1]);
			}
		}
	}
}

void pBubbleSort(vector<int>& arr){
	int n=arr.size();
	for(int i=0;i<n;++i){
		#pragma omp for
		for(int j=1;j<n;j+=2){
			if(arr[j]<arr[j-1]){
				swap(arr[j],arr[j-1]);
			}
		}

		#pragma omp barrier

		#pragma omp for
		for(int j=2;j<n;j+=2){
			if(arr[j]<arr[j-1]){
				swap(arr[j],arr[j-1]);
			}
		}
	}
}

void printArr(const vector<int>& arr){
	for(int i=0;i<arr.size();i++){
		cout<<arr[i]<<" ";
	}
}

int main(){

   int n;
   double st,et;
   cout<<"Enter no. of elements : "<<endl;
   cin>>n;


   vector<int>arr(n);
   for(int i=0;i<n;i++){
     cin>>arr[i];
   }

   st=omp_get_wtime();
   BubbleSort(arr);
   et=omp_get_wtime();

   printArr(arr);

   cout<<"Time required(sequential) : "<<et-st;

   arr.clear();

   for(int i=0;i<n;i++){
     cin>>arr[i];
   }

   st=omp_get_wtime();
   pBubbleSort(arr);
   et=omp_get_wtime();

   printArr(arr);

   cout<<"Time required(parallel) : "<<et-st;




   return 0;
}
