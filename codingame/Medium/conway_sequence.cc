/*Author: Randal Obringer
*
* Date Last Modified: 2 November 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Description: use an array of vector<int> to build the sequence. Keep track of our current position,
*	record the current # and # of occurrences before logging it in the vector for that line.
*
* Problem Statement: You mission is to print a specific line of the Conway sequence. 
*
* Rules: Warning! This sequence can make you ill. The reasoning is simple but unusual: Read a line
*	aloud whilst looking at the line above and you will notice that each line (except the first) 
*	makes ​​an inventory of the previous line.
*
*	     1			Line 3 shows 2 1 because the line 2 contains two 1, one after the other.
*		1 1			Line 4 displays 1 2 1 1 because the line 3 contains one 2 followed by one 1.
*		2 1			Line 5 displays 1 1 1 2 2 1 because the line 4 contains one 1 followed by one 2
*	  1 2 1 1			followed by two 1.
*	1 1 1 2 2 1
*	3 1 2 2 1 1 
*       ...
*
*	This sequence refers to a technique used to encode ranges in order to compress identical 
*	values ​​without losing any information. This type of method is used, amongst others, to 
*	compress images. Your mission is to write a program that will display the line L of this 
*	series on the basis of an original number R (R equals 1 in our example).
*
* Input: 
*	Line 1: The original number R of the sequence.
*	Line 2: The line L to display. The index of the first line is 1.
*
* Output: The line L of the sequence. Each element of the sequence is separated by a space.
*
* Constraints: 
*	0 < R < 100
*	0 < L ≤ 25
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main(){
    int R; //line 1 of the conway sequence. the original number.
    cin >> R; cin.ignore();
    int L; //the line to output as the answer
    cin >> L; cin.ignore();
    
    vector<int> conway[L]; //hold all lines of the conway sequence that we care about (up to line L)
    conway[0].push_back(R); //push line 1 onto the sequence
    
    //cerr << "The size of line 1 is: " << conway[0].size() << endl;
    
    //build the conway sequence in order, start at line 2 because we are given line 1
    for(int i=1;i<L;i++){
        int index=0;
        //for the length of the previous line
        while(index<conway[i-1].size()){
            int current = conway[i-1][index]; //log the current # seen on previous line
            int current_count = 0; //log # of occurrences in a row for this current #
            //begin counting how many times we see this current number
            while((index<conway[i-1].size())&&(conway[i-1][index]==current)){
                current_count++;
                index++;
            }
            //add the # of occurrences followed by the number to the current line we are building
            conway[i].push_back(current_count);
            conway[i].push_back(current);
        }
    }
    
    string answer="";
    for(int i=0;i<conway[L-1].size();i++){
        answer += to_string(conway[L-1][i]); //c++11 call
        if(i!=conway[L-1].size()-1){ //if not the last # on this sequence line
            answer+=" ";
        }
    }
    
    /*cerr << "Printing the conway sequence: " << endl;
    for(int i=0;i<L;i++){
        cerr << "Printing line " << i+1 << endl;
        for(vector<int>::iterator it=conway[i].begin();it!=conway[i].end();++it){
            cerr << *it << " ";  
        }
        cerr << endl;
    }*/

    cout << answer << endl;
}