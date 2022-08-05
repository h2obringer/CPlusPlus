#pragma once
#ifndef _MYBUCKETSORT_
#define _MYBUCKETSORT_

#include <vector>
using namespace std;

template<class T>
class MyBucketSort {
public:
	MyBucketSort();
	~MyBucketSort();
	void BucketSort(vector<T>& arr, int num_buckets);
private:
};

#include "MyBucketSort.inl"

#endif