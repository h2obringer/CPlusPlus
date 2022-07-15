/*Author: Randal Obringer
* Date Last Modified: ~2011
* Description: BinaryTree implementation.
*/
#include <iostream>
#include "BinaryTree.h"
#include <stack>

using namespace std;

//constructor
BinaryTree::BinaryTree(int data){
	data_ = data;
	left_ = right_ = NULL;
}

//destructor - calling delete on the root will delete all of its branches as well 
//	effectively deleting the whole structure from memory
BinaryTree::~BinaryTree(){
	if (left_ != NULL){
		cout << "Deleting " << left_->data_;
		delete left_;
	}
	if (right_ != NULL){
		cout << "Deleting " << right_->data_;
		delete right_;
	}
}

//set the current node's left branch to another tree or node
BinaryTree* BinaryTree::setLeft(BinaryTree *tree){
	BinaryTree* old_left = left_;
	left_ = tree;

	return old_left;
}

//set the current node's right branch to another tree or node
BinaryTree* BinaryTree::setRight(BinaryTree *tree){
	BinaryTree* old_right = right_;
	right_ = tree;

	return old_right;
}

//recursively print the tree in order as opposed to pre-print or post-print
void BinaryTree::printInOrderRecursive(BinaryTree *root){
	if(root != NULL){
		printInOrderRecursive(root->left_);
		cout << root->data_ << " ";
		printInOrderRecursive(root->right_);
	}
}

//iteratively print the tree in order as opposed to pre-print or post-print
void BinaryTree::printInOrderIterative(BinaryTree* root){
	stack<BinaryTree*> stack1;

	while(!stack1.empty()){
		if(root!=NULL){
			stack1.push(root);
			root = root->left_;
		}else{
			root = stack1.top();
			stack1.pop();
			cout << root->data_ << " ";
			root = root->right_;
		}
	}
}

