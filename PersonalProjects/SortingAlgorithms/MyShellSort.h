#pragma once
#ifndef _MYSHELLSORT_
#define _MYSHELLSORT_

#include <vector>
using namespace std;

template<class T>
class MyShellSort {
	public:
		MyShellSort();
		~MyShellSort();
		void ShellSort(vector<T>& arr);
	private:
};

#include "MyShellSort.inl"

#endif
