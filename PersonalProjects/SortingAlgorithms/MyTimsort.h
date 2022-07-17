#pragma once
#ifndef _MYTIMSORT_
#define _MYTIMSORT_

#include <vector>
using namespace std;

const int RUN = 32; //RUN should be a power of 2 to make Timsort the most efficient it can be... this value is usally 32 or 64...

template<class T>
class MyTimsort {
public:
	MyTimsort();
	~MyTimsort();
	void Timsort(vector<T>& arr);
};

#include "MyTimsort.inl"

#endif
