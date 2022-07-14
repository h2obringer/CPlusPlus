/*Author: Randal Obringer
*
* Date Last Modified: 25 August 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Description: Read input to build a map of the layout. Determine next location based on current tile
*	in map as well as direction we previously came from. Reach the exit of the map.
*
* Problem Statement: Your objective is to write a program capable of 
*	predicting the route Indy will take on his way down a tunnel. Indy is 
*	not in danger of getting trapped in this first mission.
*
* Rules: The tunnel consists of a patchwork of square rooms of different 
*	types.The rooms can be accessed and activated by computer using an 
*	ancient RS232 serial port (because Mayans aren't very technologically
*	advanced, as is to be expected...). There is a total of 14 room types 
*	(6 base shapes extended to 14 through rotations). Upon entering a room, 
*	depending on the type of the room and Indy's entrance point (TOP,LEFT, 
*	or RIGHT) he will either exit the room through a specific exit point, 
*	suffer a lethal collision or lose momentum and get stuck: 
*	
*	Type 0: This room type is not part of the tunnel per se as Indy cannot move across it.
*	Type 1: Enter from left, right, or top; exit from bottom
*	Type 2: Enter from left and exit from right, or enter from right and exit from left.
*	Type 3: Enter from top and exit from bottom.
*	Type 4: Enter from top and exit from left, or enter from right and exit from bottom.
*	Type 5: Enter from top and exit from right, or enter from left and exit from bottom.
*	Type 6: Enter from top is failure, or enter from left and exit from right, or 
*		enter from right and exit from left.
*	Type 7: Enter from top or right and exit from bottom.
*	Type 8: Enter from left or right and exit from bottom.
*	Type 9: Enter from top or left and exit from bottom.
*	Type 10: Enter from top and exit from left.
*	Type 11: Enter from top and exit from right.
*	Type 12: Enter from right and exit from bottom.
*	Type 13: Enter from left and exit from bottom.
*
*	Indy is perpetually drawn downwards: he cannot leave a room through the 
*	top. At the start of the game, you are given the map of the tunnel in 
*	the form of a rectangular grid of rooms. Each room is represented by 
*	its type. For this first mission, you will familiarize yourself with 
*	the tunnel system, the rooms have all been arranged in such a way that 
*	Indy will have a safe continuous route between his starting point (top 
*	of the temple) and the exit area (bottom of the temple).
*
* 	Each game turn: 
*		You receive Indy's current position
*		Then you specify what Indy's position will be next turn.
*		Indy will then move from the current room to the next according to the 
*			shape of the current room.
*
* Victory Conditions: Indy reaches the exit.
*
* Lost Conditions: You assert an incorrect position for Indy.
*
* Game Input: 
*	Initialization Input: 
*		Line 1: 2 space separated integers W H specifying the width and 
*			height of the grid.
*		Next H lines: each line represents a line in the grid and contains 
*			W space separated integers T. T specifies the type of the room.
*		Last line: 1 integer EX specifying the coordinate along the X axis
*			of the exit (this data is not useful for this first mission, it 
*			will be useful for the second level of this puzzle).
*	Input for one game turn: 
*		Line 1: XI YI POS -(XI, YI) two integers to indicate Indy's current 
*			position on the grid. POS a single word indicating Indy's 
*			entrance point into the current room: TOP if Indy enters from 
*			above, LEFT if Indy enters from the left and RIGHT if Indy 
*			enters from the right.
*
* Output for one game turn:
*	A single line with 2 integers: X Y representing the (X, Y) coordinates 
*	of the room in which you believe Indy will be on the next turn.
*
* Constraints:
*	0 < W ≤ 20
*	0 < H ≤ 20
*	0 ≤ T ≤ 13
*	0 ≤ EX < W
*	0 ≤ XI, X < W
*	0 ≤ YI, Y < H
*	Response time for one game ≤ 150ms
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main(){
    int W; // number of columns.
    int H; // number of rows.
    cin >> W >> H; cin.ignore();
    int maze[W][H]; //store all the data for the map
    for (int i = 0; i < H; i++) {
        string LINE; // represents a line in the grid and contains W integers. Each integer represents one room of a given type.
        getline(cin, LINE);
        
        istringstream is(LINE); //create stream
        for(int j = 0; j < W; j++){
            is >> maze[j][i]; //directly pull and assign data from the stream into the map
        }
    }
    int EX; // the coordinate along the X axis of the exit (not useful for this first mission, but must be read). NOT USED
    cin >> EX; cin.ignore();
    
    // game loop
    while (1) {
        int XI;
        int YI;
        string POS;
        cin >> XI >> YI >> POS; cin.ignore();
        cerr << "Position is: " << POS << endl; //tells us which direction we came from to make an accurate decision
        
        switch(maze[XI][YI]){
            case 1:
            case 3:
            case 7:
            case 8:
            case 9:
            case 12:
            case 13:
                YI++;
                break;
            case 2:
            case 6:
                if(POS[0]=='L'){
                    XI++;
                }else if(POS[0]=='R'){
                    XI--;
                }
                break;
            case 4:
                if(POS[0]=='T'){
                    XI--;
                }else if(POS[0]=='R'){
                    YI++;
                }
                break;
            case 5:
                if(POS[0]=='T'){
                    XI++;
                }else if(POS[0]=='L'){
                    YI++;
                }
                break;
            case 10:
                XI--;
                break;
            case 11:
                XI++;
                break;
            default:
                break;
        }

        // One line containing the X Y coordinates of the room in which you believe Indy will be on the next turn.
        cout << XI << " " << YI << endl;
    }
}