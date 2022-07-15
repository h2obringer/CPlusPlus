/*
 * vector
 *
 *  Created on: Jul 29, 2015
 *      Author: obringer
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
using namespace std;

template <class T>
class Vector {
	public:
		Vector();
		Vector(const Vector& vector);
		//Vector(const T[]& array); //TODO: pass an array as an argument
		~Vector();
		void insert(T item);
		void reassign(T item, int i);
		T itemAt(int i);
		int getSize();
		int getCapacity();
		void display();
		//TODO: overload [] operator to use like a regular array to return items if possible
	private:
		void resize();
		T vector[];
		int size;
		int capacity;

};

template <class T> Vector<T>::Vector(){
	size=0;
	capacity=2;
	//vector = new T[capacity]; //TODO: fix initializing size of array
}

template <class T> Vector<T>::Vector(const Vector& v){
	size = v.size;
	capacity = v.capacity;
	for(int i=0;i<size;i++){
		vector[i] = v[i];
	}
}

template <class T> Vector<T>::~Vector(){
	//TODO:
}

template <class T> void Vector<T>::insert(T item){
	if(size==capacity){
		resize();
	}
	vector[size] = item; //works because array is assigned 0 - size-1
	++size;
}

template <class T> void Vector<T>::reassign(T item, int i){
	if(i>size-1){
		return;
	}
	vector[i]=item;
}

template <class T> T Vector<T>::itemAt(int i){
	return vector[i];
}

template <class T> int Vector<T>::getCapacity(){
	return capacity;
}

template <class T> int Vector<T>::getSize(){
	return size;
}

template <class T> void Vector<T>::display(){
	cout << "[";
	for(int i=0;i<size;i++){
		cout << vector[i];
		if(i!=size-1){
			cout << ", ";
		}
	}
	cout << "]" << endl;
}

template <class T> void Vector<T>::resize(){
	capacity*=2;
	T temp[size]; //TODO: fix initializing size of array
	for(int i=0;i<size;i++){
		temp[i]=vector[i];
	}
	vector[capacity]; //TODO: fix initializing size of array
	for(int i=0;i<size;i++){
		vector[i]=temp[i];
	}
}

#endif /* VECTOR_H_ */
