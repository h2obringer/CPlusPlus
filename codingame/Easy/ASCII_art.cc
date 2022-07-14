/*Author: Randal Obringer
* Date Last Modified: 8/15/2016
* 
* Difficulty: Easy
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: Produce ASCII art!
*
* Rules:
*	ASCII art allows you to represent forms by using characters. To be precise, in our case, these forms 
*	are words. For example, the word "MANHATTAN" could be displayed as follows in ASCII art:
* 
*	# #  #  ### # #  #  ### ###  #  ###
*	### # # # # # # # #  #   #  # # # #
*	### ### # # ### ###  #   #  ### # #
*	# # # # # # # # # #  #   #  # # # #
*	# # # # # # # # # #  #   #  # # # #
*
​*	Your mission is to write a program that can display a line of text in ASCII art in a style you are 
*	given as input.
*
* Input:
*	Line 1: the width L of a letter represented in ASCII art. All letters are the same width.
*	Line 2: the height H of a letter represented in ASCII art. All letters are the same height.
*	Line 3: The line of text T, composed of N ASCII characters.
*	Following lines: the string of characters ABCDEFGHIJKLMNOPQRSTUVWXYZ? Represented in ASCII art.
*
* Output: 
*	The text T in ASCII art.
*	The characters a to z are shown in ASCII art by their equivalent in upper case.
*	The characters that are not in the intervals [a-z] or [A-Z] will be shown as a question mark in ASCII art.
*
* Constraints:
*	0 < L < 30
*	0 < H < 30
*	0 < N < 200
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//read a character. convert it to a 1-26 (26 characters) or ? for non a-z characters. account between upper and lower
int toIndex(char convertMe){
    if(convertMe>='A'&&convertMe<='Z'){
        return convertMe-65; //return 1-26
    }else if(convertMe>='a'&&convertMe<='z'){
        return convertMe-97; //return 1-26
    }else{
        return 26; //27 characters in our ASCII alphabet set (0-26)
    }
}

string ToAsciiArt(string& message, vector<string>& alphabet, int height, int width){
    string answer = "";
    for(int i=0;i<height;i++){
        for(int j=0;j<message.length();j++){
            //append each row of corresponding letter of the message to answer
            for(int k=0;k<width;k++){
                //use alphabet at height i and letter 'index' for the duration of its width k
                answer+=alphabet[i][width*toIndex(message[j])+k]; //should append only 1 character at a time
                
                //in depth explanation: alphabet stores entire rows of the ascii alphabet so i will iterate 
                //through each row it contains because it is the height of each character. width*toIndex(message[j]) 
                //references the first character of the ascii art row for the current letter in the message we want to 
                //display. +k iterateres the entire row for that same message character.
            }
        }
        answer+='\n'; //we have built one row of our message. onto the next row.
    }
    return answer; //should return the entire answer;
}

int main(){
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T; //input message
    getline(cin, T);
    
    vector<string> alphabet;
    
    //read in the ASCII art alphabet
    for (int i = 0; i < H; i++) {
        string ROW;
        getline(cin, ROW);
        alphabet.push_back(ROW);
    }

    cout << ToAsciiArt(T, alphabet, H, L) << endl;  
    
}