#ifndef _MYSHELLSORT_INL_
#define _MYSHELLSORT_INL_

#include "MyShellSort.h"
#include <vector>
using namespace std;

template<class T>
MyShellSort<T>::MyShellSort() {}

template<class T>
MyShellSort<T>::~MyShellSort() {}

template <class T>
void MyShellSort<T>::ShellSort(vector<T>& arr)
{
    if (arr.size() <= 1) return;

    int n = arr.size();

    // Start with a big gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted 
        for (int i = gap; i < n; i += 1) {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct 
            // location for a[i] is found
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
}

#endif