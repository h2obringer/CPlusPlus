#ifndef _MYBUCKETSORT_INL_
#define _MYBUCKETSORT_INL_

#include "MyBucketSort.h"
#include "MyInsertionSort.h"
#include <vector>
using namespace std;

template<class T>
MyBucketSort<T>::MyBucketSort() {}

template<class T>
MyBucketSort<T>::~MyBucketSort() {}

template<class T>
void MyBucketSort<T>::BucketSort(vector<T>& arr, int num_buckets)
{

    //TODO: WE ARE GOING TO IMPLEMENT THIS SORT TYPE LATER...
    if (arr.size() <= 1) return;
    
    int n = arr.size();

    //1. create n empty buckets
    vector<vector<T>> bucket(n);

    //2. put array elements in different buckets
    //TODO
    for (int i = 0; i < n; i++) {
        int bucket_index = n * arr[i];
        bucket[bucket_index].push_back(arr[i]);
    }

    //3. sort individual buckets using insertion sort
    MyInsertionSort<float> sort;
    for (int i = 0; i < n; i++) {
        sort.InsertionSort(bucket[n]);
    }

    //4. Concatenate all buckets into arr
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bucket[i].size(); j++) {
            arr[index++] = bucket[i][j];
        }
    }
}

#endif