#ifndef _MYTIMSORT_INL_
#define _MYTIMSORT_INL_

#include "MyTimsort.h"
#include "MyInsertionSort.h"
#include "MyMergesort.h"
#include <vector>
#include <algorithm>
using namespace std;

template<class T>
MyTimsort<T>::MyTimsort() {}

template<class T>
MyTimsort<T>::~MyTimsort() {}

template <class T>
void MyTimsort<T>::Timsort(vector<T>& arr)
{
	if (arr.size() <= 1) return;

	MyInsertionSort<T> iSort;
	MyMergesort<T> mSort;

	//sort individual subarrays of size RUN with InsertionSort...
	for (size_t i = 0; i < arr.size(); i += RUN) {
		iSort.InsertionSort(arr, i, min((i+RUN-1), (arr.size() -1)));
	}

	//start merging from size RUN.
	for (size_t size = RUN; size < arr.size(); size = 2 * size) {
		//pick starting point of left sub array. We are going to merge arr[left..left+size-1] and arr[left+size, left+2*size-1]
		//after every merge, we increase left by 2*size
		for (size_t left = 0; left < arr.size(); left++) {
			//find end point of left sub array, mid+1 is starting point of right sub array
			int mid = left + size - 1;
			int right = min((left + 2 * size - 1), (arr.size() - 1));

			//merge arr[left..mid] & arr[mid+1..right]
			if (mid < right) {
				mSort.Merge(arr, left, mid, right);
			}
		}
	}
}

#endif