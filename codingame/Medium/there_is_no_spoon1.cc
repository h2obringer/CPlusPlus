/*Author: Randal Obringer
*
* Last Date Modified: 20 August 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: The game is played on a rectangular grid with a given 
*	size. Some cells contain power nodes. The rest of the cells are empty.
*	The goal is to find, when they exist, the horizontal and vertical 
*	neighbors of each node.
*
* Rules: To do this, you must find each (x1,y1) coordinates containing a 
*	node, and display the (x2,y2) coordinates of the next node to the right, 
*	and the (x3,y3) coordinates of the next node to the bottom within the 
*	grid. If a neighbor does not exist, you must output the coordinates -1 
*	-1 instead of (x2,y2) and/or (x3,y3).
*
*	You lose if:
*		You give an incorrect neighbor for a node.
*		You give the neighbors for an empty cell.
*		You compute the same node twice.
*		You forget to compute the neighbors of a node.
*
* Victory Conditions: You win when all nodes have been correctly displayed.
*
* Game Input: The program must first read the initialization data from 
*	standard input. Then, provide to the standard output one line per 
*	instruction.
*
*	Initialization input:
*		Line 1: one integer width for the number of cells along the x axis.
*		Line 2: one integer height for the number of cells along the y axis.
*		Next height lines: A string  line  containing  width  characters. 
*			A dot . represents an empty cell. A zero 0 represents a cell 
*			containing a node.
*
* Output for one game turn:
*	One line per node. Six integers on each line:   x1  y1  x2  y2  x3  y3
*	Where:
*		(x1,y1) the coordinates of a node
*		(x2,y2) the coordinates of the closest neighbor on the right of the node
*		(x3,y3) the coordinates of the closest bottom neighbor
*	If there is no neighbor, the coordinates should be -1 -1.
*
* Constraints:
*	0 < width ≤ 30
*	0 < height ≤ 30
*	0 ≤ x1 < width
*	0 ≤ y1 < height
*	-1 ≤ x2, x3 < width
*	-1 ≤ y2, y3 < height
*	Alloted response time to first output line ≤ 1s.
*	Response time between two output lines ≤ 100ms
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    
    string answer = "";
    bool node[height][width];
    
    //build our map of the nodes
    for (int i = 0; i < height; i++) {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        for(int j = 0; j < width; j++){
            if(line[j]=='0'){
                node[i][j]=true;
            }else{
                node[i][j]=false;
            }
        }
    }
    
    int h,v=0;
    bool r_n = false; //is there a right neighbor?
    bool b_n = false; //is there a bottom neighbor?
    
    // Build the three coordinates: a node (h,v), its right neighbor(h,v), its bottom neighbor(h,v)
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            r_n=b_n=false; //reset
            answer = ""; //reset
            if(node[i][j]){ //found a node
                answer=answer+to_string(j)+" "+to_string(i)+" ";
                for(int k=j+1;k<width;k++){ //search only right of current node
                    if(node[i][k]){ //found its right neighbor
                        answer=answer+to_string(k)+" "+to_string(i)+" ";
                        r_n=true;
                        break; //found it, no need to continue
                    }
                }
                if(r_n==false){ //if there was no right neighbor
                    answer=answer+to_string(-1)+" "+to_string(-1)+" ";
                }
                for(int k=i+1;k<height;k++){ //search only below current node
                    if(node[k][j]){ //found its bottom neighbor
                        answer=answer+to_string(j)+" "+to_string(k)+" ";
                        b_n=true; //needed because we will break out of the loop. either way
                        break; //found it, no need to continue
                    }
                }
                if(b_n==false){ //if there was no bottom neighbor
                    answer=answer+to_string(-1)+" "+to_string(-1)+" ";
                }
				
				//cout << "0 0 1 0 0 1" << endl; // Three coordinates: a node, its right 
				//neighbor, its bottom neighbor
                cout << answer << endl; //output for neighbors of current node
            }
        }
    }    
}