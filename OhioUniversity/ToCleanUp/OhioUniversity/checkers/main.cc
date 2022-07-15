/* Author: Randal Obringer
* Date Last Modified: ~2011 
* Description: Checkers game. 
*/

#include <iostream>
#include "checkers.h"
#include "game.h"
using namespace std;

int main(){
	checkers game1;
	checkers::who winner;
	winner=game1.play();
	switch(winner){
		case checkers::HUMAN:
			cout << "You win" << endl;
			break;
		case checkers::COMPUTER:
			cout << "I win" << endl;
			break;
		case checkers::NEUTRAL:
			cout << "Draw" << endl;
			break;
	}
}
