#include "shape.h"
#include "rectangle.h"
#include "square.h"
#include "circle.h"
using namespace std;

int main(){
	Shape* ptr;
	Rectangle* rect = new Rectangle(4,5);
	Square* sq = new Square(4);
	Circle* circ = new Circle(3);
	
	ptr = rect;
	ptr->draw();
	ptr->test();
	
	ptr = sq;
	ptr->draw();
	ptr->test();
	
	ptr = circ;
	ptr->draw();
	ptr->test();
}