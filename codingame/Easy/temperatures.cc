/*Author: Randal Obringer
* Date Last Modified: 8/15/2016
* 
* Difficulty: Easy
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: In this exercise, you have to analyze records of temperature to find the closest to zero.
*
* Rules: 
*	Write a program that prints the temperature closest to 0 among input data. If two numbers are equally 
*	close to zero, positive integer has to be considered closest to zero (for instance, if the temperatures 
*	are -5 and 5, then display 5).
*
* Input: 
*	Line 1: N, the number of temperatures to analyze
*	Line 2: A string with the N temperatures expressed as integers ranging from -273 to 5526
*
* Output: 
*	Display 0 (zero) if no temperatures are provided. Otherwise, display the temperature closest to 0.
*
* Constraints:
*	0 ≤ N < 10000
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

int main()
{
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    getline(cin, temps);
    
    //using istringstream instead of a personally developed function because problem constraints tell us what 
    //type of input we can expect. Although we should do more in depth error checking
    istringstream in; //parse for individual temperatures
    
    int closest=5527; //outside expected input values so all inputs will always be closer to 0 given the perameters of the program.
    int current; //keep track of current temperature value in the string
    in.str(temps);
    
    //cout << temps << endl; //debugging purposes
    if(n==0){
        cout << 0 << endl;
    }else{
        for(int i=0;i<n;i++){
            in >> current;
            if(abs(current)<abs(closest)){
                closest=current;
            }else if(abs(current)==abs(closest)){
                if(current>closest){
                    closest=current;
                }
            }
        }
        cout << closest << endl;
    }
}