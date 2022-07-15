//******************************************************************
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Program: main.cc
//
//  Description: Read tree data structure to build a tree. See assumptions below.
//		Print percentage of monkey on the tree, # of monkeys in the tree, # of monkeys
//		on leaves in the tree, and # of hungry monkeys on the tree.
//
//  Assumptions: We are given a well-formed tree. Every node in the 
//    	tree will be either "empty","monkey", or "fruit"
//
//  Last updated: 4/12/11
//
//******************************************************************

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Tree_Node.h"
#include "MonkeyBusiness.h"

//output the tree to the given output method
void print_tree(Tree_Node *r,ostream &out) {
	if (r==NULL) return;
		out << "(" << r->node;
	for (Tree_Node *n=r->lc;n!=NULL;n=n->rs) {
		out << ",";
		print_tree(n,out);
	}
	out << ")";
}

//build a tree from the given input method
Tree_Node* read_tree(istream &in) {
	char c;
	if (in.peek()=='(') {
		in.get(c);
		string name;
		while (isalpha(in.peek())) {
			in.get(c);
			name+=c;
		}
		Tree_Node *r=new Tree_Node;
		r->node = name;
		r->lc=NULL;
		r->rs=NULL;
		Tree_Node* curr=NULL;
		while (in.peek()==',') {
			in.get(c);
			Tree_Node *l = read_tree(in);
			if (curr==NULL) {
				r->lc= l;
				curr=l;
			} else {
				curr->rs = l;
				curr=l;
			}
		}
		if (in.peek()==')') {
			in.get(c);
			return r;
		} 
	}
}

int main() {
	
	cout << "Enter a tree structure to be read" << endl;
	//Test cases:
	//1. (empty,(monkey,(empty),(fruit,(monkey),(monkey))),(monkey,(monkey,(empty),(fruit),(fruit),(fruit)),(monkey,(monkey),(fruit),(fruit),(fruit)),(fruit,(fruit),(fruit),(monkey))))
	//2. (empty,(monkey,(empty,(monkey)),(monkey,(monkey),(empty)),(fruit,(empty),(fruit),(empty),(fruit)),(monkey,(fruit),(fruit))),(fruit,(monkey,(empty),(monkey),(empty),(fruit)),
	//	(empty,(fruit),(fruit)),(empty)),(fruit,(fruit,(empty)),(fruit,(empty),(empty),(monkey)),(fruit,(empty),(fruit)),(monkey,(fruit),(monkey),(monkey))))
	//3. (monkey,(fruit,(monkey),(empty),(monkey,(fruit),(fruit)),(monkey,(fruit),(monkey))))
	//4. (fruit,(monkey,(monkey,(fruit),(monkey),(empty)),(monkey,(fruit),(empty),(empty),(fruit)),(monkey,(empty))),(monkey),(empty,(fruit,(empty))),(empty,(monkey,(fruit),(empty)),
	//	(monkey,(monkey)),(empty,(empty)),(fruit,(fruit))))
	//5. (fruit,(fruit,(fruit,(empty),(fruit),(fruit)),(fruit)),(fruit,(empty),(fruit,(monkey),(empty)),(monkey,(fruit),(fruit))),(empty,(empty,(empty),(fruit)),(fruit,(empty)),
	//	(monkey,(fruit)),(monkey,(empty),(fruit),(monkey))))
	//6. (empty,(monkey,(fruit,(empty)),(empty,(monkey),(empty),(monkey),(empty))))
	//7. (fruit,(empty,(empty,(fruit),(empty)),(empty)),(monkey,(fruit,(empty),(empty),(fruit)),(monkey,(monkey)),(fruit,(fruit),(fruit)),(monkey,(empty),(monkey),(fruit))),
	//	(fruit,(monkey,(empty),(fruit),(fruit)),(monkey),(fruit,(fruit),(monkey)),(fruit,(fruit),(monkey),(empty))))

	Tree_Node *my = read_tree(cin);

	cout << "Given Tree: " << endl;
	print_tree(my,cout);

	cout << endl;
	cout << endl;

	MonkeyBusiness obj(my);

	cout << "Number of Monkeys in the Tree = " << obj.MonkeysInTree() << endl;
	cout << "Number of Hungry Monkeys in the Tree = " << obj.HungryMonkeys() << endl;
	cout << "Number of Monkeys on Leaves in the Tree = " << obj.MonkeysOnLeaves() << endl;
	cout << "The Tree is " << obj.PercentMonkeys() <<"% full of Monkeys"<< endl;
}
