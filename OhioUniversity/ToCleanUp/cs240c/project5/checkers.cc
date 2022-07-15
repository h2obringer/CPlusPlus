//*******************************************************************
//Author: Randy Obringer
//File: checkers.cc
//Description: This is the implementation of checkers. The constructor
//sets up the boards and its pieces. The bulk of this file lies in
//the is_legal function which houses all the possible moves for any 
//given piece. Apart from this function is the make_move function
//which actually changes the board so that it may display the game
//correctly as each turn is made. Inline documentation explains most 
//of the hard stuff.
//*******************************************************************
#include <algorithm>  // Provides fill_n
#include <cassert>    // Provides assert macro
#include <cctype>     // Provides isdigit
#include <iomanip>    // Provides setw
#include <iostream>   // Provides cin, cout
#include <queue>      // Provides queue<string.      
#include <string>     // Provides string
#include <sstream>
#include "checkers.h"
using namespace std;

//static const int ROWS;
//static const int COLUMNS;
bool checkers::set_new_king(bool a){
  new_king=a;
}

checkers::checkers(){
  game::restart();
  red=black=12;
  set_new_king(false);
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

bool checkers::jump_available()const{//tells if a jump is available at the start of a turn and then forces them to make the jump
  for(int i=0;i<ROWS;i++){
    for(int j=0;j<COLUMNS;j++){
      if(next_mover()==HUMAN){
        if((board[i][j]==BLACK_PIECE)||(board[i][j]==BLACK_KING)){ //jump available to black...
          if(new_king){
            return false;
          }else if((i+2>=0)&&(i+2<=7)&&(j+2>=0)&&(j+2<=7)&&(board[i][j]==BLACK_KING)&&(board[i+1][j+1]==RED_PIECE)&&(board[i+2][j+2]==BLACK_SPACE)){
	    return true; //king down and right
          }else if((i+2>=0)&&(i+2<=7)&&(j+2>=0)&&(j+2<=0)&&(board[i][j]==BLACK_KING)&&(board[i+1][j+1]==RED_KING)&&(board[i+2][j+2]==BLACK_SPACE)){
            return true; //king down and right on a king
          }else if((i+2>=0)&&(i+2<=7)&&(j-2>=0)&&(j-2<=7)&&(board[i][j]==BLACK_KING)&&(board[i+1][j-1]==RED_PIECE)&&(board[i+2][j-2]==BLACK_SPACE)){
            return true; //king down and left
          }else if((i+2>=0)&&(i+2<=7)&&(j-2>=0)&&(j-2<=7)&&(board[i][j]==BLACK_KING)&&(board[i+1][j-1]==RED_KING)&&(board[i+2][j-2]==BLACK_SPACE)){
            return true; //king down and left on a king
          }else if((i-2>=0)&&(i-2<=7)&&(j+2>=0)&&(j+2<=7)&&(board[i-1][j+1]==RED_PIECE)&&(board[i-2][j+2]==BLACK_SPACE)){
            return true; //any piece up and right
          }else if((i-2>=0)&&(i-2<=7)&&(j+2>=0)&&(j+2<=7)&&(board[i-1][j+1]==RED_KING)&&(board[i-2][j+2]==BLACK_SPACE)){
            return true; //any piece up and right on a king
          }else if((i-2>=0)&&(i-2<=7)&&(j-2>=0)&&(j-2<=7)&&(board[i-1][j-1]==RED_PIECE)&&(board[i-2][j-2]==BLACK_SPACE)){
            return true; //any piece up and left
          }else if((i-2>=0)&&(i-2<=7)&&(j-2>=0)&&(j-2<=7)&&(board[i-1][j-1]==RED_KING)&&(board[i-2][j-2]==BLACK_SPACE)){
            return true; //and piece up and left on a king
          }
        }
      }else if(next_mover()==COMPUTER){
        if((board[i][j]==RED_PIECE)||(board[i][j]==RED_KING)){ //jump available to red...
          if(new_king){
            return false;
          }else if((i+2>=0)&&(i+2<=7)&&(j+2>=0)&&(j+2<=7)&&(board[i+1][j+1]==BLACK_PIECE)&&(board[i+2][j+2]==BLACK_SPACE)){
	    return true; //any piece down and right
          }else if((i+2>=0)&&(i+2<=7)&&(j+2>=0)&&(j+2<=7)&&(board[i+1][j+1]==BLACK_KING)&&(board[i+2][j+2]==BLACK_SPACE)){
            return true; //any piece down and right on a king
          }else if((i+2>=0)&&(i+2<=7)&&(j-2>=0)&&(j-2<=7)&&(board[i+1][j-1]==BLACK_PIECE)&&(board[i+2][j-2]==BLACK_SPACE)){
            return true; //any piece down and left
          }else if((i+2>=0)&&(i+2<=7)&&(j-2>=0)&&(j-2<=7)&&(board[i+1][j-1]==BLACK_KING)&&(board[i+2][j-2]==BLACK_SPACE)){
            return true; //any piece down and left on a king
          }else if((i-2>=0)&&(i-2<=7)&&(j+2>=0)&&(j+2<=7)&&(board[i][j]==RED_KING)&&(board[i-1][j+1]==BLACK_PIECE)&&(board[i-2][j+2]==BLACK_SPACE)){
            return true; //king up and right
          }else if((i-2>=0)&&(i-2<=7)&&(j+2>=0)&&(j+2<=7)&&(board[i][j]==RED_KING)&&(board[i-1][j+1]==BLACK_KING)&&(board[i-2][j+2]==BLACK_SPACE)){
            return true; //king up and right on a king
          }else if((i-2>=0)&&(i-2<=7)&&(j-2>=0)&&(j-2<=7)&&(board[i][j]==RED_KING)&&(board[i-1][j-1]==BLACK_PIECE)&&(board[i-2][j-2]==BLACK_SPACE)){
            return true; //king up and left
          }else if((i-2>=0)&&(i-2<=7)&&(j-2>=0)&&(j-2<=7)&&(board[i-1][j-1]==BLACK_KING)&&(board[i][j]==RED_KING)&&(board[i-2][j-2]==BLACK_SPACE)){
            return true; //king up and left on a king
          }
        }
      }
    }
  }return false;
}

bool checkers::jump_again(const std::string move)const{
  int a,b;
  a=int(move[4]-'0');
  b=int(move[6]-'0');   
  if(next_mover()==HUMAN){
    if((board[a][b]==BLACK_PIECE)||(board[a][b]==BLACK_KING)){ //jump available to black...
      if(new_king){
        return false;
      }else if((a+2>=0)&&(a+2<=7)&&(b+2>=0)&&(b+2<=7)&&(board[a][b]==BLACK_KING)&&(board[a+1][b+1]==RED_PIECE)&&(board[a+2][b+2]==BLACK_SPACE)){
        return true; //king down and right
      }else if((a+2>=0)&&(a+2<=7)&&(b+2>=0)&&(b+2<=7)&&(board[a][b]==BLACK_KING)&&(board[a+1][b+1]==RED_KING)&&(board[a+2][b+2]==BLACK_SPACE)){
        return true; //king down and right on a king
      }else if((a+2>=0)&&(a+2<=7)&&(b-2>=0)&&(b-2<=7)&&(board[a][b]==BLACK_KING)&&(board[a+1][b-1]==RED_PIECE)&&(board[a+2][b-2]==BLACK_SPACE)){
        return true; //king down and left
      }else if((a+2>=0)&&(a+2<=7)&&(b-2>=0)&&(b-2<=7)&&(board[a][b]==BLACK_KING)&&(board[a+1][b-1]==RED_KING)&&(board[a+2][b-2]==BLACK_SPACE)){
        return true; //king down and left on a king
      }else if((a-2>=0)&&(a-2<=7)&&(b+2>=0)&&(b+2<=7)&&(board[a-1][b+1]==RED_PIECE)&&(board[a-2][b+2]==BLACK_SPACE)){
        return true; //any piece up and right
      }else if((a-2>=0)&&(a-2<=7)&&(b+2>=0)&&(b+2<=7)&&(board[a-1][b+1]==RED_KING)&&(board[a-2][b+2]==BLACK_SPACE)){
        return true; //any piece up and right on a king
      }else if((a-2>=0)&&(a-2<=7)&&(b-2>=0)&&(b-2<=7)&&(board[a-1][b-1]==RED_PIECE)&&(board[a-2][b-2]==BLACK_SPACE)){
        return true; //any piece up and left
      }else if((a-2>=0)&&(a-2<=7)&&(b-2>=0)&&(b-2<=7)&&(board[a-1][b-1]==RED_KING)&&(board[a-2][b-2]==BLACK_SPACE)){
        return true; //and piece up and left on a king
      }
    }
  }else if(next_mover()==COMPUTER){
    if((board[a][b]==RED_PIECE)||(board[a][b]==RED_KING)){ //jump available to red...
      if(new_king){
        return false;
      }else if((a+2>=0)&&(a+2<=7)&&(b+2>=0)&&(b+2<=7)&&(board[a+1][b+1]==BLACK_PIECE)&&(board[a+2][b+2]==BLACK_SPACE)){
        return true; //any piece down and right
      }else if((a+2>=0)&&(a+2<=7)&&(b+2>=0)&&(b+2<=7)&&(board[a+1][b+1]==BLACK_KING)&&(board[a+2][b+2]==BLACK_SPACE)){
        return true; //any piece down and right on a king
      }else if((a+2>=0)&&(a+2<=7)&&(b-2>=0)&&(b-2<=7)&&(board[a+1][b-1]==BLACK_PIECE)&&(board[a+2][b-2]==BLACK_SPACE)){
        return true; //any piece down and left
      }else if((a+2>=0)&&(a+2<=7)&&(b-2>=0)&&(b-2<=7)&&(board[a+1][b-1]==BLACK_KING)&&(board[a+2][b-2]==BLACK_SPACE)){
        return true; //any piece down and left on a king
      }else if((a-2>=0)&&(a-2<=7)&&(b+2>=0)&&(b+2<=7)&&(board[a][b]==RED_KING)&&(board[a-1][b+1]==BLACK_PIECE)&&(board[a-2][b+2]==BLACK_SPACE)){
        return true; //king up and right
      }else if((a-2>=0)&&(a-2<=7)&&(b+2>=0)&&(b+2<=7)&&(board[a][b]==RED_KING)&&(board[a-1][b+1]==BLACK_KING)&&(board[a-2][b+2]==BLACK_SPACE)){
        return true; //king up and right on a king
      }else if((a-2>=0)&&(a-2<=7)&&(b-2>=0)&&(b-2<=7)&&(board[a][b]==RED_KING)&&(board[a-1][b-1]==BLACK_PIECE)&&(board[a-2][b-2]==BLACK_SPACE)){
        return true; //king up and left
      }else if((a-2>=0)&&(a-2<=7)&&(b-2>=0)&&(b-2<=7)&&(board[a-1][b-1]==BLACK_KING)&&(board[a][b]==RED_KING)&&(board[a-2][b-2]==BLACK_SPACE)){
        return true; //king up and left on a king
      }
    }
  }
}

void checkers::make_move(const string& move){
  int a= int(move[0]-'0');
  int b= int(move[2]-'0');
  int newA= int(move[4]-'0');
  int newB= int(move[6]-'0');
  std::string move1;
  
//**************************************************************************************
//MOVING A BLACK PIECE
//**************************************************************************************
  if(board[a][b]==BLACK_PIECE){ //moving a black piece
    board[a][b]=BLACK_SPACE; //replace with black space
    board[newA][newB]=BLACK_PIECE; //make destination a black piece
    if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==RED_PIECE)&&(a-2==newA)&&(b+2==newB)){//making a jump up and right
      board[a-1][b+1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){ //changed from if statement
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }//if(!jump_available()){game::make_move(move);}
    }else if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==RED_KING)&&(a-2==newA)&&(b+2==newB)){//making a jump up and right on a king
      board[a-1][b+1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){ //changed from if statement
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }//if(!jump_available()){game::make_move(move);}
    }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==RED_PIECE)&&(a-2==newA)&&(b-2==newB)){//making a jump up and left
      board[a-1][b-1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){ //changed from if statement
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }//if(!jump_available()){game::make_move(move);}
    }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==RED_KING)&&(a-2==newA)&&(b-2==newB)){//making a jump up and left on a king
      board[a-1][b-1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){ //changed from if statement
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }//if(!jump_available()){game::make_move(move);}
    }
    if((newA==0)&&(board[newA][newB]==BLACK_PIECE)){ //change to a black king
      board[newA][newB]=BLACK_KING; set_new_king(true); return;
    }
