#include "board.h"

Board::Board(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			board[i][j] = new Tile((i+1),(j+1));
		}
	}
}

Board::~Board(){

}

void Board::output(){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			board[i][j]->output();
		}
	}
}

Tile* Board::getTile(int r, int c){
	return board[r][c];
}

void Board::remove_tile_possibilities(int remove, int tr, int tc){
	board[tr][tc]->remove_tile_possibilities(remove);
}

void Board::remove_row_possibilities(int remove, int r){
	for(int i=0;i<3;i++){
		board[r][i]->remove_row_possibilities(remove,r);
	}
}

void Board::remove_column_possibilities(int remove, int c){
	for(int i=0;i<3;i++){
		board[i][c]->remove_column_possibilities(remove,c);
	}
}

void Board::solve(){
	//queue<Pair<int,Pair<int,int>>> solution;
	//solution.push()
}
