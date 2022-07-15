/* Author: Randal Obringer
* Date Last Modified: ~2011 
* Description: implementation for checkers game. Note: color.h escapes do not work on Windows OS.
*/

#include <algorithm>  // Provides fill_n
#include <cassert>    // Provides assert macro
#include <cctype>     // Provides isdigit
#include <iomanip>    // Provides setw
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string.      
#include <string>     // Provides string
#include "checkers.h"
using namespace std;

//constructor
checkers::checkers(){
	game::restart(); //call parent class 
	for(int i=0;i<ROWS;i++){ //rows
		for(int j=0;j<COLUMNS;j++){ //columns
			//set initial red pieces
			if((((i==0)||(i==2))&&(j%2!=0))||((i==1)&&(j%2==0))){
				board[i][j]=RED_PIECE;
			//set initial black pieces
			}else if((((i==5)||(i==7))&&(j%2==0))||((i==6)&&(j%2!=0))){
				board[i][j]=BLACK_PIECE;
			//set board black spaces
			}else if((i%2==0)&&(j%2!=0)){
				board[i][j]=BLACK_SPACE;
			//set board red spaces
			}else if((i%2==0)&&(j%2==0)){
				board[i][j]=RED_SPACE;
			//set board additional red spaces
			}else if((i%2!=0)&&(j%2!=0)){
				board[i][j]=RED_SPACE;
			//set board additional black spaces
			}else if((i%2!=0)&&(j%2==0)){
				board[i][j]=BLACK_SPACE;
			}
		}
	}
}

//restart the checkers game
void checkers::restart(){
	checkers();
}

//receive the user's move from user input and return it.
string checkers::get_user_move()const{
	string move;
  
	cout << "Please enter the row and then the column of " << endl;
	cout << "the chip you wish to move and then enter the row and then " << endl;
	cout << "the column of the space you wish to move to (separate with a space):" << endl;
	getline(cin,move);
	return move;
}

//finalize the players turn. Take the move given from get_user_move() as input.
void checkers::make_move(const string& move){
	//pull the move coordinates out of the string. Convert its char to an int.
	int a = int(move[0]-'0');
	int b = int(move[2]-'0');
	int newA = int(move[4]-'0');
	int newB = int(move[6]-'0');
	
	if(board[a][b]==BLACK_PIECE){ //if black player
		board[a][b]=BLACK_SPACE; //change player's old board position to an empty black board space
		board[newA][newB]=BLACK_PIECE; //change player's new board position to display it's piece
	}else if(board[a][b]==RED_PIECE){ //if red player
		board[a][b]=BLACK_SPACE; //change player's old board position to an empty black board space
		board[newA][newB]=RED_PIECE; //change player's new board position to display it's piece
	}  
	game::make_move(move); //call the parent function, increments # of moves made by the players
}

//return a copy of the game
game* checkers::clone()const{
	return new checkers(*this);
}

//display the board. Uses string color codes outlined in color.h
void checkers::display_status()const{
	cout << BOLD <<"Checkers" << RESET << endl;
	cout << "Human chips are: " << BLACK_PIECE << RESET << endl;
	cout << "Computer chips are: " << RED_PIECE << RESET << endl << endl;
	for(int i=0;i<ROWS;i++){ //rows
		for(int j=0;j<COLUMNS;j++){//columns
			if(j<7){
				cout << board[i][j];
			}else{
				cout << board[i][j] << RESET << " " << i << " " << endl;
			}
		}
	}
	for(int i=0;i<ROWS;i++){
		if(i==7){
			cout << " " << i << " " << endl;
		}else{
			cout << " " << i << " ";
		}
	}
}
  
void checkers::compute_moves(std::queue<std::string>& moves) const{
	//unimplemented
}

int checkers::evaluate() const{
	//unimplemented
	return 1;
}

