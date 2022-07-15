//****************************************************************************
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Program: EscapeTheMaze.h
//
//  Description: This is the class declaration of EscapeTheMaze, a class that 
//    analyzes a maze and will tell you important information in order to get out
//    of the maze
//
//  Assumptions: We are given a maze in vector<string> form and a coordinate
//  		as a starting point. Also it is assumed that the graph is a
//              square or a rectangle.
//
//  Last Updated: 5/28/2011
//
//****************************************************************************
#ifndef ESCAPETHEMAZE_H
#define ESCAPETHEMAZE_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

class EscapeTheMaze{
  public:
    int lengthShortestExit(vector<string> &maze, int x, int y);
    vector<string> shortestExit(vector<string> &maze, int x, int y);
    
    static const size_t NMAX = 100;
    static const int BIG_VALUE = 1000000;
    
  private:
    vector<string> backTrack(vector<string> &maze,const int a,const int b);
    int minimum(const int a,const int b);
    int length(vector<string> &maze,const int a,const int b,const int c,const int d);
    pair<int,int> previous(vector<string> &maze,const int a,const int b,const int c,const int d);
    pair<int,int> choose(const int x,const int y);

    pair<int,int> from[NMAX][NMAX]; //gives the coordinates of the vertex the current vertex came from
    int dist[NMAX][NMAX]; //length of shortest path
    bool s[NMAX][NMAX]; //tells if the shortest length to that vertex has been found or not
};

#endif
