#ifndef _MYSELECTIONSORT_INL_
#define _MYSELECTIONSORT_INL_

#include "MySelectionSort.h"
#include <vector>
using namespace std;

template<class T>
MySelectionSort<T>::MySelectionSort() {}

template<class T>
MySelectionSort<T>::~MySelectionSort() {}

template <class T>
void MySelectionSort<T>::SelectionSort(vector<T>& arr)
{
    if (arr.size() <= 1) return;

    int n = arr.size();
    int i, j, min_idx;

    // one by one move boundary of 
    // unsorted subarray 
    for (i = 0; i < n - 1; i++)
    {
        // find the minimum element in 
        // unsorted array 
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) min_idx = j;
        }

        // swap the found minimum element 
        // with the first element 
        swap(arr[min_idx], arr[i]);
    }
}

#endif