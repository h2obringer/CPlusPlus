//******************************************************************
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Program: MonkeyBusiness.h
//
//  Description: This is the class declaration of the MonkeyBusiness
//    class
//
//  Assumptions: We are given a well-formed tree. Every node in the 
//    tree will be either "empty","monkey", or "fruit"
//
//  Last updated: 4/12/11
//
//******************************************************************
#include "Tree_Node.h"

//class declaration
class MonkeyBusiness{
	public:
		MonkeyBusiness(); //constructor
		MonkeyBusiness(Tree_Node *root); //copy constructor
		~MonkeyBusiness(); //destructor
		int MonkeysOnLeaves(); //return # of monkeys on leaves in the tree
		int MonkeysInTree(); //return # of monkeys in the tree
		int HungryMonkeys();  //return number of hungry monkeys in the tree
		double PercentMonkeys(); //return the percent value of monkeys in the tree
	private:
		Tree_Node *root_ptr;
		void clear_tree(Tree_Node *root);
		int MOL(Tree_Node *root);
		int number_of_nodes(Tree_Node *root);
		int total_monkeys(Tree_Node *root);
		bool hungry(Tree_Node *parent,Tree_Node *root);
		int count_hungry(Tree_Node *root);
};