#include <iostream>
#include "board.h"
#include <queue>

int main(){
	queue<int> myQueue;
	myQueue.push(1);
	myQueue.push(2);
	myQueue.push(3);
	cout << myQueue.front() << ", "; myQueue.pop();
	cout << myQueue.front() << ", "; myQueue.pop();
	cout << myQueue.front() << endl; myQueue.pop();

	Board board;
	board.output();
	board.getTile(0,0)->getSquare(0,0)->showPossibilities();
	board.getTile(0,0)->getSquare(0,0)->setAnswer(9);
	board.getTile(0,0)->getSquare(0,0)->showPossibilities();
	board.output();

}




