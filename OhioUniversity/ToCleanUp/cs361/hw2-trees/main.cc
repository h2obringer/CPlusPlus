#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Tree_Node.h"

#include "MonkeyBusiness.cc"


void print_tree(Tree_Node *r,ostream &out) {
  if (r==NULL) return;
  out << "(" << r->node;
  for (Tree_Node *n=r->lc;n!=NULL;n=n->rs) {
    out << ",";
    print_tree(n,out);
  }
  out << ")";
}

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
