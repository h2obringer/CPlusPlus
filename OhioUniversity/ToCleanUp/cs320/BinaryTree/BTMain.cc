//Randy Obringer

#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main(int argc, char** argv)
{
  /** Create the following tree:
              2
          1       4
                3    5
   */
  BinaryTree* root;
  BinaryTree* t1 = new BinaryTree(1);
  BinaryTree* t2 = new BinaryTree(2);
  BinaryTree* t3 = new BinaryTree(3);
  BinaryTree* t4 = new BinaryTree(4);
  BinaryTree* t5 = new BinaryTree(5);
  root=t2;

  t4->setLeft(t3);
  t4->setRight(t5);
  t2->setLeft(t1);
  t2->setRight(t4);

  t2->printInOrderRecursive(root);
  cout << endl;

  root=t2;

  t2->printInOrderIterative(root);
  cout << endl;

  delete t2;

  return 0;
}