//***************************************************************************************
//MOVING A BLACK KING 
//***************************************************************************************
  }else if(board[a][b]==BLACK_KING){ //moving a red king
    board[a][b]=BLACK_SPACE; //replace with black space
    board[newA][newB]=BLACK_KING; //new place becomes red king
    if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==RED_PIECE)&&(a-2==newA)&&(b+2==newB)){//making a jump up and right
      board[a-1][b+1]=BLACK_SPACE;
      red--; //total red pieces subtract
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==RED_KING)&&(a-2==newA)&&(b+2==newB)){//making a jump up and right on a king
      board[a-1][b+1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==RED_PIECE)&&(a-2==newA)&&(b-2==newB)){//making a jump up and left
      board[a-1][b-1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){ 
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==RED_KING)&&(a-2==newA)&&(b-2==newB)){//making a jump up and left on a king
      board[a-1][b-1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==RED_PIECE)&&(a+2==newA)&&(b+2==newB)){ //making a jump down and right
      board[a+1][b+1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==RED_KING)&&(a+2==newA)&&(b+2==newB)){ //making a jump down and right on a king
      board[a+1][b+1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==RED_PIECE)&&(a+2==newA)&&(b-2==newB)){ //making a jump down and left
      board[a+1][b-1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==RED_KING)&&(a+2==newA)&&(b-2==newB)){ //making a jump down and left on a king
      board[a+1][b-1]=BLACK_SPACE;
      red--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }

