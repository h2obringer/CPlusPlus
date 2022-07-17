#ifndef _MYHEAPSORT_INL_
#define _MYHEAPSORT_INL_

#include "MyHeapsort.h"
#include <vector>
#include <algorithm>
using namespace std;

template<class T>
MyHeapsort<T>::MyHeapsort() {}

template<class T>
MyHeapsort<T>::~MyHeapsort() {}

template <class T>
void MyHeapsort<T>::Heapsort(vector<T>& arr)
{
	if (arr.size() <= 1) return;

	//build heap (rearrange array)
	for (int i = (arr.size() / 2) - 1; i >= 0; i--) {
		Heapify(arr, arr.size(), i);
	}

	//one by one extract an element from the heap
	for (int i = arr.size() - 1; i > 0; i--) {
		//move current root to the end
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap
		Heapify(arr, i, 0);
	}
}

//i = node (array index)
//n = size of heap
template <class T>
void MyHeapsort<T>::Heapify(vector<T>& arr, int n, int i)
{
	if (n <= 1) return;

	//initialize largest as root
	int largest = i;

	int left = (2 * i) + 1;
	int right = (2 * i) + 2;

	//if left child is larger than root
	if (left < n && arr[left] > arr[largest]) largest = left;

	//if right child is larger than largest so far
	if (right < n && arr[right] > arr[largest]) largest = right;

	//if largest is not root
	if (largest != i) {
		swap(arr[i], arr[largest]);

		//recursively feapify the affected subtree
		Heapify(arr, n, largest);
	}
}

#endif