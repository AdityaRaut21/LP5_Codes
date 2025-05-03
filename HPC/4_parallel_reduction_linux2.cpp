#include<iostream>
#include<omp.h>
#include<vector>

using namespace std;
int maximum(vector<int>& arr){
	int max1=arr[0];
	int n=arr.size();
	#pragma omp parallel for reduction(max:max1)
	for(int i=0;i<n;i++){
		if(arr[i]>max1){
			max1=arr[i];
		}
	}

	return max1;
}

int minimum(vector<int>& arr){
	int min1=arr[0];
	int n=arr.size();
 	#pragma omp parallel for reduction(min:min1)
 	for(int i=0;i<n;i++){
 		if(arr[i]<min1){
 		 	min1=arr[i];
 		}
 	}
 	return min1;
}

int sum(vector<int>& arr){
	int sum=0;
	#pragma omp parallel for reduction(+:sum)
	for(int i=0;i<arr.size();i++){
		sum+=arr[i];
	}
	return sum;
}
double avg(vector<int>& arr){
	return (sum(arr)/arr.size());
}
int main(){
	int n;
	cout<<"Enter no.of elements : ";
	cin>>n;
	vector<int>arr(n);
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	int res=maximum(arr);
	cout<<"Maximum : "<<res<<endl;

	res=minimum(arr);
	cout<<"Minimum : "<<res<<endl;

	res=sum(arr);
	cout<<"Sum : "<<res<<endl;

	double avgRes=avg(arr);
	cout<<"Average : "<<avgRes<<endl;
	return 0;
}
