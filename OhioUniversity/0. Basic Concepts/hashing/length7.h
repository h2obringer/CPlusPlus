//**************************************************************************************
//File: length7.h
//
//Author: Randal Obringer
//
//Date Last Modified: ~2011
//
//Desciption: Class header for hashing class computing hash values for strings A-ZZZZZZZ
//**************************************************************************************

#ifndef LENGTH7_H
#define LENGTH7_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

class length7{
	public:
		length7();
		long long hash(string &x,int M); //Compute hash value on a string given the hashcode# (M)
		void compute(); //brute force algorithm. Compute hash values for strings A-ZZZZZZZ
		//Accessors
		long long get0();
		long long get996();
		long long get500();
		long long get400();
		long long get211();
		long long getTotal();
	private:
		long long HASH0;
		long long HASH996;
		long long HASH500;
		long long HASH400;
		long long HASH211;
		long long TOTAL;
};

#endif
