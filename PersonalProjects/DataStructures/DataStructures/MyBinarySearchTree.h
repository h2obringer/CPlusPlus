#ifndef _MYBINARYSEARCHTREE_
#define _MYBINARYSEARCHTREE_

class MyBinarySearchTreeNode {
public:
	MyBinarySearchTreeNode(int value);
	~MyBinarySearchTreeNode();
	MyBinarySearchTreeNode* insert(MyBinarySearchTreeNode* root, int value);
	bool contains(MyBinarySearchTreeNode* root, int value);
private:
	int value;
	MyBinarySearchTreeNode* left;
	MyBinarySearchTreeNode* right;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MyBinarySearchTreeNode::MyBinarySearchTreeNode(int value) {
	this->value = value;
	left = right = NULL;
}

MyBinarySearchTreeNode::~MyBinarySearchTreeNode(){ }

MyBinarySearchTreeNode* MyBinarySearchTreeNode::insert(MyBinarySearchTreeNode* root, int value) {
	if (root == NULL) {
		root = new MyBinarySearchTreeNode(value);
		return root;
	}

	if (root->value <= value) {
		root->left = insert(root->left, value);
	} else {
		root->right = insert(root->right, value);
	}

	return root;
}

bool MyBinarySearchTreeNode::contains(MyBinarySearchTreeNode* root, int value) {
	if (root == NULL) return false;
	if (root->value == value) return true;

	if (root->value <= value)
	{
	}
	else
	{

	}
}

#endif