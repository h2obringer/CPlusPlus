#pragma once
#ifndef _MYTREESORT_
#define _MYTREESORT_

#include <vector>
using namespace std;

//Tree Sort can be improved to O(n log(n)) time complexity by using a self balancing binary tree instead of an unbalanced binary tree

template<class T>
struct Node {
	T key;
	Node* left;
	Node* right;
};

template<class T>
class MyTreeSort {
public:
	MyTreeSort();
	~MyTreeSort();
	void TreeSort(vector<T>& arr);
private:
	Node<T>* CreateNode(T item);
	Node<T>* InsertIntoTree(Node<T>* node, T key);
	void TraverseTreeInOrder(vector<T>& arr, Node<T>* root);
	void TraverseTreeInOrder(vector<T>& arr, Node<T>* root, int& index);
};

#include "MyTreeSort.inl"

#endif
