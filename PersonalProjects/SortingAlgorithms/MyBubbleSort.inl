#ifndef _MYBUBBLESORT_INL_
#define _MYBUBBLESORT_INL_

#include "MyBubbleSort.h"
#include <vector>
using namespace std;

template<class T>
MyBubbleSort<T>::MyBubbleSort() {}

template<class T>
MyBubbleSort<T>::~MyBubbleSort() {}

template <class T>
void MyBubbleSort<T>::BubbleSort(vector<T>& arr)
{
	if (arr.size() <= 1) return;

    int n = arr.size();
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // IF no two elements were swapped  
        // by inner loop, then break 
        if (swapped == false)
            break;
    }
}

#endif