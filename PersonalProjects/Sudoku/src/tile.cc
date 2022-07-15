#include "tile.h"

Tile::Tile(int r, int c){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			tile[i][j] = new Square(r*(i+1),c*(j+1));
		}
	}

}

Tile::~Tile(){

}

void Tile::output(){
	for(int i=0;i<3;i++){ //rows
		for(int j=0;j<3;j++){ //columns
			cout << tile[j][i]->getAnswer();
			if(j!=2){
				cout << ", ";
			}
		}
		cout << endl;
	}
}

Square* Tile::getSquare(int r, int c){
	return tile[r][c];
}


void Tile::remove_tile_possibilities(int remove){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			tile[i][j]->removePossibility(remove);
		}
	}
}

void Tile::remove_row_possibilities(int remove,int r){
	for(int i=0;i<3;i++){
		tile[r][i]->removePossibility(remove);
	}
}

void Tile::remove_column_possibilities(int remove,int c){
	for(int i=0;i<3;i++){
		tile[i][c]->removePossibility(remove);
	}
}
