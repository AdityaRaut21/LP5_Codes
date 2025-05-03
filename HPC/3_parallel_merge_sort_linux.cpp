#include<iostream>
#include<omp.h>
#include<vector>

using namespace std;

void merge(vector<int>& arr,int low,int mid , int high){
	int n1=mid-low +1;
	int n2=high-mid;

	vector<int>left(n1);
	vector<int>right(n2);

	for(int i=0;i<n1;i++){
		left[i]=arr[low+i];
	}

	for(int j=0;j<n2;j++){
		right[j]=arr[mid+1+j];
	}

	int i=0 ,j=0,k=low;

	while(i<n1 && j<n2){
		if(left[i]<=right[j]){
			arr[k]=left[i];
			i++;
			k++;
		}
		else{
			arr[k]=right[j];
			j++;
			k++;
		}
	}

	while(i<n1){
		arr[k]=left[i];
		i++;
		k++;
	}
	while(j<n2){
		arr[k]=right[j];
		j++;
		k++;
	}
}

void mergeSort(vector<int>& arr,int low,int high){
if(low<high){
	int mid=(low + high)/2;
	mergeSort(arr,low,mid);
	mergeSort(arr,mid+1,high);
	merge(arr,low,mid,high);

}
}

void pmergeSort(vector<int>& arr,int low,int high){
	if(low<high){
		int mid=(low+high)/2;
		#pragma omp parallel sections
		{
			#pragma omp section
			pmergeSort(arr,low,mid);

			#pragma omp section
			pmergeSort(arr,mid+1,high);
		}

		merge(arr,low,mid,high);


	}
}

void printArr(const vector<int>& arr){
	for(int i=0;i<arr.size();i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
int main(){
	int n;
	double st,et;
	cout<<"Enter no. of elements : ";
	cin>>n;

	vector<int>arr(n);

	for(int i=0;i<n;i++){
		cin>>arr[i];
	}

	st=omp_get_wtime();
	mergeSort(arr,0,n-1);
	et=omp_get_wtime();

	printArr(arr);

	cout<<"Time required(sequential) : "<<et-st<<endl;

	arr.clear();

	for(int i=0;i<n;i++){
		cin>>arr[i];
	}

	st=omp_get_wtime();
	pmergeSort(arr,0,n-1);
	et=omp_get_wtime();

	printArr(arr);

	cout<<endl;

	cout<<"Time required(parallal) : "<<et-st<<endl;



	return 0;
}
