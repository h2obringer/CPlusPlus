#pragma once
#ifndef _MYINSERTIONSORT_
#define _MYINSERTIONSORT_

#include <vector>
using namespace std;

template<class T>
class MyInsertionSort {
	public:
		MyInsertionSort();
		~MyInsertionSort();
		void InsertionSort(vector<T>& arr);
		void InsertionSort(vector<T>& arr, int left, int right);
};

#include "MyInsertionSort.inl"

#endif