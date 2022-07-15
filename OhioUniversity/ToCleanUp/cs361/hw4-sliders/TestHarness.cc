//*********************************************************************
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Program: TestHarness.cc
// Description: Test Code from sliders.cc
//
// Last Updated: 5/16/2010
//
//********************************************************************* 
#include "sliders.h"
int main(){
  sliders game;
  string first="12 345678";
  cout << "Current board position: " << first << endl;
  cout << "Function gives: ";
  game.BFS(first); 
  cout << "\nThe output of this position should be RR" << endl;
  cout << endl;
  first="432 15678";
  cout << "Current board position: " << first << endl;
  cout << "Function gives: ";
  game.BFS(first); 
  cout << "\nThe output of this position should be DLURD" << endl;
  cout << endl;
  first=" 12345678";
  cout << "Current board position: " << first << endl;
  cout << "Function gives: ";
  game.BFS(first); 
  cout << "\nThis board position should be at the goal state already" << endl;
  cout << endl;
  first="54321 768";
  cout << "Current board position: " << first << endl;
  cout << "Function gives: ";
  game.BFS(first);
  cout << "\nThis board position should be impossible to solve" << endl;
  cout << endl;
  
}
