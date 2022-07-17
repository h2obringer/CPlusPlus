#ifndef _MYINSERTIONSORT_INL_
#define _MYINSERTIONSORT_INL_

#include "MyInsertionSort.h"
#include <vector>
using namespace std;

template<class T>
MyInsertionSort<T>::MyInsertionSort() {}

template<class T>
MyInsertionSort<T>::~MyInsertionSort() {}

template<class T>
void MyInsertionSort<T>::InsertionSort(vector<T>& arr) {
	if (arr.size() <= 1) return;

	InsertionSort(arr, 0, arr.size() - 1);
}

template<class T>
void MyInsertionSort<T>::InsertionSort(vector<T>& arr, int left, int right) {
	if (arr.size() <= 1) return;

	for (int i = left + 1; i <= right; i++) {
		int key = arr[i];
		int j = i - 1;

		//move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
		while (j >= left && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

#endif