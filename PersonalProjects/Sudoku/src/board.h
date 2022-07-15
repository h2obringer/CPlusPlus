
#ifndef BOARD_H
#define BOARD_H

#include "tile.h"
#include "pair.h"
#include <iostream>
#include <queue>

using namespace std;

class Board{
	public:
		Board();
		~Board();
		void output();
		Tile* getTile(int r, int c);
		void remove_tile_possibilities(int remove,int tr,int tc);
		void remove_row_possibilities(int remove,int r);
		void remove_column_possibilities(int remove,int c);
		void solve();
	protected:
	private:
		Tile* board[3][3];
};




#endif /* BOARD_H_ */
