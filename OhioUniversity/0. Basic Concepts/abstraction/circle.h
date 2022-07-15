#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

class Circle:public Shape{
	public:
		Circle(int radius);
		void draw();
	private:
		int radius;
};

#endif