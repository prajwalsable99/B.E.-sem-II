
//#include <iostream>
//#include <omp.h>
//#include <climits>
//#include <cstdlib>
//#include <chrono>
//#include <ctime>
#include<bits/stdc++.h>
using namespace std;


int min_reduction(int arr[], int n) {
	
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] < min_value) {
  	min_value = arr[i];
	}
  }
  return min_value;
}

int max_reduction(int arr[], int n) {
  int max_value = INT_MIN;
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] > max_value) {
  	max_value = arr[i];
	}
  }
  return max_value;
}

int sum_reduction(int arr[], int n) {
  int sum = 0;
   #pragma omp parallel for reduction(+: sum)
   for (int i = 0; i < n; i++) {
	sum += arr[i];
  }
  return sum;
}

int average_reduction(int arr[], int n) {
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
	sum += arr[i];
  }
  return sum/n;
}

int main() {
    int *arr,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    
    int lb=0;
    int ub=n;
	arr=new int[n];
    
    for(int i=0;i<n;i++)
    {
  	 arr[i]=(rand() % (ub - lb + 1));
    }
	for(int i=0;i<n;i++)
    {
  	 	cout<<arr[i]<<" ";
    }
    cout<<endl;
    
    auto start = chrono::steady_clock::now();
    	cout<<"min ="<< min_reduction(arr, n)<<endl;
    auto end = chrono::steady_clock::now();
	cout << "Elapsed time in microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count()<< " microsecs" << endl;
 	
 	start = chrono::steady_clock::now();
 		cout<<"max ="<< max_reduction(arr, n)<<endl;
 	end = chrono::steady_clock::now();
	cout << "Elapsed time in microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count()<< " microsecs" << endl;
 	
 	
 	start = chrono::steady_clock::now();
  		cout<<"sum ="<<sum_reduction(arr, n)<<endl;
  	end = chrono::steady_clock::now();
	cout << "Elapsed time in microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count()<< " microsecs" << endl;
 	
  	
  	start = chrono::steady_clock::now();
  		cout<<"avg ="<<average_reduction(arr, n)<<endl;
  	end = chrono::steady_clock::now();
	cout << "Elapsed time in microseconds: " << chrono::duration_cast<chrono::microseconds>(end - start).count()<< " microsecs" << endl;
 	
}
