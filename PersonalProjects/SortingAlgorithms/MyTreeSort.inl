#ifndef _MYTREESORT_INL_
#define _MYTREESORT_INL_

#include "MyTreeSort.h"
#include <vector>
using namespace std;

template<class T>
MyTreeSort<T>::MyTreeSort() {}

template<class T>
MyTreeSort<T>::~MyTreeSort() {}

template <class T>
void MyTreeSort<T>::TreeSort(vector<T>& arr)
{
    if (arr.size() <= 1) return;

    int n = arr.size();
    Node<T>* root = NULL;
    
    //construct the BST
    root = InsertIntoTree(root, arr[0]);
    for (int i = 1; i < n; i++) {
        root = InsertIntoTree(root, arr[i]);
    }

    //store inorder traversal of the BST
    TraverseTreeInOrder(arr, root);
    
}

template<class T>
Node<T>* MyTreeSort<T>::CreateNode(T item) {
    Node<T>* temp = new Node<T>();
    temp->key = item;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

template <class T>
Node<T>* MyTreeSort<T>::InsertIntoTree(Node<T>* node, T key) {
    //if the tree is empty, return a new Node
    if (node == NULL) return CreateNode(key);

    //otherwise, recurse down the tree
    //TODO -> what if the key is equal?????????
    if (key <= node->key) {
        node->left = InsertIntoTree(node->left, key);
    }
    else if (key > node->key) {
        node->right = InsertIntoTree(node->right, key);
    }

    //return the unchanged node pointer
    return node;
}

template<class T>
void MyTreeSort<T>::TraverseTreeInOrder(vector<T>& arr, Node<T>* root)
{
    if (arr.size() <= 1) return;
    if (root != NULL) {
        int index = 0;
        TraverseTreeInOrder(arr, root, index);
    }
}

template<class T>
void MyTreeSort<T>::TraverseTreeInOrder(vector<T>& arr, Node<T>* root, int& index)
{
    if (arr.size() <= 1) return;
    if (root != NULL) {
        TraverseTreeInOrder(arr, root->left, index);
        arr[index++] = root->key;
        TraverseTreeInOrder(arr, root->right, index);
    }
}

#endif