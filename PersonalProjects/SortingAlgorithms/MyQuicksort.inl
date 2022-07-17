#ifndef _MYQUICKSORT_INL_
#define _MYQUICKSORT_INL_

#include "MyQuicksort.h"
#include <vector>
using namespace std;

template<class T>
MyQuicksort<T>::MyQuicksort() {}

template<class T>
MyQuicksort<T>::~MyQuicksort() {}

template <class T>
void MyQuicksort<T>::Quicksort(vector<T> &arr)
{
	if (arr.size() <= 1) return;
	
	Quicksort(arr, 0, arr.size() - 1);
}

template <class T>
void MyQuicksort<T>::Quicksort(vector<T> &arr, int start, int end) {
	//base case
	if (start >= end) return;

	//partitioning the array
	int p = Partition(arr, start, end);

	//sorting the left part
	Quicksort(arr, start, p - 1);

	//sorting the right part
	Quicksort(arr, p + 1, end);
}

template <class T>
int MyQuicksort<T>::Partition(vector<T> &arr, int start, int end) {
	int pivot = arr[start];
	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if (arr[i] <= pivot) count++;
	}

	//giving pivot element its correct position
	int pivotIndex = start + count;
	swap(arr[pivotIndex], arr[start]);

	//sorting left and right parts of the pivot element
	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {
		while (arr[i] <= pivot) {
			i++;
		}

		while (arr[j] > pivot) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(arr[i++], arr[j--]);
		}
	}

	return pivotIndex;
}

#endif