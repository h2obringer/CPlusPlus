//****************************************************************************
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Program: EscapeTheMaze.cc
//
//  Description: This is the class implementation of EscapeTheMaze, A class that 
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

#include "EscapeTheMaze.h"

//****************************************************************************
// Function: length(private)
//
// Parameters: 
//    1.a maze given in vector<string> form (passed by reference) 
//    2.a, an integer, this is the vertical position in the vector
//	and part of the current coordinate
//    3.b, an integer, this is the horizontal position in the vector
//	and part of the cuurent coordinate
//    4.c, an integer, this is the vertical position in the vector
//	and part of the coordinate adjacent to the current vertex
//    5.d, an integer, this is the horizontal position in the vector
//	and part of the coordinate adjacent to the current vertex
//
// Description/Effect: computes the weight between two coordinates in the maze.
//
//***************************************************************************** 
int EscapeTheMaze::length(vector<string> &maze,const int a,const int b,const int c,const int d){
	//(a,b) is the current coordinate
	//(c,d) is neighbor
	if((a==c)&&(b==d)){ 
		return 0;
	}else if((b==d-1)&&(a==c)&&(maze[c][d]!='*')){ //move left from current coordinate
		return (maze[c][d]-'0');
	}else if((b==d+1)&&(a==c)&&(maze[c][d]!='*')){ //move right from current coordinate
		return (maze[c][d]-'0');
	}else if((b==d)&&(a==c+1)&&(maze[c][d]!='*')){ //move down from current coordinate
		return (maze[c][d]-'0');
	}else if((b==d)&&(a==c-1)&&(maze[c][d]!='*')){ //move up from current coordinate
		return (maze[c][d]-'0');
	}else{
		return BIG_VALUE;
	}
}

//****************************************************************************
// Function: previous(private)
//
// Parameters: 
//    1.a maze given in vector<string> form (passed by reference) 
//    2.a, an integer, this is the vertical position in the vector
//	and part of the current coordinate
//    3.b, an integer, this is the horizontal position in the vector
//	and part of the cuurent coordinate
//    4.c, an integer, this is the vertical position in the vector
//	and part of the coordinate adjacent to the current vertex
//    5.d, an integer, this is the horizontal position in the vector
//	and part of the coordinate adjacent to the current vertex
//
// Description/Effect: Updates the from array to allow us to back track to the
// 	starting vertex
//
//*****************************************************************************
pair<int,int> EscapeTheMaze::previous(vector<string> &maze,const int a,const int b,const int c,const int d){
	if((a==c)&&(b==d)){ //from coordinate to itself should be infinite to prevent from going there
		return pair<int,int>(-1,-1);
	}else if((b==d-1)&&(a==c)&&(maze[c][d]!='*')&&(maze[a][b]!='*')){ //move left from current coordinate
		return pair<int,int>(a,b);
	}else if((b==d+1)&&(a==c)&&(maze[c][d]!='*')&&(maze[a][b]!='*')){ //move right from current coordinate
		return pair<int,int>(a,b);
	}else if((b==d)&&(a==c+1)&&(maze[c][d]!='*')&&(maze[a][b]!='*')){ //move down from current coordinate
		return pair<int,int>(a,b);
	}else if((b==d)&&(a==c-1)&&(maze[c][d]!='*')&&(maze[a][b]!='*')){ //move up from current coordinate
		return pair<int,int>(a,b);
	}else{
		return pair<int,int>(-1,-1);
	}
}

//****************************************************************************
// Function: lengthShortestExit(public)
//
// Parameters: 
//    1. a maze given in vector<string> form 
//    2. x, an integer, part of the starting coordinate
//    3. y, an integer, part of the starting coordinate
//
// Description/Effect: Computes the length of the shortest distance out of the 
//    maze from the start vertex. This is djikstras algorithm.
//
//*****************************************************************************
int EscapeTheMaze::lengthShortestExit(vector<string> &maze, int x, int y){
	//Initialize loop
	int a=maze.size(); 
	int b=maze[0].length(); 
   
	for(int i=0;i<a;++i){
		for(int j=0;j<b;++j){
			s[i][j]=false; //none of maze positions have been discovered yet
			dist[i][j]=length(maze,x,y,i,j); //initialize the weight array
		}
	}
	
	s[x][y]=true; //the source is discovered
	dist[x][y]=0; //the distance to the source from the source is 0
	int n=a*b; //the number of nodes in the graph

	//determine n-1 paths from vertex
	for(int i=0;i<(n-2);++i){
		pair<int,int> u=choose(a,b); //choose the least weight node from the source
		if (u.first==-1) break;
		s[u.first][u.second]=true;
		
		for(int v=0;v<a;++v){
			for(int w=0;w<b;++w){
				if(!s[v][w]){ //if the node was not discovered
					if(dist[u.first][u.second]+length(maze,u.first,u.second,v,w)<dist[v][w]){ //relax edges in graph
						dist[v][w]=dist[u.first][u.second]+length(maze,u.first,u.second,v,w);
					}
				}
			}
		}
	}//end for loop
	
	int min=minimum(a,b); 
	return min+(maze[x][y]-'0'); //return the total distance of the shortest path
}


