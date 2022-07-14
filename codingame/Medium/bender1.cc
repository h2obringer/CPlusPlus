/*Author: Randal Obringer
*
* Date Last Modified: 2 November 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Description: 
*
* Problem Statement: Bender is a depressed robot who heals his depression by partying and 
*	drinking alcohol. To save him from a life of debauchery, his creators have reprogrammed 
*	the control system with a more rudimentary intelligence. Unfortunately, he has lost his 
*	sense of humor and his former friends have now rejected him. Bender is now all alone and 
*	is wandering through the streets of Futurama with the intention of ending it all in a 
*	suicide booth. To intercept him and save him from almost certain death, the authorities 
*	have given you a mission: write a program that will make it possible to foresee the path 
*	that Bender follows. To do so, you are given the logic for the new intelligence with which 
*	Bender has been programmed as well as a map of the city.
*
* Rules: The 9 rules of the new Bender system:
*	Bender starts from the place indicated by the @ symbol on the map and heads SOUTH.
*	Bender finishes his journey and dies when he reaches the suicide booth marked $.
*	Obstacles that Bender may encounter are represented by # or X.
*	When Bender encounters an obstacle, he changes direction using the following priorities: 
*		SOUTH, EAST, NORTH and WEST. So he first tries to go SOUTH, if he cannot, then he will 
*		go EAST, if he still cannot, then he will go NORTH, and finally if he still cannot, 
*		then he will go WEST.
*	Along the way, Bender may come across path modifiers that will instantaneously make him 
*		change direction. The S modifier will make him turn SOUTH from then on, E, to the EAST, 
*		N to the NORTH and W to the WEST.
*	The circuit inverters (I on map) produce a magnetic field which will reverse the direction 
*		priorities that Bender should choose when encountering an obstacle. Priorities will 
*		become WEST, NORTH, EAST, SOUTH. If Bender returns to an inverter I, then priorities 
*		are reset to their original state (SOUTH, EAST, NORTH, WEST).
*	Bender can also find a few beers along his path (B on the map) that will give him strength 
*		and put him in “Breaker” mode. Breaker mode allows Bender to destroy and automatically 
*		pass through the obstacles represented by the character X (only the obstacles X). When 
*		an obstacle is destroyed, it remains so permanently and Bender maintains his course of 
*		direction. If Bender is in Breaker mode and passes over a beer again, then he 
*		immediately goes out of Breaker mode. The beers remain in place after Bender has passed.
*	2 teleporters T may be present in the city. If Bender passes over a teleporter, then he is 
*		automatically teleported to the position of the other teleporter and he retains his 
*		direction and Breaker mode properties.
*	Finally, the space characters are blank areas on the map (no special behavior other than 
*		those specified above).
*
*	Your program must display the sequence of moves taken by Bender according to the map provided 
*	as input. The map is divided into lines (L) and columns (C). The contours of the map are 
*	always unbreakable # obstacles. The map always has a starting point @ and a suicide booth $.
*	If Bender cannot reach the suicide booth because he is indefinitely looping, then your 
*	program must only display LOOP.
*
* Example:		In this example, Bender will follow this sequence of moves:
*	######		-SOUTH (initial direction)
*	#@E $#		-EAST (because of the obstacle X)
*	# N  #		-NORTH (change of direction caused by N)
*	#X   #		-EAST (change of direction caused by E)
*	######		-EAST (currect direction, until end point $)
*
* Input: 
*	Line 1: the number of lines L and columns C on the map, separated by a space.
*	The following L lines: a line of the length C representing a line on the map. A line can 
*		contain the characters #, X, @, $, S, E, N, W, B, I, T and space character.
*
* Output: 
*	If Bender can reach $, then display the sequence of moves he has taken. One move per line: 
*		SOUTH for the South, EAST for the East, NORTH for the North and WEST for the west.
*	If Bender cannot reach $, then only display LOOP.
*
* Constraints:
*	4 ≤ C ≤ 100
*	4 ≤ L ≤ 100
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//GLOBAL VARIABLES
const bool DEBUG = true;

char direction='s'; //bender's current direction - default to south
int L; //# of rows in the map
int C; //# of columns in the map

string* the_map; //make global so we can make functions. intialize later
int **visits; //2D array to store # of times bender has walked over the same path. Used to identify loops.
vector<string> move_log; //hold all the moves of bender

bool inverted=false; //circuits currently inverted?
bool breaker_mode=false; //currently in breaker mode?
bool loop=false; //is bender in an indefinite loop?
bool barrier=false; //is there a barrier in the way?

int current_x=-1; //hold bender's current x coordinate in the map
int current_y=-1; //hold bender's current y coordinate in the map

int peek_x=-1; //look at the next x direction on the map so we can make decisions
int peek_y=-1; //look at the next y direction on the map so we can make decisions

int try_direction=0; //holds current index for the direction priority arrays below, allows us to iterate through the directions
char direction_list[] = {'s','e','n','w'}; //hold the highest priority directions in the lower indices
char reversed_list[] = {'w','n','e','s'}; //hold the highest priority direction in lower indices for when inverted==true

int teleport_x[2]; //hold x coordinates of teleporters
int teleport_y[2]; //hold y coordinates of teleporters
int teleport_count=0; //# of currently logged teleporters

//check the visit information for current location, identify a loop when bender has been there x times
// although unlikely, it is possible to go over the same location just approach from different directions
// which could yield different results and therefore shouldn't be considered a loop. Set the visits limit
// modestly to account for these
void check_for_loop(){
    if(visits[current_y][current_x]>6){
        loop=true;
    }
}

//After bender moves he is on a new map coordinate. Process any special cases here.
void new_location_action(){
    //moving onto the new location for the first time
    //if bender is in the middle of choosing a new direction because of a barrier then we 
    //don't want to trip anything multiple times while bender is deciding
    if(barrier==false){
        //bender is located at a new location so update the visit information
        visits[current_y][current_x]++;
        check_for_loop();
        
        switch(the_map[current_y][current_x]){
            case 'S': //south manipulator
                direction='s';
                break;
            case 'E': //east manipulator
                direction='e';
                break;
            case 'N': //north manipulator
                direction='n';
                break;
            case 'W': //west manipulator
                direction='w';
                break;
            case 'B': //beer
                breaker_mode = !breaker_mode;
				if(DEBUG){
					if(breaker_mode){
						cerr << "breaker_mode was activated!" << endl;
					}else{
						cerr << "breaker_mode was deactiviated" << endl;
					}
				}
                break;
            case 'I': //inverter
                inverted = !inverted;
				if(DEBUG){
					if(inverted){
						cerr << "inversion activated" << endl;
					}else{
						cerr << "inversion deactivated" << endl;
					}
				}
                break;
            case 'T': //teleporters
                //bender is at teleporter[0] so move to the other teleporter location
                if((teleport_x[0]==current_x)&&(teleport_y[0]==current_y)){
                    current_x=teleport_x[1];
                    current_y=teleport_y[1];
                //bender is at teleporter[1] so move to the other teleporter location
                }else{
                    current_x=teleport_x[0];
                    current_y=teleport_y[0];
                }
                //bender has teleported and therefore at a new location so log the visit there
                visits[current_y][current_x]++;
				if(DEBUG) cerr << "TELEPORTED!" << endl;
                break;
            default:
                //do nothing
                break;
        }
    }
}

//Log the actions that were decided to store the answer
void log_action(){
    //direction will not need to be changed
    switch(direction){
        case 's':
            move_log.push_back("SOUTH");
            if(DEBUG) cerr << "Logged south" << endl;
            break;
        case 'e':
            move_log.push_back("EAST");
            if(DEBUG) cerr << "Logged east" << endl;
            break;
        case 'n':
            move_log.push_back("NORTH");
            if(DEBUG) cerr << "Logged north" << endl;
            break;
        case 'w':
            move_log.push_back("WEST");
            if(DEBUG) cerr << "Logged west" << endl;
            break;
    }
}

//given the current direction of travel, compute the next map coordinate
void compute_ahead(){
    //set the conditions to look ahead in current direction
    switch(direction){ 
        case 's':
            peek_x=current_x;
            peek_y=current_y+1;
            break;
        case 'e':
            peek_x=current_x+1;
            peek_y=current_y;
            break;
        case 'n':
            peek_x=current_x;
            peek_y=current_y-1;
            break;
        case 'w':
            peek_x=current_x-1;
            peek_y=current_y;
            break;
    }
    
    if(DEBUG) cerr << "\'" << the_map[peek_y][peek_x] << "\' is in front of bender" << endl;
}

//execute the move, log the action, reset key variables so bender can make the next decision
void move(){
    current_x=peek_x;
    current_y=peek_y;
    try_direction=0; //reset the priority chain
    barrier=false;
    log_action();
}

//A barrier is in the way so we need to choose the next direction to go in
void choose_direction(){
    barrier=true;
    if(inverted){ //priorities will be reversed
        direction = reversed_list[try_direction];
    }else{
        direction = direction_list[try_direction];
    }
    try_direction++; //if we make it back here again we can try another direction
    
    if(DEBUG) cerr << "There is a barrier in the way. Trying: "<< direction << endl;
	
    //if we have tried all directions bender is stuck and there is a loop
    //this really should never happen though
    if(try_direction==4){
        loop=true;
		if(DEBUG) cerr << "Bender is stuck which caused a loop" << endl;
    }
}

//look at where the next move would put bender. If the move is safe then move, if there is a barrier then choose other directions
void look_ahead(){
    //look ahead in current direction
    switch(the_map[peek_y][peek_x]){
        //unbreakable barrier
        case '#':
            //choose prioritized directions
            choose_direction(); //iterate back through main while loop, if we end back up here we will choose another direction
            break;
        //breakable barrier
        case 'X':
            //if bender has had beer then he can break the barrier
            if(breaker_mode==true){
                //break the X barrier and remove it
                the_map[peek_y][peek_x]=' ';
                if(DEBUG) cerr << "Broke the barrier!" << endl;
                //move bender to his next location on the map
                move();
            }else{
                //choose prioritized directions
                choose_direction(); //iterate back through main while loop, if we end back up here we will choose another direction
            }
            break;
        default:
            //move bender to his next location on the map
            move();
            break;
    }
}

//find and log bender's start position and the teleporter positions
//the_map array and visits array must be initialized before calling this function
void find_things(){
    if(DEBUG) cerr << "The map: " << endl;
    for(int i=0;i<L;i++){ //for all rows (y)
        for(int j=0;j<C;j++){ //for all columns (x)
            if(the_map[i][j]=='@'){ //bender starts on '@'
                current_x=j; //log starting x coordinate
                current_y=i; //log starting y coordinate
                visits[i][j]++;
            }else if(the_map[i][j]=='T'){ //teleporter
                //log the teleporter coordinates
                teleport_x[teleport_count]=j;
                teleport_y[teleport_count]=i;
                teleport_count++; //keep track of the array index we will fill next
            }
        }
        if(DEBUG) cerr << the_map[i] << endl;
    }
    if(DEBUG) cerr << "Bender's starting coordinates are: " << current_x << "," << current_y << endl;
}

int main(){
    cin >> L >> C; cin.ignore();
    the_map = new string[L]; //holds the map
    
    //initialize the visits array so we can later identify loops
    visits = new int*[L];
    for(int i=0;i<L;i++){ //for each row (y)
        visits[i] = new int[C];
        for(int j=0;j<C;j++){ //for each column (x)
            visits[i][j]=0; //bender hasn't been anywhere yet
        }
    }
    
    //initialize the map
    for (int i = 0; i < L; i++) {
        string row;
        getline(cin, row);
        the_map[i]=row; 
    }
    
    //locate bender's start position and the teleporters
    find_things();
    
    //end the loop when bender has reached the suicide booth ($) or a loop in bender's path has been identified
    while((the_map[current_y][current_x]!='$')&&(loop==false)){
        //handle new location special states
        new_location_action();
        //get our peek values
        compute_ahead();
        look_ahead();
    }
    
    //output the answer
    if(loop){
        cout << "LOOP" << endl;
    }else{
        for(int i=0;i<move_log.size();i++){
            cout << move_log[i] << endl;
        }
    }
}