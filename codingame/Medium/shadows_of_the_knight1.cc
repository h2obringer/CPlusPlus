/*Author: Randal Obringer
*
* Last Date Modified: 20 August 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Description: Given the direction of a bomb, bisect in half the building windows 0 to width, 
*  0 to height till batman finds the bomb. If you move in the same direction more than 3 times,
*  bisect 65% (more aggressively), instead of 50% to search more area faster.
*
* Problem Statement: Batman will look for the hostages on a given building 
*	by jumping from one window to another using his grapnel gun. Batman's 
*	goal is to jump to the window where the hostages are located in order 
*	to disarm the bombs. Unfortunately he has a limited number of jumps 
*	before the bombs go off...
*
* Rules: Before each jump, the heat-signature device will provide Batman 
*	with the direction of the bombs based on Batman current position:
*		U (Up)
*		UR (Up-Right)
*		R (Right)
*		DR (Down-Right)
*		D (Down)
*		DL (Down-Left)
*		L (Left)
*		UL (Up-Left)
*	Your mission is to program the device so that it indicates the location 
*	of the next window Batman should jump to in order to reach the bombs' 
*	room as soon as possible. Buildings are represented as a rectangular 
*	array of windows, the window in the top left corner of the building is 
*	at index (0,0).
*
* Game Input:
*	The program must first read the initialization data from standard 
*	input. Then, within an infinite loop, read the device data from the 
*	standard input and provide to the standard output the next movement 
*	instruction.
*
* 	Initialization input:
*		Line 1 : 2 integers W H. The (W, H) couple represents the width 
*			and height of the building as a number of windows.
*		Line 2 : 1 integer N, which represents the number of jumps Batman 
*			can make before the bombs go off.
*		Line 3 : 2 integers X0 Y0, representing the starting position of 
*			Batman.
*
*	Input for one game turn: The direction indicating where the bomb is.
*
* Output for one game turn: A single line with 2 integers X Y separated by 
*	a space character. (X, Y) represents the location of the next window 
*	Batman should jump to. X represents the index along the horizontal 
*	axis, Y represents the index along the vertical axis. (0,0) is located 
*	in the top-left corner of the building.
*
* Constraints:
*	1 ≤ W ≤ 10000
*	1 ≤ H ≤ 10000
*	2 ≤ N ≤ 100
*	0 ≤ X, X0 < W
*	0 ≤ Y, Y0 < H
*	Response time per turn ≤ 150ms
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
//credit goes to DevSolar on StackOverflow for this code. Another solution could have been used but I like the simplified usage.
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;

//global variables - determine how aggressive we need to go in a particular direction
//holds how many times you have need to go a certain direction in a row
//currently doing 4th time or more in a row in a single direction will bisect 65% instead of normal 50%
static int countUp = 0; 
static int countDown = 0;
static int countLeft = 0;
static int countRight = 0;

int findNextX(int start_x, int& L_lim, int& R_lim, const string direction){
    int interval = 0; //hold # of windows from batman to edge of building in the direction of the bomb, or from last starting point
    
    for(int i=0;i<direction.length();i++){ //will run max of 2 loops
        if(direction[i]=='R'){
            L_lim = start_x; //if we have to move right then we don't want to ever go farther left than we have previously been
            
            countRight++;
            countLeft=0;
            if(countRight>3){ //bomb is still in the same direction as before last movement so move more aggressively
                interval = 65*(R_lim - start_x)/100;
            }else{
                interval = (R_lim - start_x)/2;
            }
            if(interval == 0){ //ensure progress is being made
                interval = 1;
            }
        }else if(direction[i]=='L'){
            R_lim = start_x; //if we have to move left then we don't want to ever go farther right than we have previously been
            
            countLeft++;
            countRight=0;
            if(countLeft>3){ //bomb is still in the same direction as before last movement so move more aggressively
                interval = -65*(start_x - L_lim)/100;
            }else{
                interval = -1*(start_x - L_lim)/2;
            }
            if(interval == 0){ //ensure progress is being made
                interval = -1;
            }
        }else if(direction[i]=='U'){
            countDown=0; //we will add to countUp in findNextY but we know we aren't going down again so zeroize it
        }else if(direction[i]=='D'){
            countUp=0; //we will add to countDown in findNextY but we know we aren't going up again so zeroize it
        }
    }
    
    return start_x+interval;
}         

int findNextY(int start_y, int& U_lim, int& D_lim, const string direction){
    int interval = 0; //hold # of windows from batman to edge of building in the direction of the bomb, or from last starting point
    
    //countLeft=countRight=0;
    for(int i=0;i<direction.length();i++){ //will run max of 2 loops
        if(direction[i]=='D'){
            U_lim = start_y; //if we have to move right then we don't want to ever go farther left than we have previously been
            
            countDown++;
            countUp=0;
            if(countDown>3){ //bomb is still in the same direction as before last movement so move more aggressively
                interval = 65*(D_lim - start_y)/100;                
            }else{
                interval = (D_lim - start_y)/2;
            }
            if(interval == 0){ //ensure progress is being made
                interval = 1;
            }
        }else if(direction[i]=='U'){
            D_lim = start_y; //if we have to move left then we don't want to ever go farther right than we have previously been
            
            countUp++;
            countDown=0;
            if(countUp>3){ //bomb is still in the same direction as before last movement so move more aggressively
                interval = -65*(start_y - U_lim)/100;
            }else{
                interval = -1*(start_y - U_lim)/2;
            }
            if(interval == 0){ //ensure progress is being made
                interval = -1;
            }
        }else if(direction[i]=='L'){
            countRight=0; //we will add to countLeft in findNextX but we know we aren't going right again so zeroize it
        }else if(direction[i]=='R'){
            countLeft=0; //we will add to countRight in findNextX but we know we aren't going left again so zeroize it
        }
    }
    
    return start_y+interval;
}

string tryNextWindow(int& x, int& y, int& L_lim, int& R_lim, int& U_lim, int& D_lim, const string direction){
    x=findNextX(x, L_lim, R_lim, direction);
    y=findNextY(y, U_lim, D_lim, direction);
    
    string answer = SSTR(x) + " " + SSTR(y);
    return answer;
}
 
int main(){
    int W; // width of the building.
    int H; // height of the building. (0,0 = top left of building, W,H = bottom right of building)
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0; //starting and current horizontal position of batman
    int Y0; //starting and current vertical position of batman
    cin >> X0 >> Y0; cin.ignore();
    
    //allow us to better track intervals, keep track of previous limits on the position of batman
    int U_lim = 0;
    int D_lim = H;
    int L_lim = 0;
    int R_lim = W;

    // game loop
    while (1) {
        string bombDir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bombDir; cin.ignore();

        string answer = tryNextWindow(X0, Y0, L_lim, R_lim, U_lim, D_lim,bombDir);
        //tryNextWindow(X0, Y0, prev_x, prev_y, W, H,bombDir);

        // the location of the next window Batman should jump to (X,Y) - "x y"
        cout << answer << endl;
    }
}