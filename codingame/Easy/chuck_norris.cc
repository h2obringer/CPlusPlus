/*Author: Randal Obringer
* Date Last Modified: 8/15/2016
* 
* Difficulty: Easy
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: 
*	Binary with 0 and 1 is good, but binary with only 0, or almost, is even better! Originally, this 
*	is a concept designed by Chuck Norris to send so called unary messages. Write a program that takes 
*	an incoming message as input and displays as output the message encoded using Chuck Norris’ method.
*
* Rules: Here is the encoding principle:
*   The input message consists of ASCII characters (7-bit)
*   The encoded output message consists of blocks of 0
*   A block is separated from another block by a space
*   Two consecutive blocks are used to produce a series of same value bits (only 1 or 0 values):
*  		- First block: it is always 0 or 00. If it is 0, then the series contains 1, if not, it contains 0
*	  	- Second block: the number of 0 in this block is the number of bits in the series
*
* Example:
*	Let’s take a simple example with a message which consists of only one character: Capital C. C in binary is represented as 1000011, so with Chuck Norris’ technique this gives:
*
*   0 0 (the first series consists of only a single 1)
*   00 0000 (the second series consists of four 0)
*   0 00 (the third consists of two 1)
*
*	So C is coded as: 0 0 00 0000 0 00
*
*	Second example, we want to encode the message CC (i.e. the 14 bits 10000111000011) :
*
*   0 0 (one single 1)
*   00 0000 (four 0)
*   0 000 (three 1)
*   00 0000 (four 0)
*   0 00 (two 1)
*
*	So CC is coded as: 0 0 00 0000 0 000 00 0000 0 00
*
* Input:
*	Line 1: the message consisting of N ASCII characters (without carriage return)
*
* Output:
*	The encoded message
*
* Constraints:
*	0 < N < 100
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


//helper function: used as an intermediary conversion from a char to a binary string representation
string CharToBinary(unsigned int value){
    unsigned int mask = 1 << 6; //bitwise shift left 6 times, masks the most significant bit in a char with 7 bits
    string answer = "";
    
    for(int i = 0; i < 7; i++){ //7 digits in the binary answer
        if((value & mask)==0){
            answer=answer+"0";
        }else{
            answer=answer+"1";
        }
        mask  >>= 1; //shift right 1 (mask = mask >> 1)
    }
    
    return answer;
}


string BinaryToNorris(string& toConvert){    
    //convert raw string to a string of binary values of each character in the string
    string value="";
    for(int k=0;k<toConvert.length();k++){
        value+=CharToBinary(toConvert[k]);
    }
    
    //begin conversion to Norris code
    string answer = "";
    int i=0; //hold entire
    int seriesSize;
    
    while(i<value.length()){
        if(value[i]=='1'){
            answer+="0 "; //1 (1st in the pair)
            seriesSize=0;
            do{ //build up # of 1s in this series (second in the pair)
                seriesSize++; 
                i++;
            }while((value[i]=='1')&&(i<value.length())); //stop if current char !="1" or if at end of string
        }else{
            answer+="00 "; //0 (1st in the pair)
            seriesSize=0;
            do{ //build up # of 0s in this series (second in the pair)
                seriesSize++;
                i++;
            }while((value[i]=='0')&&(i<value.length())); //stop if current char !="1" or if at end of string
        }
        
        for(int j=0;j<seriesSize;j++){ //second in the pair
            answer+="0";
        }
        
        //add a space, we are expecting another pair, otherwise we have reached the end of the string
        if(i!=value.length()){
            answer+=" ";
        }
    }
    return answer;
}

int main(){
    string MESSAGE;
    getline(cin, MESSAGE);

    cout << BinaryToNorris(MESSAGE) << endl;
}