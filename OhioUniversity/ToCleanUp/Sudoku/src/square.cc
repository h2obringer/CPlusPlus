#include "square.h"

Square::Square(int r, int c){
	answer=0;
	row=r;
	column=c;
	possibilities.insert(1);
	possibilities.insert(2);
	possibilities.insert(3);
	possibilities.insert(4);
	possibilities.insert(5);
	possibilities.insert(6);
	possibilities.insert(7);
	possibilities.insert(8);
	possibilities.insert(9);
}

Square::~Square(){
	possibilities.clear();
	answer=0;
}

void Square::removePossibility(int num){
	possibilities.erase(num);
	setAnswer();
	//idea: return a pair of numbers here for which row/column we
	//just set the answer for so we can "smartly" remove other possibilities
}

int Square::getAnswer(){
	return answer;
}

void Square::setAnswer(int num){
	answer=num;
	possibilities.clear();
}

void Square::setAnswer(){
	if(possibilities.size()==1){
		answer=*possibilities.begin();
	}
}

void Square::showPossibilities(){
	for(set<int>::iterator it=possibilities.begin();it!=possibilities.end();++it){
		if(it!=possibilities.begin()){
			cout << ", ";
		}
		cout << *it;
	}
	cout << endl;
}
