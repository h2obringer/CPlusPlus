#include "rectangle.h"
using namespace std;

Rectangle::Rectangle(int width,int height){
	type = "Rectangle";
	this->width=width;
	this->height=height;
}

void Rectangle::draw(){
	cout << type << ": " << width << ", " << height << endl;
}