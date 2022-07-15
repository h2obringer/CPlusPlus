//******************************************************************
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Program: MonkeyBusiness.cc
//
//  Description: This is the class implementation of the MonkeyBusiness
//    class
//
//  Assumptions: We are given a well-formed tree. Every node in the 
//    tree will be either "empty","monkey", or "fruit"
//
//  Last updated: 4/12/11
//
//******************************************************************

#include <string>
#include <iostream>
#include <cstdlib>
#include "MonkeyBusiness.h"
using namespace std;

//constructor
MonkeyBusiness::MonkeyBusiness(){ 
	root_ptr=NULL;
}

//2nd constructor that initializes the tree to another tree that has already been created
MonkeyBusiness::MonkeyBusiness(Tree_Node *root){ 
	root_ptr=root;
}

//destructor - calls clear_tree which deletes nodes recursively
MonkeyBusiness::~MonkeyBusiness(){
	clear_tree(root_ptr);
}

//***********************************************************************
//  Function: MonkeysOnLeaves (public)
//
//  Parameters: None
//
//  Effects: Calls MOL so that recursion may be used. Computes and outputs
//    the number of monkeys in the tree that are located on leaves
//
//***********************************************************************
int MonkeyBusiness::MonkeysOnLeaves(){ //calls MOL which is needed for recursion
	return MOL(root_ptr);
}

//***********************************************************************
//  Function: MonkeysInTree (public)
//
//  Parameters: None
//
//  Effects: Calls total_monkeys so that recursion may be used. Computes and
//    outputs the number of monkeys that are in the tree
//
//***********************************************************************
int MonkeyBusiness::MonkeysInTree(){ 
	return total_monkeys(root_ptr);
}

//***********************************************************************
//  Function: HungryMonkeys (public)
//
//  Parameters: None
//
//  Effects: Counts the number of hungry monkeys in the tree using a call
//    to count_hungry. This is done so that recursion can be achieved.
//
//***********************************************************************
int MonkeyBusiness::HungryMonkeys(){ 
	return count_hungry(root_ptr);
}

//***********************************************************************
//  Function: PercentMonkeys (public)
//
//  Parameters: None
//
//  Effects: Uses two recursive functions to compute and output the % of
//    monkeys there are in the tree. Calls total_monkeys to get the amount
//    monkeys in the tree and is divided by the total number of spots in the 
//    tree which is given by the call to number_of_nodes
//
//***********************************************************************
double MonkeyBusiness::PercentMonkeys(){
	return 100*((total_monkeys(root_ptr)*1.0)/(number_of_nodes(root_ptr)*1.0));
}

//***********************************************************************
//  Function: clear_tree (private)
//
//  Parameters: a pointer to a tree node
//
//  Effects: deletes an entire tree recursively
//
//***********************************************************************
void MonkeyBusiness::clear_tree(Tree_Node *root){ 
	if(root==NULL){ //base case
		return;
	}else{
		clear_tree(root->lc);
		clear_tree(root->rs);
		delete root;
	}
}

//***********************************************************************
//  Function: MOL (private)
//
//  Parameters: a pointer to a tree node
//
//  Effects: recursively computes the number of monkeys located on leaves
//    in a tree
//
//***********************************************************************
int MonkeyBusiness::MOL(Tree_Node *root){ 
	if(root==NULL){ //base case
		return 0;
	}else if((root->node=="monkey")&&(root->lc==NULL)){ //target case
		return 1;
	}else{
		int sum=0;
		for(Tree_Node *ptr=root->lc; ptr!=NULL; ptr=ptr->rs){
			sum+=MOL(ptr);
		}
		return sum;
	}    
}

//***********************************************************************
//  Function: number_of_nodes (private)
//
//  Parameters: a pointer to a tree node
//
//  Effects: recursively counts the amount of nodes in a tree (the total)
//
//***********************************************************************
int MonkeyBusiness::number_of_nodes(Tree_Node *root){ 
	if(root==NULL){ //base case
		return 0;
	}else{
		int sum=1;
		for(Tree_Node *ptr=root->lc;ptr!=NULL;ptr=ptr->rs){
			sum+=number_of_nodes(ptr);
		}
		return sum;
	}
}

//***********************************************************************
//  Function: total_monkeys (private)
//
//  Parameters: a pointer to a tree node
//
//  Effects: recursively counts the amount of monkeys in a tree (the total)
//    (different than nodes)
//
//***********************************************************************
int MonkeyBusiness::total_monkeys(Tree_Node *root){
	if(root==NULL){
		return 0;
	}else{
		int sum=0;
		if(root->node=="monkey")sum++;
		for(Tree_Node *ptr=root->lc;ptr!=NULL;ptr=ptr->rs){
			sum+=total_monkeys(ptr);
		}
		return sum;
	}
}

//***********************************************************************
//  Function: hungry (private)
//
//  Parameters: 2 pointers to a tree node
//    1: must be the pointer to the parent of the node being tested for hunger
//    2: must be the pointer to the node being tested for hunger
//
//  Effects: returns true if the root (2nd parameter) is a hungry monkey
//    and false if the root (2nd parameter is not a hungry monkey
//
//  Note: the root (2nd parameter) is the node being tested for hunger
//
//***********************************************************************
bool MonkeyBusiness::hungry(Tree_Node *parent,Tree_Node *root){ //root is being decided on if hungry or not
	if(parent->node!="fruit"){ 
		if(root==NULL){
			return false;
		}else if(root->node=="empty"){
			return false;
		}else if(root->node=="monkey"){ //only possibility of being true is if one being looked at is a monkey
			if(root->lc==NULL){
				return true;
			}else if(root->lc->node!="fruit"){
				bool fruit_below=false;
				for(Tree_Node *ptr=root->lc;ptr!=NULL;ptr=ptr->rs){
					if(ptr->node=="fruit"){
						fruit_below=true;
					}
				}
				if(fruit_below==true){
					return false;
				}else{
					return true;
				}
			}
		}else if(root->node=="fruit"){
			return false;
		}
	}else if(parent->node=="fruit"){
		return false;
	}
	return false;
}

//***********************************************************************
//  Function: count_hungry (private)
//
//  Parameters: a pointer to a tree node
//
//  Effects: traverses a tree from the root (parameter) and counts the
//    nodes that are hungry. Returns the total number of hungry monkeys
//    on the tree.
//  
//***********************************************************************
int MonkeyBusiness::count_hungry(Tree_Node *root){
	if(root==NULL){
		return 0;
	}else{
		int sum=0;
		for(Tree_Node *ptr=root->lc;ptr!=NULL;ptr=ptr->rs){
			if(hungry(root,ptr)==true){
				sum++;
			}
			sum+=count_hungry(ptr);
		}
		return sum;
	}
}