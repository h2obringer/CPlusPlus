#include <algorithm>  // Provides fill_n
#include <cassert>    // Provides assert macro
#include <cctype>     // Provides isdigit
#include <iomanip>    // Provides setw
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string.      
#include <string>     // Provides string
#include "checkers.h"
using namespace std;

//static const int ROWS;
//static const int COLUMNS;

checkers::checkers(){
  game::restart();
  for(int i=0;i<ROWS;i++){ //rows
    for(int j=0;j<COLUMNS;j++){ //columns
      if((((i==0)||(i==2))&&(j%2!=0))||((i==1)&&(j%2==0))){
        board[i][j]=RED_PIECE;
      }else if((((i==5)||(i==7))&&(j%2==0))||((i==6)&&(j%2!=0))){
        board[i][j]=BLACK_PIECE;
      }else if((i%2==0)&&(j%2!=0)){
        board[i][j]=BLACK_SPACE;
      }else if((i%2==0)&&(j%2==0)){
        board[i][j]=RED_SPACE;
      }else if((i%2!=0)&&(j%2!=0)){
        board[i][j]=RED_SPACE;
      }else if((i%2!=0)&&(j%2==0)){
        board[i][j]=BLACK_SPACE;
      }
    }
  }
}

void checkers::restart(){
  checkers();
}

std::string checkers::get_user_move()const{
  string move;
  
  cout << "Please enter the row and then the column of " << endl;
  cout << "the chip you wish to move and then enter the row and then " << endl;
  cout << "the column of the space you wish to move to (seperate with a space):" << endl;
  getline(cin,move);
  return move;
}

void checkers::make_move(const string& move){
  int a= int(move[0]-'0');
  int b= int(move[2]-'0');
  int newA= int(move[4]-'0');
  int newB= int(move[6]-'0');
  if(board[a][b]==BLACK_PIECE){
    board[a][b]=BLACK_SPACE;
    board[newA][newB]=BLACK_PIECE;
  }else if(board[a][b]==RED_PIECE){
    board[a][b]=BLACK_SPACE;
    board[newA][newB]=RED_PIECE;
  }  
  game::make_move(move);
}

game* checkers::clone()const{ //MAYBE
  return new checkers(*this);
}

void checkers::display_status()const{ //CORRECT
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
  
void checkers::compute_moves(std::queue<std::string>& moves) const{ //NO
  
}

int checkers::evaluate() const{ //NO
  return 1;
}

bool checkers::is_legal(const string& move) const{ //yes

  int a= int(move[0]-'0');
  int b= int(move[2]-'0');
  int newA= int(move[4]-'0');
  int newB= int(move[6]-'0');

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
    }else return false; //otherwise (no good)
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
    }else return false; //otherwise (no good)
  }

//*******************************************************************************
//CHECKING IF SPACE BEING MOVED IS A PIECE
//*******************************************************************************
  else if(board[a][b]==BLACK_SPACE){ //if you choose to move a blank space (false)
    return false;
  }else if(board[a][b]==RED_SPACE){ //if you choose to move a blank space (false)
    return false;
  }else return false;
}
bool checkers::is_game_over() const{ //check to see if the game is over or not
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
