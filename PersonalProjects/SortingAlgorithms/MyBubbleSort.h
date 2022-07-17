#pragma once
#ifndef _MYBUBBLESORT_
#define _MYBUBBLESORT_

#include <vector>
using namespace std;

template<class T>
class MyBubbleSort {
public:
	MyBubbleSort();
	~MyBubbleSort();
	void BubbleSort(vector<T>& arr);
private:
};

#include "MyBubbleSort.inl"

#endif
