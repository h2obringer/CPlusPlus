/*
 * main.cc
 *
 *  Created on: Jul 24, 2015
 *      Author: obringer
 */
#include <iostream>
#include <cstdlib>

#include "doubleLinkedList.h"
#include "vector.h"
#include "linkedList.h"

using namespace std;

int main(){

//	DoubleLinkedList<int> list;
//	list.add(1);
//	list.add(3);
//	list.add(5);
//	list.add(0);
//	list.add(4);
//	list.add(3);
//	list.add(2);
//	list.add(6);
//	list.remove(0);
//	list.remove(6);
//	list.remove(3);
//
//	list.display();
//
//	list.displayReversed();

	LinkedList<int> list;
	list.add(2);
	list.add(1);
	list.add(3);
	list.add(0);
	list.add(89);
	list.add(3);

	list.display();
	exit(0);
}