//***************************************************************************************
//MOVING A RED PIECE
//***************************************************************************************
  }else if(board[a][b]==RED_PIECE){
    board[a][b]=BLACK_SPACE;
    board[newA][newB]=RED_PIECE;
    if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==BLACK_PIECE)&&(a+2==newA)&&(b+2==newB)){//making a jump down and right
      board[a+1][b+1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==BLACK_KING)&&(a+2==newA)&&(b+2==newB)){//making a jump down and right on a king
      board[a+1][b+1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==BLACK_PIECE)&&(a+2==newA)&&(b-2==newB)){//making a jump down and left
      board[a+1][b-1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==BLACK_KING)&&(a+2==newA)&&(b-2==newB)){//making a jump down and left on a king
      board[a+1][b-1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }
    if((newA==7)&&(board[newA][newB]==RED_PIECE)){ //change to a red king
      board[newA][newB]=RED_KING; set_new_king(true); return;
    }
//***************************************************************************************
//MOVING A RED KING 
//***************************************************************************************
  }else if(board[a][b]==RED_KING){ //moving a red king
    board[a][b]=BLACK_SPACE; //replace with black space
    board[newA][newB]=RED_KING; //new place becomes red king
    if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==BLACK_PIECE)&&(a-2==newA)&&(b+2==newB)){//making a jump up and right
      board[a-1][b+1]=BLACK_SPACE;
      black--; //total black pieces subtract
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==BLACK_KING)&&(a-2==newA)&&(b+2==newB)){//making a jump up and right on a king
      board[a-1][b+1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==BLACK_PIECE)&&(a-2==newA)&&(b-2==newB)){//making a jump up and left
      board[a-1][b-1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==BLACK_KING)&&(a-2==newA)&&(b-2==newB)){//making a jump up and left on a king
      board[a-1][b-1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==BLACK_PIECE)&&(a+2==newA)&&(b+2==newB)){ //making a jump down and right
      board[a+1][b+1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==BLACK_KING)&&(a+2==newA)&&(b+2==newB)){ //making a jump down and right on a king
      board[a+1][b+1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==BLACK_PIECE)&&(a+2==newA)&&(b-2==newB)){ //making a jump down and left
      board[a+1][b-1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==BLACK_KING)&&(a+2==newA)&&(b-2==newB)){ //making a jump down and left on a king
      board[a+1][b-1]=BLACK_SPACE;
      black--;
      if(jump_again(move)){
        display_status();
        move1 = get_user_move( );
        while (!is_legal(move1)){
          display_message(BOLD+"Illegal move,incorrect input,or out of turn."+RESET+"\n");
          display_status();
          move1 = get_user_move( );
        }
        make_move(move1); 
      }
    }
  }
