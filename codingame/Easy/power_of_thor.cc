/*Author: Randal Obringer
* Date Last Modified: 8/15/2016
* 
* Difficulty: Easy
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: Your program must allow Thor to reach the light of power.
*
* Rules: 
*	Thor moves on a map which is 40 wide by 18 high. Note that the coordinates (X and Y) start at the top left! 
*	This means the most top left cell has the coordinates "X=0,Y=0" and the most bottom right one has the 
*	coordinates "X=39,Y=17".
*
* Input: 
*	lightX: the X position of the light of power that Thor must reach.
*   lightY: the Y position of the light of power that Thor must reach.
*   initialTX: the starting X position of Thor.
*   initialTY: the starting Y position of Thor.
* Input for a game round:
*	Line 1: the number of remaining moves for Thor to reach the light of power: remainingTurns. You can ignore
*	this data but you must read it.
*
* Output: At the end of the game turn, you must output the direction in which you want Thor to go among: 
*	N = North
*	NE = North-East
*	E = East
*	SE = South-East
*	S = South
*	SW = South-West
*	W = West
*	NW = North-West
*	Each movement makes Thor move by 1 cell in the chosen direction.
*
* Victory Conditions: You win when Thor reaches the light of power.
* Lost Conditions: Thor moves outside the map.
*
* Constraints:
*	0 ≤ lightX < 40
*	0 ≤ lightY < 18
*	0 ≤ initialTX < 40
*	0 ≤ initialTY < 18
*	Response time for a game round ≤ 100ms
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int lightX; // the X position of the light of power
    int lightY; // the Y position of the light of power
    int initialTX; // Thor's starting X position
    int initialTY; // Thor's starting Y position
    int thorX;
    int thorY;
    int dx;
    int dy;
    cin >> lightX >> lightY >> initialTX >> initialTY; cin.ignore();
    thorX=initialTX;
    thorY=initialTY;
    string directionX="";
    string directionY="";

    // game loop
    while (1) {
        int remainingTurns; // The remaining amount of turns Thor can move. Do not remove this line.
        cin >> remainingTurns; cin.ignore();
        
        //solve x direction
        if(thorX<lightX){
            thorX+=1;
            directionX="E";
        }else if(thorX>lightX){
            thorX-=1;
            directionX="W";
        }else{
            directionX="";
        }
        //solve y direction
        if(thorY<lightY){
            thorY+=1;
            directionY="S";
        }else if(thorY>lightY){
            thorY-=1;
            directionY="N";
        }else{
            directionY="";
        }
        
        cout << directionY << directionX << endl;

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        //cout << "SE" << endl; // A single line providing the move to be made: N NE E SE S SW W or NW
    }
}