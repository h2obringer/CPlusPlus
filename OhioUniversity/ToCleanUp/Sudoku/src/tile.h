/*
 * tile.h
 *
 *  Created on: Sep 30, 2015
 *      Author: obringer
 */

#ifndef TILE_H
#define TILE_H

#include "square.h"
#include <iostream>
using namespace std;

class Tile{
	public:
		Tile(int r, int c);
		~Tile();
		void output();
		Square* getSquare(int r, int c);
		void remove_tile_possibilities(int remove);
		void remove_row_possibilities(int remove,int r);
		void remove_column_possibilities(int remove,int c);
	protected:
	private:
		Square* tile[3][3];
		int row;
		int column;
};



#endif /* TILE_H */