if(!jump_available()||((newA==a+1)&&(newB==b+1))||((newA==a+1)&&(newB==b-1))||((newA==a-1)&&(newB==b+1))||((newA==a-1)&&(newB==b-1))){game::make_move(move); set_new_king(false);}
  //The if statement above makes sure that a player cant just make a move where a jump would be available and allow for them to not keep going
}

game* checkers::clone()const{ //MAYBE
  return new checkers(*this);
}

void checkers::display_status()const{ //CORRECT
  cout << BOLD <<"Checkers" << RESET << endl;
  cout << "Player 1's chips are: " << BLACK_PIECE << RESET << " Player 2's chips are: " << RED_PIECE << RESET << endl;
  if(next_mover()==HUMAN){
    cout << BOLD << "Player 1's turn" << RESET << " " << black << " chips left" << endl;
  }else if(next_mover()==COMPUTER){
    cout << BOLD << "Player 2's turn" << RESET << " " << red << " chips left" << endl;
  }
  if(jump_available()){
    cout << "Jump available!" << endl;
  }

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

bool checkers::is_legal(const string& move)const{ //yes

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

  else if(next_mover()==HUMAN){
  //*******************************************************************************
  //BLACK PIECE LEGAL MOVES (done)
  //*******************************************************************************
    if(board[a][b]==BLACK_PIECE){ //if moving a BLACK PIECE
      if((board[newA][newB]==BLACK_PIECE)||(board[newA][newB]==BLACK_KING)||(board[newA][newB]==RED_KING)||(board[newA][newB]==RED_PIECE)){ 
        return false;//if space is occupied (no good)
      }else if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==RED_PIECE)&&(a-2==newA)&&(b+2==newB)){ //making a jump up and right
        return true;
      }else if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==RED_KING)&&(a-2==newA)&&(b+2==newB)){ //making a jump up and right on a king
        return true;
      }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==RED_PIECE)&&(a-2==newA)&&(b-2==newB)){ //making a jump up and left
        return true;
      }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==RED_KING)&&(a-2==newA)&&(b-2==newB)){ //making a jump up and right on a king
        return true;
      }else if(jump_available()){ //if a jump is available then these moves cannot be made
        if((newA==a-1)&&(newB==b+1)){ //if move is up and right (good)
          return false;
        }else if((newA==a-1)&&(newB==b-1)){ //if move is up and left (good)
          return false;
        }
      }else if(!jump_available()){ //if a jump is not available then these moves can be made
        if((newA==a-1)&&(newB==b+1)){ //if move is up and right (good)
          return true;
        }else if((newA==a-1)&&(newB==b-1)){ //if move is up and left (good)
          return true;
        }
      }else return false; //otherwise (no good)
    }
  //*******************************************************************************
  //BLACK KING LEGAL MOVES
  //*******************************************************************************
    else if(board[a][b]==BLACK_KING){ //if moving a RED KING
      if((board[newA][newB]==BLACK_PIECE)||(board[newA][newB]==BLACK_KING)||(board[newA][newB]==RED_KING)||(board[newA][newB]==RED_PIECE)){ 
        return false;//if space is occupied (no good)
      }else if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==RED_PIECE)&&(a-2==newA)&&(b+2==newB)){//making a jump up and right
        return true;
      }else if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==RED_KING)&&(a-2==newA)&&(b+2==newB)){//making a jump up and right on a king
        return true;
      }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==RED_PIECE)&&(a-2==newA)&&(b-2==newB)){//making a jump up and left
        return true;
      }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==RED_KING)&&(a-2==newA)&&(b-2==newB)){//making a jump up and left on a king
        return true;
      }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==RED_PIECE)&&(a+2==newA)&&(b+2==newB)){ //making a jump down and right
        return true;
      }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==RED_KING)&&(a+2==newA)&&(b+2==newB)){ //making a jump down and right on a king
        return true;
      }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==RED_PIECE)&&(a+2==newA)&&(b-2==newB)){ //making a jump down and left
        return true;
      }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==RED_KING)&&(a+2==newA)&&(b-2==newB)){ //making a jump down and left on a king
        return true;
      }else if(jump_available()){ //if jump available these moves cannot be made
        if((newA==a-1)&&(newB==b-1)){ //if move is up and left (good)
          return false;
        }else if((newA==a-1)&&(newB==b+1)){ //if move is up and right (good)
          return false;
        }else if((newA==a+1)&&(newB==b+1)){ //if move is down and right (good)
          return false;
        }else if((newA==a+1)&&(newB==b-1)){ //if move is down and left (good)
          return false;
        }
      }else if(!jump_available()){ //if jump is not availabe these move can be made
        if((newA==a-1)&&(newB==b-1)){ //if move is up and left (good)
          return true;
        }else if((newA==a-1)&&(newB==b+1)){ //if move is up and right (good)
          return true;
        }else if((newA==a+1)&&(newB==b+1)){ //if move is down and right (good)
          return true;
        }else if((newA==a+1)&&(newB==b-1)){ //if move is down and left (good)
          return true;
        }
      }else return false; //otherwise (no good)
    }
  }
  
  else if(next_mover()==COMPUTER){
  //*******************************************************************************
  //RED PIECE LEGAL MOVES
  //*******************************************************************************   
    if(board[a][b]==RED_PIECE){ //if moving a red piece
      if((board[newA][newB]==BLACK_PIECE)||(board[newA][newB]==BLACK_KING)||(board[newA][newB]==RED_KING)||(board[newA][newB]==RED_PIECE)){ 
        return false;//if space is occupied (no good)
      }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==BLACK_PIECE)&&(a+2==newA)&&(b+2==newB)){//making a jump down and right 
        return true;
      }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==BLACK_KING)&&(a+2==newA)&&(b+2==newB)){//making a jump down and right on a king
        return true;
      }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==BLACK_PIECE)&&(a+2==newA)&&(b-2==newB)){//making a jump down and left
        return true;
      }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==BLACK_KING)&&(a+2==newA)&&(b-2==newB)){//making a jump down and left on a king
        return true;
      }else if(jump_available()){ //if jump available these moves cannot be made
        if((newA==a+1)&&(newB==b+1)){ //if move is down and right (good)
          return false;
        }else if((newA==a+1)&&(newB==b-1)){ //if move is down and left (good)
          return false;
        }
      }else if(!jump_available()){ //if jump not availabe these moves cannot be made
        if((newA==a+1)&&(newB==b+1)){ //if move is down and right (good)
          return true;
        }else if((newA==a+1)&&(newB==b-1)){ //if move is down and left (good)
          return true;
        }
      }else return false; //otherwise (no good)
    }
  

  //*******************************************************************************
  //RED KING LEGAL MOVES
  //*******************************************************************************
    else if(board[a][b]==RED_KING){ //if moving a RED KING
      if((board[newA][newB]==BLACK_PIECE)||(board[newA][newB]==BLACK_KING)||(board[newA][newB]==RED_KING)||(board[newA][newB]==RED_PIECE)){ 
        return false;//if space is occupied (no good)
      }else if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==BLACK_PIECE)&&(a-2==newA)&&(b+2==newB)){//making a jump up and right
        return true;
      }else if((a-1>=0)&&(b+1<=7)&&(board[a-1][b+1]==BLACK_KING)&&(a-2==newA)&&(b+2==newB)){//making a jump up and right on a king
        return true;
      }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==BLACK_PIECE)&&(a-2==newA)&&(b-2==newB)){//making a jump up and left
        return true;
      }else if((a-1>=0)&&(b-1<=7)&&(board[a-1][b-1]==BLACK_KING)&&(a-2==newA)&&(b-2==newB)){//making a jump up and left on a king
        return true;
      }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==BLACK_PIECE)&&(a+2==newA)&&(b+2==newB)){ //making a jump down and right
        return true;
      }else if((a+1>=0)&&(b+1<=7)&&(board[a+1][b+1]==BLACK_KING)&&(a+2==newA)&&(b+2==newB)){ //making a jump down and right on a king
        return true;
      }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==BLACK_PIECE)&&(a+2==newA)&&(b-2==newB)){ //making a jump down and left
        return true;
      }else if((a+1>=0)&&(b-1<=7)&&(board[a+1][b-1]==BLACK_KING)&&(a+2==newA)&&(b-2==newB)){ //making a jump down and left on a king
        return true;
      }else if(jump_available()){ //if a jump is available these moves cannot be made
        if((newA==a-1)&&(newB==b-1)){ //if move is up and left (good)
          return false;
        }else if((newA==a-1)&&(newB==b+1)){ //if move is up and right (good)
          return false;
        }else if((newA==a+1)&&(newB==b+1)){ //if move is down and right (good)
          return false;
        }else if((newA==a+1)&&(newB==b-1)){ //if move is down and left (good)
          return false;
        }
      }else if(!jump_available()){ //if there is a jump available these moves can be made
        if((newA==a-1)&&(newB==b-1)){ //if move is up and left (good)
          return true;
        }else if((newA==a-1)&&(newB==b+1)){ //if move is up and right (good)
          return true;
        }else if((newA==a+1)&&(newB==b+1)){ //if move is down and right (good)
          return true;
        }else if((newA==a+1)&&(newB==b-1)){ //if move is down and left (good)
          return true;
        }
      }else return false; //otherwise (no good)
    }
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
  int possibilities=0;
  for(int i=0;i<ROWS;i++){
    for(int j=0;j<COLUMNS;j++){
      if((board[i][j]==RED_PIECE)||(board[i][j]==RED_KING)||(board[i][j]==BLACK_KING)){//red or kings
        if((i+1>=0)&&(i+1<=7)&&(j+1>=0)&&(j+1<=7)&&(board[i+1][j+1]==BLACK_SPACE)){//down and right
          possibilities++;
        }if((i+1>=0)&&(i+1<=7)&&(j-1>=0)&&(j-1<=7)&&(board[i+1][j-1]==BLACK_SPACE)){//down and left
          possibilities++;
        }if((i+2>=0)&&(i+2<=7)&&(j+2>=0)&&(j+2<=7)&&(board[i+1][j+1]!=BLACK_SPACE)&&(board[i+2][j+2]==BLACK_SPACE)){//jump down and right
          possibilities++;
        }if((i+2>=0)&&(i+2<=7)&&(j-2>=0)&&(j-2<=7)&&(board[i+1][j-1]!=BLACK_SPACE)&&(board[i+2][j-2]==BLACK_SPACE)){//jump down and left
          possibilities++;
        }
      }if((board[i][j]==BLACK_PIECE)||(board[i][j]==RED_KING)||(board[i][j]==BLACK_KING)){//black or kings
        if((i-1>=0)&&(i-1<=7)&&(j+1>=0)&&(j+1<=7)&&(board[i-1][j+1]==BLACK_SPACE)){//up and right
          possibilities++;
        }if((i-1>=0)&&(i-1<=7)&&(j-1>=0)&&(j-1<=7)&&(board[i-1][j-1]==BLACK_SPACE)){//up and left
          possibilities++;
        }if((i-2>=0)&&(i-2<=7)&&(j+2>=0)&&(j+2<=7)&&(board[i-1][j+1]!=BLACK_SPACE)&&(board[i-2][j+2]==BLACK_SPACE)){//jump up and right
          possibilities++;
        }if((i-2>=0)&&(i-2<=7)&&(j-2>=0)&&(j-2<=7)&&(board[i-1][j-1]!=BLACK_SPACE)&&(board[i-2][j-2]==BLACK_SPACE)){//jump up and left
          possibilities++;
        }
      }
    }
  }if(possibilities==0){
    return true;
  }else if((red==0)||(black==0)){
    return true;
  }else{
    return false;
  }
}
