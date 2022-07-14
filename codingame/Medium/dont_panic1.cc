/*Author: Randal Obringer
*
* Date Last Modified: 21 August 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: You need to help Marvin and his clones (or is it the 
*	other way round?) reach the exit in order to help them escape the 
*	inside of the Infinite Improbability Drive. 
*
* Rules: The drive has a rectangular shape of variable size. It is composed 
*	of several floors (0 = lower floor) and each floor has several possible 
*	positions that the clones can occupy (0 = leftmost position, width - 1 
*	= rightmost position).
*
*	The goal is to save at least one clone in a limited amount of rounds.
*	The details:
*		Clones appear from a unique generator at regular intervals, every 
*			three game turns. The generator is located on floor 0. Clones 
*			exit the generator heading towards the right.
*		Clones move one position per turn in a straight line, moving in 
*			their current direction.
*		A clone is destroyed by a laser if it is goes below position 0 or 
*			beyond position width - 1.
*		Elevators are scattered throughout the drive and can be used to 
*			move from one floor to the one above. When a clone arrives on 
*			the location of an elevator, it moves up one floor. Moving up 
*			one floor takes one game turn. On the next turn, the clone 
*			continues to move in the direction it had before moving upward.
*		On each game turn you can either block the leading clone - meaning 
*			the one that got out the earliest - or do nothing.
*		Once a clone is blocked, you can no longer act on it. The next clone
*			in line takes the role of "leading clone" and can be blocked at 
*			a later time.
*		When a clone moves towards a blocked clone, it changes direction 
*			from left to right or right to left. It also changes direction 
*			when getting out of the generator directly on a blocked clone 
*			or when going up an elevator onto a blocked clone.
*		If a clone is blocked in front of an elevator, the elevator can no 
*			longer be used.
*		When a clone reaches the location of the exit, it is saved and 
*			disappears from the area.
* Victory Conditions: You win if at least one clone reaches the exit location 
*	in a limited amount of game rounds.
*
* Game Input:
*	The program must first read the initialization data from standard input. 
*	Then, within an infinite loop, read the contextual data (location of 
*	leading clone) from the standard input and provide the next instruction 
*	to standard output.
*
*	Initialization input:
*		Line 1: 8 integers:
*			nbFloors : number of floors in the area. A clone can move between 
*				floor 0 and floor nbFloors - 1
*			width : the width of the area. The clone can move without being 
*				destroyed between position 0 and position width - 1
*			nbRounds : maximum number of rounds before the end of the game
*			exitFloor : the floor on which the exit is located
*			exitPos : the position of the exit on its floor
*			nbTotalClones : the number of clones that will come out of the 
*				generator during the game
*			nbAdditionalElevators : not used for this first question, value is 
*				always 0
*			nbElevators : number of elevators in the area
*		(nbElevators) next lines: 2 integers elevatorFloor elevatorPos providing the floor and position of an elevator.
*
*	Input for one game turn:
*		Line 1: 2 integers cloneFloor clonePos and one string direction. 
*		cloneFloor and clonePos are the coordinates of the leading unblocked
*		clone. direction indicates the current direction of the leading clone:
*			LEFT the clone is moving towards the left
*			RIGHT the clone moving towards the right
*		If there is no leading clone, the line values are: -1 -1 NONE. This 
*		can happen only when the clones which are already outside are all 
*		blocked and the next clone is not out yet. In this case, you may 
*		output action WAIT.
* 
* Output for one game turn:
*	A single line (including newline character) to indicate which action to 
*	take:
*		Either the keyword WAIT to do nothing.
*		or the keyword BLOCK to block the leading clone.
*
* Constraints:
*	1 ≤ nbFloors ≤ 15
*	5 ≤ width ≤ 100
*	10 ≤ nbRounds ≤ 200
*	0 ≤ exitFloor, elevatorFloor < nbFloors
*	0 ≤ exitPos , elevatorPos < width
*	-1 ≤ cloneFloor < nbFloors
*	-1 ≤ clonePos < width
*	2 ≤ nbTotalClones ≤ 50
*	0 ≤ nbElevators ≤ 100
*	Duration of one game turn: 100 ms
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

//sorts both arrays
void quickSort(int arr[], int arr2[], int left, int right) {
    int i = left, j = right;
    int temp;
    int temp2;
    int pivot = arr[(left + right) / 2];

    /* partition */
    while (i <= j) {
        while (arr[i] < pivot){
            i++;
        }
        while (arr[j] > pivot){
            j--;
        }

        if (i <= j) {
            temp = arr[i];
            temp2 = arr2[i];
            arr[i] = arr[j];
            arr2[i] = arr2[j];
            arr[j] = temp;
            arr2[j] = temp2;
            i++;
            j--;
        }
    };

    /* recursion */
    if (left < j){
        quickSort(arr, arr2, left, j);
    }
    if (i < right){
        quickSort(arr, arr2, i, right);
    }
}

