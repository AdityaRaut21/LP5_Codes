#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void parallelBubbleSort(vector<int>& arr) {

    int n = arr.size();
    for(int i=0; i<n; i++) {
        #pragma omp parallel for
        for(int j=0; j<n-i; j++) {
            if(arr[j] > arr[j+1]) {
                #pragma omp critical
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

int main() {
    int n;
    cout<<"Enter the size of array: ";
    cin>>n;
    vector<int> arr(n);
    cout<<"Enter the array elements: \n";
    for(int i=0; i<n; i++) {
        cin>>arr[i];
    }

    parallelBubbleSort(arr);

    cout<<"\nSorted array: ";
    for(int val:arr) cout<<val<<" ";
    cout<<endl;

    return 0;
}