//get the minimum path value from the outskirts of the graph. It represents the shortest path to the exit.
int EscapeTheMaze::minimum(const int a,const int b){
	int min=BIG_VALUE;
	
	for(int i=0;i<a;i++){ //check min distances on outskirts of the graph
		if(dist[i][0]<min) min=dist[i][0]; 
		if(dist[i][b-1]<min) min=dist[i][b-1];
	}
	
	for(int j=0;j<b;j++){ //check min distances on outskirts of the graph
		if(dist[0][j]<min) min=dist[0][j];
		if(dist[a-1][j]<min) min=dist[a-1][j];
	}
	
	return min;
}


//****************************************************************************
// Function: shortestExit(public)
//
// Parameters: 
//    1. a maze given in vector<string> form
//    2. x, an integer, part of the starting coordinate
//    3. y, an integer, part of the starting coordinate    
//
// Description/Effect: Updates the from array to allow us to back track to the
// 	starting coordinate. Utilizes djikstras algorithm.
//
//*****************************************************************************
vector<string> EscapeTheMaze::shortestExit(vector<string> &maze, int x, int y){
	//Initialize loop
	int a=maze.size(); 
	int b=maze[0].length(); 
	
	//initialize discovered, previous, and weight arrays
	for(int i=0;i<a;++i){
		for(int j=0;j<b;++j){
			s[i][j]=false; 
			dist[i][j]=length(maze,x,y,i,j);
			from[i][j]=previous(maze,x,y,i,j);
		}
	}
	
	s[x][y]=true; //the source is discovered
	dist[x][y]=0; //distance from source to source is 0
	from[x][y]=make_pair(-1,-1); //there is no previous node to the source
  
	int n=a*b; //the number of nodes in the graph

	//determine n-1 paths from vertex
	for(int i=0;i<(n-2);++i){
		pair<int,int> u=choose(a,b); //choose the least cost node in the graph
		if (u.first==-1) break;
		s[u.first][u.second]=true; //the node is now discovered
		
		for(int v=0;v<a;++v){
			for(int w=0;w<b;++w){
				previous(maze,v,w,u.first,u.second);
				if(!s[v][w]){  //if the vertex is not discovered
					if(dist[u.first][u.second]+length(maze,u.first,u.second,v,w)<dist[v][w]){ //relax the edge
						dist[v][w]=dist[u.first][u.second]+length(maze,u.first,u.second,v,w);
						from[v][w]=u;
					}
				}
			}
		}
	}//end for loop
	
	return backTrack(maze,a,b);
}


//****************************************************************************
// Function: backTrack(private)
//
// Parameters: 
//    1. a maze given in vector<string> form
//    2. x, an integer, the size of the vertical distance of the maze
//    3. y, an integer, the size of the hortizontal distance of the maze
//
// Description/Effect: Changes the shortest path of the maze to '+' 
//
//*****************************************************************************
vector<string> EscapeTheMaze::backTrack(vector<string> &maze,const int a,const int b){
	vector<string> shortest=maze;
	int min=BIG_VALUE;
	int minV=0;
	int minH=0;
	
	for(int i=0;i<a;i++){ //check min distances on outskirts of the graph
		if(dist[i][0]<min){
			min=dist[i][0]; 
			minV=i;
			minH=0;
		}
		if(dist[i][b-1]<min){
			min=dist[i][b-1];
			minV=i;
			minH=b-1;
		}
	}
	
	for(int j=0;j<b;j++){ //continue checking min distances on outskirts of the graph
		if(dist[0][j]<min){
			min=dist[0][j];
			minV=0;
			minH=j;
		}
		if(dist[a-1][j]<min){
			min=dist[a-1][j];
			minV=a-1;
			minH=j;
		}
	}
	
	int v=minV;
	int h=minH;
	int tempV;
	int tempH;
	do{ //do the actual backtracking
		if((v==0)&&(h==0)){ //if no path out from start vertex was found on the outskirts of the graph
			shortest.clear(); //clear the graph
			shortest.push_back("No path out"); //The graph is now this.
			break;
		}
		shortest[v][h]='+'; //change the path to show the answer
		//walk to the previous vertex
		tempV=from[v][h].first; 
		tempH=from[v][h].second;
		v=tempV;
		h=tempH;
	}while(v!=-1);
	
	return shortest;
}

//****************************************************************************
// Function: shortestExit(public)
//
// Parameters: 
//    1. x, an integer, the size of the vertical length of the maze
//    2. y, an integer, the size of the horizontal length of the maze
//
// Description/Effect: Chooses vertices on the graph
//
//*****************************************************************************
pair<int,int> EscapeTheMaze::choose(const int x,const int y){
	int prevmax=-1;
	int index_x=-1;
	int index_y=-1;
	
	//for all nodes in the graph
	for(int i=0;i<x;++i){
		for(int j=0;j<y;++j){ 
			if((!s[i][j])&&((prevmax==-1)||(dist[i][j]<prevmax))){ //if node is not discovered and first run through loop or node weight is less than current max weight value
				prevmax=dist[i][j];
				index_x=i;
				index_y=j;
			}
		}
	}
	
	//if the coordinate picked was a '*'
	if (prevmax==BIG_VALUE) index_x=-1; 
	pair<int,int> p(index_x,index_y); //return the coordinates of the chosen node
	if(prevmax==-1){
		cout << "error PREVMAX=-1\n";
	}
	return p;
}
