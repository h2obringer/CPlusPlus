#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <string>

using namespace std;

struct Tree_Node {
	string node;
	Tree_Node *lc; //left child
	Tree_Node *rs; //right sibling
};

#endif
