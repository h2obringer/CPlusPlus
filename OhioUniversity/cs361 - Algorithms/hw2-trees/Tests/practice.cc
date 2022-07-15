#include <cstdlib>
#include <iostream>
#include "Tree_Node.h"
using namespace std;

int main(){
  for(Tree_Node *ptr=NULL;ptr!=NULL;ptr=ptr->rs){
    cout << "nothing" << endl;
  }
}
