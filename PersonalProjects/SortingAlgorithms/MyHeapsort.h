#pragma once
#ifndef _MYHEAPSORT_
#define _MYHEAPSORT_

#include <vector>
using namespace std;

template<class T>
class MyHeapsort {
	public:
		MyHeapsort();
		~MyHeapsort();
		void Heapsort(vector<T>& arr);
	private:
		void Heapify(vector<T>& arr, int n, int i);
};

#include "MyHeapsort.inl"

#endif
