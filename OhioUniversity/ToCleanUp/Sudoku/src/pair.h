/*
 * pair.h
 *
 *  Created on: Jul 30, 2015
 *      Author: obringer
 */

#ifndef PAIR_H_
#define PAIR_H_

template <class T, class U>
class Pair {
	public:
		Pair(T f,U s);
		Pair(const Pair& p);
		~Pair();
		T getFirst();
		U getSecond();
		void setFirst(T f);
		void setSecond(U s);
	private:
		T first;
		U second;
};

template <class T, class U> Pair<T,U>::Pair(T f,U s){
	first=f;
	second=s;
}

template <class T, class U> Pair<T,U>::Pair(const Pair& p){
	first=p.first;
	second=p.second;
}

template <class T, class U> Pair<T,U>::~Pair(){
	//TODO: unimplemented
}

template <class T, class U> T Pair<T,U>::getFirst(){
	return first;
}

template <class T, class U> U Pair<T,U>::getSecond(){
	return second;
}

template <class T, class U> void Pair<T,U>::setFirst(T f){
	first = f;
}

template <class T, class U> void Pair<T,U>::setSecond(U s){
	second = s;
}

#endif /* PAIR_H_ */
