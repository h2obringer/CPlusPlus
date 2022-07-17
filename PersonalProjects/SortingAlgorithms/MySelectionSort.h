#pragma once
#ifndef _MYSELECTIONSORT_
#define _MYSELECTIONSORT_

#include <vector>
using namespace std;

template<class T>
class MySelectionSort {
	public:
		MySelectionSort();
		~MySelectionSort();
		void SelectionSort(vector<T>& arr);
	private:
};

#include "MySelectionSort.inl"

#endif