//check user move input is legal. Constructs the game's rules
bool checkers::is_legal(const string& move) const{
	//pull the move coordinates out of the string. Convert its char to an int.
	int a = int(move[0]-'0');
	int b = int(move[2]-'0');
	int newA = int(move[4]-'0');
	int newB = int(move[6]-'0');

	//*******************************************************************************
	//CHECKING INPUT
	//*******************************************************************************
	if((!isspace(move[1]))&&(!isspace(move[3]))&&(!isspace(move[5]))){
		return false;//checking correct form of input
	}else if((int(move[0]-'0')<0)||(int(move[0]-'0')>7)){
		return false;//checks if first input # is within board bounds
	}else if((int(move[2]-'0')<0)||(int(move[2]-'0')>7)){
		return false;//checks if second input # is within board bounds
	}else if((int(move[4]-'0')<0)||(int(move[4]-'0')>7)){
		return false;//checks if third input # is within board bounds
	}else if((int(move[6]-'0')<0)||(int(move[6]-'0')>7)){
		return false;//checks if fourth input # is within board bounds
	}

	//*******************************************************************************
	//BLACK PIECE LEGAL MOVES
	//*******************************************************************************
	else if(board[a][b]==BLACK_PIECE){ //if moving a BLACK PIECE
		if((board[newA][newB]==BLACK_PIECE)||(board[newA][newB]==BLACK_KING)||(board[newA][newB]==RED_KING)||(board[newA][newB]==BLACK_KING)){ 
			return false;//if space is occupied (no good)
		}else if((newA==a-1)&&(newB==b+1)){ //if move is up and right (good)
			return true;
		}else if((newA==a-1)&&(newB==b-1)){ //if move is up and left (good)
			return true;
		}else{
			return false; //otherwise (no good)
		}
	}

	//*******************************************************************************
	//BLACK KING/RED KING LEGAL MOVES
	//*******************************************************************************
	else if((board[a][b]==BLACK_KING)||(board[a][b]==RED_KING)){ //if moving a BLACK/RED KING
		if((board[newA][newB]==BLACK_PIECE)||(board[newA][newB]==BLACK_KING)||(board[newA][newB]==RED_KING)||(board[newA][newB]==BLACK_KING)){ 
			return false;//if space is occupied (no good)
		}else if((newA==a-1)&&(newB==b-1)){ //if move is up and left (good)
			return true;
		}else if((newA==a-1)&&(newB==b+1)){ //if move is up and right (good)
			return true;
		}else if((newA==a+1)&&(newB==b+1)){ //if move is down and right (good)
			return true;
		}else if((newA==a+1)&&(newB==b-1)){ //if move is down and left (good)
			return true;
		}else return false; //otherwise (no good)
	}
      

	//*******************************************************************************
	//RED PIECE LEGAL MOVES
	//*******************************************************************************   
	else if(board[a][b]==RED_PIECE){ //if moving a red piece
		if((board[newA][newB]==BLACK_PIECE)||(board[newA][newB]==BLACK_KING)||(board[newA][newB]==RED_KING)||(board[newA][newB]==BLACK_KING)){ 
			return false;//if space is occupied (no good)
		}else if((newA==a+1)&&(newB==b+1)){ //if move is down and right (good)
			return true;
		}else if((newA==a+1)&&(newB==b-1)){ //if move is down and left (good)
			return true;
		}else{ 
			return false; //otherwise (no good)
		}
	}

	//*******************************************************************************
	//CHECKING IF SPACE BEING MOVED IS A PIECE
	//*******************************************************************************
	else if(board[a][b]==BLACK_SPACE){ //if you choose to move a blank space (false)
		return false;
	}else if(board[a][b]==RED_SPACE){ //if you choose to move a blank space (false)
		return false;
	}else{ 
		return false;
	}
}

//check and output if the game has been won
bool checkers::is_game_over() const{ 
	int red,black;
	red=black=0;
	for(int i=0;i<ROWS;i++){
		for(int j=0;j<COLUMNS;j++){
			if((board[i][j]==RED_PIECE)||(board[i][j]==RED_KING)){
				red++;
			}else if((board[i][j]==BLACK_PIECE)||(board[i][j]==BLACK_KING)){
				black++;
			}
		}
	}
	if((red==0)||(black==0)){
		return true;
	}else{
		return false;
	}
}
