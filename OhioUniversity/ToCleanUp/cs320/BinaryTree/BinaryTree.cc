//Randy Obringer

#include <iostream>
#include "BinaryTree.h"
#include <stack>

using namespace std;

BinaryTree::BinaryTree(int data)
{
  data_ = data;
  left_ = right_ = NULL;
}

BinaryTree::~BinaryTree()
{
  if (left_ != NULL)
    delete left_;
  if (right_ != NULL)
    delete right_;
}

BinaryTree* BinaryTree::setLeft(BinaryTree *tree)
{
  BinaryTree* old_left = left_;
  left_ = tree;

  return old_left;
}

BinaryTree* BinaryTree::setRight(BinaryTree *tree)
{
  BinaryTree* old_right = right_;
  right_ = tree;

  return old_right;
}

void BinaryTree::printInOrderRecursive(BinaryTree *root)
{
  if(root != NULL){
    printInOrderRecursive(root->left_);
    cout << root->data_ << " ";
    printInOrderRecursive(root->right_);
  }
}

void BinaryTree::printInOrderIterative(BinaryTree* root)
{
  stack<BinaryTree*> stack1;
  bool done=false;

  while(!done){
    if(root!=NULL){
      stack1.push(root);
      root = root->left_;
    }else if(!stack1.empty()){
      root = stack1.top();
      stack1.pop();
      cout << root->data_ << " ";
      root = root->right_;
    }else if(stack1.empty()){
      done=true;
    }
  }
}

