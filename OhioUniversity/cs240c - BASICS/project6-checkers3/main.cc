//*******************************************************************
//Author: Randy Obringer
//File: main.cc
//Description: This is what actually declares the game object so that 
//we may play checkers. 
//*******************************************************************
#include <iostream>
#include "checkers.h"
#include "game.h"
using namespace std;

int main(){
  char c;
  do{
    checkers game1;
    checkers::who winner;
    winner=game1.play();
    switch(winner){
      case checkers::HUMAN:
        cout << "Player 1 wins" << endl;
        break;
      case checkers::COMPUTER:
        cout << "I win" << endl;
        break;
      case checkers::NEUTRAL:
        cout << "Draw" << endl;
        break;
    }
    cout << "Press Y to play again, press N to quit" << endl;
    cin >> c;
  }while((c=='Y')||(c=='y'));
}

