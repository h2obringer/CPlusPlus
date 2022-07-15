#include "circle.h"
using namespace std;

Circle::Circle(int radius){
	this->radius=radius;
	type="Circle";
}

void Circle::draw(){
	cout << type << ": " << "Area is " << radius*radius*3.14 << endl;
}