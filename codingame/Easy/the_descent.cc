/*Author: Randal Obringer
* Date Last Modified: 10/29/2016
* 
* Difficulty: Easy
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: Destroy the mountains before your starship collides with one of them. For that, 
*	shoot the highest mountain on your path.
*
* Rules:
*	At the start of each game turn, you are given the height of the 8 mountains from left to right.
*	By the end of the game turn, you must fire on the highest mountain by outputting its index (from 0 to 7).
*	Firing on a mountain will only destroy part of it, reducing its height. Your ship descends after each pass.  

* Victory Conditions: You win if you destroy every mountain
* Lost Conditions:
*	Your ship crashes into a mountain
*	You provide incorrect output or your program times out
*
* Game Input: Within an infinite loop, read the heights of the mountains from the standard input and print to the standard output the index of the mountain to shoot.
* Input for one game turn: 8 lines: one integer mountainH per line. Each represents the height of one mountain given in the order of their index (from 0 to 7).
* Output for one game turn: A single line with one integer for the index of which mountain to shoot.
* Constraints: 
*	0 ≤ mountainH ≤ 9
*	Response time per turn ≤ 100ms
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main(){

    // game loop
    while (1) {
        int highest = INT_MIN; //hold height of highest mountain
        int index = 0; //hold index of highest mountain
        for (int i = 0; i < 8; i++) {
            int mountainH; // represents the height of one mountain.
            cin >> mountainH; cin.ignore();
            if(mountainH>highest){
                highest=mountainH;
                index = i;
            }
        }

        cout << index << endl; // The index of the mountain to fire on.
    }
}