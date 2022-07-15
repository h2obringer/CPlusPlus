//Randy Obringer

#ifndef BINARY_TREE_H__
#define BINARY_TREE_H__

class BinaryTree {
  int data_;
  BinaryTree* left_;
  BinaryTree* right_;

public:
  BinaryTree(int data);
  ~BinaryTree();

  
  
  BinaryTree* setLeft(BinaryTree *tree);
  BinaryTree* setRight(BinaryTree *tree);

  void printInOrderRecursive(BinaryTree *root);
  void printInOrderIterative(BinaryTree *root);
};

#endif // BINARY_TREE_H__
