#pragma once

#ifndef _MYQUICKSORT_
#define _MYQUICKSORT_

#include <vector>
using namespace std;

template <class T>
class MyQuicksort {
	public:
		MyQuicksort();
		~MyQuicksort();
		void Quicksort(vector<T>& arr);
		void Quicksort(vector<T>& arr, int start, int end);

	private:
		int Partition(vector<T>& arr, int start, int end);
};

#include "MyQuicksort.inl"

#endif
