#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
using namespace std;

class Rectangle:public Shape{
	public:
		Rectangle(int width,int height);
		void draw();
	protected:
		int width;
		int height;
};

#endif