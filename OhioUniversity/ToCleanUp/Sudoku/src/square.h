/*
 * square.h
 *
 *  Created on: Sep 30, 2015
 *      Author: obringer
 */

#ifndef SQUARE_H
#define SQUARE_H
#include <set>
#include <iostream>
using namespace std;

class Square{
	public:
		Square(int r, int c);
		~Square();
		void removePossibility(int num);
		int getAnswer();
		void setAnswer(int num);
		void setAnswer();
		void showPossibilities();
	protected:
	private:
		set<int> possibilities;
		int answer;
		int row; //used in solve() at Board level
		int column;
};



#endif /* SQUARE_H_ */
