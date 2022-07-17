#ifndef _MYMERGESORT_INL_
#define _MYMERGESORT_INL_

#include "MyMergesort.h"
#include <vector>
using namespace std;

template<class T>
MyMergesort<T>::MyMergesort()
{
}

template<class T>
MyMergesort<T>::~MyMergesort()
{
}

template <class T>
void MyMergesort<T>::Merge(vector<T>& arr, int const left, int const mid, int const right)
{
	int const leftArrSize = mid - left + 1;
	int const rightArrSize = right - mid;

	//create temp arrays/vectors
	vector<T> leftArray(leftArrSize);
	vector<T> rightArray(rightArrSize);

	//copy data to temp arrays
	for (int i = 0; i < leftArrSize; i++) {
		leftArray[i] = arr[left + i];
	}
	for (int i = 0; i < rightArrSize; i++) {
		rightArray[i] = arr[mid + 1 + i];
	}

	int indexOfLeftArr = 0;
	int indexOfRightArr = 0;
	int indexOfMergedArr = left; //initial index of merged array

	while (indexOfLeftArr < leftArrSize && indexOfRightArr < rightArrSize) {
		if (leftArray[indexOfLeftArr] <= rightArray[indexOfRightArr]){
			arr[indexOfMergedArr] = leftArray[indexOfLeftArr];
			indexOfLeftArr++;
		}
		else
		{
			arr[indexOfMergedArr] = rightArray[indexOfRightArr];
			indexOfRightArr++;
		}
		indexOfMergedArr++;
	}

	//copy remaining elements of left[] if any
	while (indexOfLeftArr < leftArrSize) {
		arr[indexOfMergedArr] = leftArray[indexOfLeftArr];
		indexOfLeftArr++;
		indexOfMergedArr++;
	}

	//copy remaining elements of right[] if any
	while (indexOfRightArr < rightArrSize) {
		arr[indexOfMergedArr] = rightArray[indexOfRightArr];
		indexOfRightArr++;
		indexOfMergedArr++;
	}
}

template <class T>
void MyMergesort<T>::Mergesort(vector<T>& arr) {
	//base case
	if (arr.size() <= 1) return;

	Mergesort(arr, 0, arr.size() - 1);
}

template <class T>
void MyMergesort<T>::Mergesort(vector<T>& arr, int start, int end) {
	//base case
	if (start >= end) return;

	int mid = start + (end - start) / 2;
	Mergesort(arr, start, mid);
	Mergesort(arr, mid + 1, end);
	Merge(arr, start, mid, end);
}

#endif