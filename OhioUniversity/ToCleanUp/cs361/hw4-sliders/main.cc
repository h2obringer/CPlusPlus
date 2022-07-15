//********************************************************************
// Author: Randy Obringer
// Email: ro120908@ohio.edu
//
// Program: main.cc
// Description: This is the main function that uses the slider game
//   created in sliders.cc. It provides the user with a choice 
//   interface, allowing the user to input board states and gives the
//   answer to each state. 
//
// Created: 5/10/2010
// Update on 5/13/2010: Changed input of rows to getline to allow the input
//   of a ' '(space) instead of having to denote it as a '_'
//********************************************************************
#include "sliders.h"
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int main(){
  sliders game;
  string row1,row2,row3,board;
  int choice;
  do{
    cout << "1: Get answers to slider game" << endl;
    cout << "2: Exit program" << endl;
    cin >> choice;

    switch(choice){
      case 1: 
        try{
          cout << "Enter 3x3 board (denote empty position with a space)" << endl;
          if(cin.peek()=='\n'){
            cin.ignore();
          }
          getline(cin,row1);
          getline(cin,row2);
          getline(cin,row3);
          board=row1+row2+row3;
          int count=0;
          for(int i=0;i<board.length();i++){
            if(board[i]!=' '){
              count++;
            }
          }
          if((count!=8)||(board.length()!=9)){ 
            throw 0; //if input does not contain 8 numbers and only 1 space throw exception (change flow of control)
          }
          cout << endl;
          game.BFS(board);
        }catch(...){
          cout << "Bad input try again" << endl;
        }
        break;
      case 2:
        cout << "End of program" << endl;
        break;
      default:
        cout << "Try again" << endl;
    }
  }while(choice!=2);
}

