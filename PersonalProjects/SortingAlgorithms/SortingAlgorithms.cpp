// SortingAlgorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "MyQuicksort.h"
#include "MyMergesort.h"
#include "MyInsertionSort.h"
#include "MyTimsort.h"
#include "MyHeapsort.h"
#include "MyBubbleSort.h"
#include "MySelectionSort.h"
#include "MyTreeSort.h"
#include "MyShellSort.h"
#include "MyBucketSort.h"

using namespace std;

template<class T>
void PrintArray(vector<T> arr) {
	for (size_t i = 0; i < arr.size(); i++) {
		cout << arr[i] << ' ';
	}

	cout << endl;
}

int main()
{
	vector<int> test {8, 8, 8, 7, 5, 6, 9, 10, 1, 4, 2, 3};

    /*MyQuicksort<int> sort;
    sort.Quicksort(test);*/

	/*MyMergesort<int> sort;
	sort.Mergesort(test);*/

	/*MyInsertionSort<int> sort;
	sort.InsertionSort(test);*/

	/*MyTimsort<int> sort;
	sort.Timsort(test);*/

	/*MyHeapsort<int> sort;
	sort.Heapsort(test);*/

	/*MyBubbleSort<int> sort;
	sort.BubbleSort(test);*/

	/*MySelectionSort<int> sort;
	sort.SelectionSort(test);*/

	/*MyTreeSort<int> sort;
	sort.TreeSort(test);*/

	/*MyShellSort<int> sort;
	sort.ShellSort(test);*/

	MyBucketSort<int> sort;
	sort.BucketSort(test);

    PrintArray(test);

	return 0;
}