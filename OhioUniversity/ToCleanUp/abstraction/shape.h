#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>
using namespace std;

class Shape{
	public:
		Shape(){ type = "Shape"; };
		virtual void draw() = 0;
		virtual void test(){ cout << "This is implemented in Shape object! Did not have to overwrite it!" << endl; };
	protected:
		string type;
};

#endif