int main(){
    int nbFloors; // number of floors. 0 is lowest floor
    int width; // width of the area. 0 is leftmost. width-1 is rightmost.
    int nbRounds; // maximum number of rounds
    int exitFloor; // floor on which the exit is found
    int exitPos; // position of the exit on its floor
    int nbTotalClones; // number of generated clones
    int nbAdditionalElevators; // ignore (always zero)
    int nbElevators; // number of elevators
    cin >> nbFloors >> width >> nbRounds >> exitFloor >> exitPos >> nbTotalClones >> nbAdditionalElevators >> nbElevators; cin.ignore();
    
    int currentElevator=0; //keep track of which elevator is next through the game loop
    int elevatorsFloor[nbElevators]; //hold elevator floor data
    int elevatorsPos[nbElevators]; //hold elevator position data
    
    for (int i = 0; i < nbElevators; i++) {
        int elevatorFloor; // floor on which this elevator is found
        int elevatorPos; // position of the elevator on its floor
        cin >> elevatorFloor >> elevatorPos; cin.ignore();
        
        //cerr << "Elevator floor: " << elevatorFloor << ", Elevator position: " << elevatorPos << endl;
        elevatorsFloor[i]=elevatorFloor;
        elevatorsPos[i]=elevatorPos;
    }
    quickSort(elevatorsFloor, elevatorsPos,0,nbElevators-1); //hold elevators floors from lowest to highest, sort the positions based on floors
    
    //DEBUG
    /*for(int i=0;i<nbElevators;i++){
        cerr << "elevatorsFloor[" << i << "] is " << elevatorsFloor[i] << endl;
        cerr << "elevatorsPos[" << i << "] is " << elevatorsPos[i] << endl;
    }*/

    // game loop
    while (1) {
        int cloneFloor; // floor of the leading clone
        int clonePos; // position of the leading clone on its floor
        string direction; // direction of the leading clone: LEFT or RIGHT
        cin >> cloneFloor >> clonePos >> direction; cin.ignore();
        //if first elevator is to left of generator
        if((cloneFloor==0)&&(nbElevators>0)&&(elevatorsPos[0]<clonePos)){ 
            if(direction[0]=='R'){ //and if clone is traveling right
                cout << "BLOCK" << endl; //turn it around to head to elevator
            }else{
                cout << "WAIT" << endl; //otherwise keep heading to the elevator
            }
        }else if(exitFloor==0){ //if there is only one floor
            if(exitPos<clonePos){ //and the exit is to the left of the clone
                if(direction[0]=='R'){ //and the clone is traveling right
                    cout << "BLOCK" << endl; //turn it around to head to exit
                }else{
                    cout << "WAIT" << endl; //otherwise keep heading to exit
                }
            }else{ //otherwise exit is to right of clone and it is already going right so keep heading to the exit
                cout << "WAIT" << endl;
            }
        }else if(cloneFloor==exitFloor){ //if clone is on exit floor
            if(clonePos==elevatorsPos[currentElevator]){ //and the clone is at position of last elevator
                if(exitPos>clonePos){ //and the exit is to the right of clone
                    if(direction[0]=='L'){ //and the clone is going left
                        cout << "BLOCK" << endl; //turn it around to head to the exit
                    }else{
                        cout << "WAIT" << endl; //otherwise keep heading to the exit
                    }
                }else{ //and the exit is to the left of clone
                    if(direction[0]=='L'){ //then keep heading to the exit
                        cout << "WAIT" << endl;
                    }else{ //otherwise turn it around to head to exit
                        cout << "BLOCK" << endl;
                    }
                }
            }else{ //otherwise keep going
                cout << "WAIT" << endl;
            }
        }else if(clonePos==elevatorsPos[currentElevator]){ //if clone is at elevator
            if(cloneFloor==elevatorsFloor[currentElevator]+1){ //and clone has gone up the elevator
                if(nbElevators>currentElevator+1){ //and there is another elevator
                    if(elevatorsPos[currentElevator+1]>clonePos){ //and that next elevator is to the right of clone
                        if(direction[0]=='L'){ //and clone is going opposite direction of it then turn it around
                            cout << "BLOCK" << endl;
                        }else{
                            cout << "WAIT" << endl;
                        }
                    }else{ //if elevator is to the left of clone
                        if(direction[0]=='L'){
                            cout << "WAIT" << endl;
                        }else{ //and clone is going opposite direction of it then turn it around
                            cout << "BLOCK" << endl;
                        }
                    }
                }
                currentElevator++; //keep track of which elevator we care about. Executes after we have already gone up the elevator
            }else{
                cout << "WAIT" << endl;
            }
        }else if(clonePos == width-1){
            cout << "BLOCK" << endl;
        }else if(clonePos ==0){
            cout << "BLOCK" << endl;
        }else{
            cout << "WAIT" << endl; // action: WAIT or BLOCK
        }
    }
}