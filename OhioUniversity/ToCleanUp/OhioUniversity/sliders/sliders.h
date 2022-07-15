//****************************************************************************
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Program: sliders.h
//
//  Description: This is the header of sliders. A class that 
//    analyzes a board position and will tell you the moves necessary to get 
//    to the start position in a 3x3 slider puzzle (with one piece missing to allow sliding)
//
//  Assumptions: The start position string is " 12345678"
//  		or in matrix form:	
//						12
//				       345
//				       678
//
//  Last Updated: 5/10/2011
//
//****************************************************************************
#ifndef SLIDERS_H
#define SLIDERS_H

#include <queue>
#include <set>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class sliders{
	public:
		void BFS(string &v);
	private:
		string build_sequence(string const &start,string const &next,string &answer);
		void build_adjacent_vertex_list(pair<string,string> &p,vector <pair <string,string> > &avl);
};

#endif
