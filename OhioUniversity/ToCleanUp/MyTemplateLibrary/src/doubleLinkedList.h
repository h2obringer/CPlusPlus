/*
 * doubleLinkedList.h
 *
 *  Created on: Jul 28, 2015
 *      Author: obringer
 *
 *      Any class that uses this template must overload the "<",">", and "==" operators
 *
 *      Implementation is in the header because it is the only way to make templates work
 */

#ifndef DOUBLELINKEDLIST_H_
#define DOUBLELINKEDLIST_H_

#include <iostream>
#include <cstdlib>
#include <algorithm> //provide swap function

using namespace std;

template <class T>
class DoubleLinkedNode {
	public:
		DoubleLinkedNode(T v);
		DoubleLinkedNode(const DoubleLinkedNode& node);
		~DoubleLinkedNode();
		void setNext(DoubleLinkedNode<T>* n);
		void setPrevious(DoubleLinkedNode<T>* p);
		void setValue(T v);
		DoubleLinkedNode<T>* getNext();
		DoubleLinkedNode<T>* getPrevious();
		T getValue();
	private:
		T value;
		DoubleLinkedNode<T>* next;
		DoubleLinkedNode<T>* previous;
};

template <class T>
class DoubleLinkedList {
	public:
		DoubleLinkedList();
		~DoubleLinkedList();
		void add(T v);
		void remove(T v);
		void display();
		void displayReversed();

	private:
		DoubleLinkedNode<T>* head;
		DoubleLinkedNode<T>* current;
		DoubleLinkedNode<T>* tail;
};

template <class T> DoubleLinkedNode<T>::DoubleLinkedNode(T v) {
	value = v;
	next = NULL; //NULL is in cstdlib
	previous = NULL;
}

template <class T> DoubleLinkedNode<T>::DoubleLinkedNode(const DoubleLinkedNode& node){
	//Exception proof way to write copy constructor
	DoubleLinkedNode tmp(node);
	std::swap(value,tmp.value);
	std::swap(previous,tmp.previous);
	std::swap(next,tmp.next);
}

template <class T> DoubleLinkedNode<T>::~DoubleLinkedNode() {
	//TODO: unimplemented
}

template <class T> void DoubleLinkedNode<T>::setNext(DoubleLinkedNode<T>* n){
	next = n;
}

template <class T> void DoubleLinkedNode<T>::setPrevious(DoubleLinkedNode<T>* p){
	previous = p;
}

template <class T> void DoubleLinkedNode<T>::setValue(T v){
	value = v;
}

template <class T> DoubleLinkedNode<T>* DoubleLinkedNode<T>::getNext(){
	return next;
}

template <class T> DoubleLinkedNode<T>* DoubleLinkedNode<T>::getPrevious(){
	return previous;
}

template <class T> T DoubleLinkedNode<T>::getValue(){
	return value;
}

template <class T> DoubleLinkedList<T>::DoubleLinkedList() {
	head=tail=current=NULL;

}

template <class T> DoubleLinkedList<T>::~DoubleLinkedList() {
	current=head;
	while(current!=NULL){
		head=current->getNext();
		//required to eliminate double freed or corruption errors
		if (head != current && tail != current){
			delete current;
		}
		head=current;
	}
	if (tail != head)
		delete tail;
	delete head;
}

template <class T> void DoubleLinkedList<T>::add(T v){
	if(head==NULL){
		head = new DoubleLinkedNode<T>(v);
		head->setNext(NULL);
		head->setPrevious(NULL);
		tail=head;
	}else if(head==tail){
		current = head;
		if(v > head->getValue()){
			tail = new DoubleLinkedNode<T>(v);
			tail->setNext(NULL);
			tail->setPrevious(head);
			head->setNext(tail);
		}else{
			head = new DoubleLinkedNode<T>(v);
			head->setNext(current);
			head->setPrevious(NULL);
			current->setPrevious(head);
			tail=current;
		}
	}else{
		current=head;
		DoubleLinkedNode<T>* next = current->getNext();
		while(current!=NULL){
			if(v < current->getValue()){
				DoubleLinkedNode<T>* temp = new DoubleLinkedNode<T>(v);
				if(head==current){
					head=temp;
				}else{
					current->getPrevious()->setNext(temp);
				}
				temp->setPrevious(current->getPrevious());
				temp->setNext(current);
				current->setPrevious(temp);
				return;
			}else{
				if(next==NULL){
					DoubleLinkedNode<T>* temp = new DoubleLinkedNode<T>(v);
					current->setNext(temp);
					temp->setPrevious(current);
					temp->setNext(NULL);
					tail=temp;
					return;
				}else{
					current=next;
					next = next->getNext();
				}
			}
		}

	}
	return;
}

template <class T> void DoubleLinkedList<T>::remove(T v){
	current=head;
	while(current!=NULL){
		if(current->getValue()==v){
			if(head == tail){ //only 1 item
				head=tail=NULL;
				delete current;
			}else if(current==head){
				head=current->getNext();
				head->setPrevious(NULL);
				delete current;
			}else if(current==tail){
				tail=current->getPrevious();
				tail->setNext(NULL);
				delete current;
			}else{ //guaranteed to have at least 1 item before and after current if here
				current->getPrevious()->setNext(current->getNext());
				current->getNext()->setPrevious(current->getPrevious());
				delete current;
			}
			return;
		}else{
			current=current->getNext();
		}
	}
}

template <class T> void DoubleLinkedList<T>::display(){
	current=head;
	if(current==NULL){
		cout << "List is empty" << endl;
		return;
	}
	while(current!=NULL){
		if(current->getNext()!=NULL){
			cout << current->getValue() << ", ";
		}else{
			cout << current->getValue();
		}
		current = current->getNext();
	}
	cout << endl;
	return;
}

template <class T> void DoubleLinkedList<T>::displayReversed(){
	current=tail;
	if(current==NULL){
		cout << "List is empty" << endl;
		return;
	}
	while(current!=NULL){
		if(current->getPrevious()!=NULL){
			cout << current->getValue() << ", ";
		}else{
			cout << current->getValue();
		}
		current = current->getPrevious();
	}
	cout << endl;
	return;
}

#endif /* DOUBLELINKEDLIST_H_ */

