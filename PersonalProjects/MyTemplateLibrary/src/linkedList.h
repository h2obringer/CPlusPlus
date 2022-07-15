/*
 * linkedList.h
 *
 *  Created on: Jul 29, 2015
 *      Author: obringer
 */

//TODO: FINISH
#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <cstdlib>
#include <algorithm> //provide swap function

using namespace std;

template <class T>
class LinkedNode {
	public:
		LinkedNode(T v);
		LinkedNode(const LinkedNode& node);
		~LinkedNode();
		void setNext(LinkedNode<T>* n);
		void setValue(T v);
		LinkedNode<T>* getNext();
		T getValue();
	private:
		T value;
		LinkedNode<T>* next;
};

template <class T>
class LinkedList {
	public:
		LinkedList();
		~LinkedList();
		void add(T v);
		void remove(T v);
		void display();

	private:
		LinkedNode<T>* head;
		LinkedNode<T>* current;
};

template <class T> LinkedNode<T>::LinkedNode(T v) {
	value = v;
	next = NULL; //NULL is in cstdlib
}

template <class T> LinkedNode<T>::LinkedNode(const LinkedNode& node){
	//Exception proof way to write copy constructor
	LinkedNode tmp(node);
	std::swap(value,tmp.value);
	std::swap(next,tmp.next);
}

template <class T> LinkedNode<T>::~LinkedNode() {
	//TODO: unimplemented
}

template <class T> void LinkedNode<T>::setNext(LinkedNode<T>* n){
	next = n;
}

template <class T> void LinkedNode<T>::setValue(T v){
	value = v;
}

template <class T> LinkedNode<T>* LinkedNode<T>::getNext(){
	return next;
}

template <class T> T LinkedNode<T>::getValue(){
	return value;
}

template <class T> LinkedList<T>::LinkedList() {
	head=current=NULL;

}

template <class T> LinkedList<T>::~LinkedList() {
	current=head;
	while(current!=NULL){
		head=current->getNext();
		//required to eliminate double freed or corruption errors
		if (head != current){
			delete current;
		}
		head=current;
	}
	delete head;
}

template <class T> void LinkedList<T>::add(T v){
	if(head==NULL){
		head = new LinkedNode<T>(v);
		head->setNext(NULL);
	}else{
		current=head;
		LinkedNode<T>* next = current->getNext();
		while(current!=NULL){
			if(v < current->getValue()){
				DoubleLinkedNode<T>* temp = new DoubleLinkedNode<T>(v);
				if(head==current){
					head=temp;
				}else{
					//current->getPrevious()->setNext(temp);
				}
				temp->setNext(current);
				return;
			}else{
				if(next==NULL){
					DoubleLinkedNode<T>* temp = new DoubleLinkedNode<T>(v);
					current->setNext(temp);
					temp->setNext(NULL);
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

template <class T> void LinkedList<T>::remove(T v){
	current=head;
	while(current!=NULL){
		if(current->getValue()==v){
			if(current==head){
				head=current->getNext();
				delete current;
			}else{ //guaranteed to have at least 1 item after current if here
				//TODO: rework
//				current->getPrevious()->setNext(current->getNext());
//				current->getNext()->setPrevious(current->getPrevious());
				delete current;
			}
			return;
		}else{
			current=current->getNext();
		}
	}
}

template <class T> void LinkedList<T>::display(){
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



#endif /* LINKEDLIST_H_ */
