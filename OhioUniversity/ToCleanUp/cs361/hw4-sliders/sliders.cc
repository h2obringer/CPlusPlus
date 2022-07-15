//****************************************************************************
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Program: sliders.cc
//
//  Description: This is the class implementation of sliders. A class that 
//    analyzes a board position and will tell you the moves necessary to get 
//    to the start position.
//
//  Assumptions: The start position string is " 12345678"
//  		or in matrix form:	12
//				       345
//				       678
//
//  Last Updated: 5/10/2011
//
//****************************************************************************
#include "sliders.h"

#include <queue>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

//****************************************************************************
// Function: build_adjacent_vertex_list (private)
//
// Parameters: 
//    1. a pair of strings. The first being the starting position of the board
//         and the second being the moves needed to get there. The moves are
//         very important and will become the final output for the BFS function
//    2. a vector of pairs similar to the first parameter (This is passed by
//         reference so as to modify it so that nothing has to be returned by
//         the function)
//
// Description/Effect: fills a vector with the adjacent vertices to the current 
//   vertex
//
//***************************************************************************** 
void sliders::build_adjacent_vertex_list(pair<string,string> &p,vector <pair <string,string> > &avl){ //parameters:(string &v,vector<string> &avl)
 //following is to find vertices avl adjacent to v
  int index;
  //find index of where empty space is in slider position
  string v=p.first;
  for(int i=0;i<v.length();i++){
    if(v[i]==' '){
      index=i;
      break;
    }
  }
  string temp;
  string moves;
  
  //add all posible adjacent vertices to the vector
  if((index!=0)&&(index!=3)&&(index!=6)){
    temp=v;
    moves=p.second;
    temp[index]=temp[index-1];
    temp[index-1]=' ';
    moves+="R";
    pair<string,string> p2(temp,moves);
    avl.push_back(p2);
  }
  if((index!=2)&&(index!=5)&&(index!=8)){
    temp=v;
    moves=p.second;
    temp[index]=temp[index+1];
    temp[index+1]=' ';
    moves+="L";
    pair<string,string> p2(temp,moves);
    avl.push_back(p2);
  }
  if((index!=0)&&(index!=1)&&(index!=2)){
    temp=v;
    moves=p.second;
    temp[index]=temp[index-3];
    temp[index-3]=' ';
    moves+="D";
    pair<string,string> p2(temp,moves);
    avl.push_back(p2);
  }
  if((index!=6)&&(index!=7)&&(index!=8)){
    temp=v;
    moves=p.second;
    temp[index]=temp[index+3];
    temp[index+3]=' ';
    moves+="U";
    pair<string,string> p2(temp,moves);
    avl.push_back(p2);
  }
}

//***************************************************************************************
// Function: BFS (public)
//
// Parameters: a string (this will be the starting position of the board in sliders)
//
// Description: This is a modified version of the BFS function given in class. It uses
//   strings and not integers. It shows line for line what lines I have replaced from
//   the original function in order to make it work for my problem.
//
// Effect: outputs to the screen the moves needed to complete the slider puzzle in order
// 
//***************************************************************************************
void sliders::BFS(string &v){
  try{
    if(v==" 12345678"){
      cout << "This board is already correct" << endl;
      throw 0;
    }
  
    set<string> visited;			//visited = new bool[n]; 
         				//for(size_t i=0; i<n;++i){ 
			     		//visited[v]=false; }
    visited.insert(v);         		//visited[v]=true;
    queue <pair <string,string> > q;
    pair<string,string> p(v,"");
    q.push(p);
    while(!q.empty()){
      p=q.front(); 			//v=q.front();
      q.pop();

      vector <pair <string,string> > adjacent_vertices; //for(all vertices w adjacent to v){
      build_adjacent_vertex_list(p,adjacent_vertices);

      vector <pair<string,string> >::iterator p;
      for(p=adjacent_vertices.begin();p!=adjacent_vertices.end();++p){
        if(p->first==" 12345678"){
          cout << p->second << endl;
          adjacent_vertices.clear();
          throw 0; //transfer flow of control to end of function
          //exit(-1);
        }
        if(visited.count(p->first)==0){	//if(!visited[w]){
          q.push(*p);			//q.push(w);
          visited.insert(p->first);	//visited[w]=true;
        }
      }  //end for loop					//end for(all vertices w adjacent to v)
    }  //end while loop
    if(q.empty()){  
      cout << "impossible" << endl;
    }
  }//end try
  catch(...){ //transfer flow of control
    ;
  }
}
