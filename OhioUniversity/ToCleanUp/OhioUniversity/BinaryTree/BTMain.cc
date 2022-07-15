/*Author: Randal Obringer
* Date Last Modified: ~2011
* Description: Create a binary tree to store numbers. Has mechanism to print the tree in order 
*	both iteratively and recursively.
*/

#include <iostream>
#include "BinaryTree.h"

using namespace std;

int main(int argc, char** argv){
	/** Create the following tree:
              2
          1       4
                3    5
	*/
	//first create the nodes
	BinaryTree* root;
	BinaryTree* t1 = new BinaryTree(1);
	BinaryTree* t2 = new BinaryTree(2);
	BinaryTree* t3 = new BinaryTree(3);
	BinaryTree* t4 = new BinaryTree(4);
	BinaryTree* t5 = new BinaryTree(5);
	root=t2;
	//build the appropriate tree structure out of the nodes
	t4->setLeft(t3);
	t4->setRight(t5);
	t2->setLeft(t1);
	t2->setRight(t4);
  
	//print the tree recursively in order
	t2->printInOrderRecursive(root);
	cout << endl;

	root=t2;
	//print the tree iteratively in order
	t2->printInOrderIterative(root);
	cout << endl;

	delete root;

	return 0;
}
