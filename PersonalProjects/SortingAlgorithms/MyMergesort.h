#pragma once

#ifndef _MYMERGESORT_
#define _MYMERGESORT_

#include <vector>
using namespace std;

template <class T>
class MyMergesort {
public:
	MyMergesort();
	~MyMergesort();
	void Mergesort(vector<T>& arr);
	void Merge(vector<T>& arr, int const left, int const mid, int const right); //make this public so we can make it available to Timsort

private:
	void Mergesort(vector<T>& arr, int start, int end);
};

#include "MyMergesort.inl"

#endif
