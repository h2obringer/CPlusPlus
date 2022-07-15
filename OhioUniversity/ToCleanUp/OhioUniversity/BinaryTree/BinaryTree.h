/*Author: Randal Obringer
* Date Last Modified: ~2011
* Description: BinaryTree header.
*/

#ifndef BINARY_TREE_H__
#define BINARY_TREE_H__

class BinaryTree {
	public:
		BinaryTree(int data); 	//constructor
		~BinaryTree();			//destructor
		BinaryTree* setLeft(BinaryTree *tree);	//set the left branch of the current node
		BinaryTree* setRight(BinaryTree *tree);	//set the right branch of the current node

		void printInOrderRecursive(BinaryTree *root);	//print the tree in order recursively
		void printInOrderIterative(BinaryTree *root);	//print the tree in order iteratively
	private:
		int data_;			//the node data
		BinaryTree* left_; 	//pointer to left branch
		BinaryTree* right_; //pointer to right branch
};

#endif // BINARY_TREE_H__
