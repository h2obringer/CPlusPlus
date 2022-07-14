/*Author: Randal Obringer
*
* Date Last Modified: 28 August 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Description: Read in a dictionary of words and 7 scrabble letters. Match our letters to 
*  the dictionary words, If we can make the word then score it according to scrabble scoring
*  rules. Choose the highest value word that we can make and output the winning word.
*
* Problem Statement: When playing Scrabble©, each player draws 7 letters and 
*	must find a word that scores the most points using these letters. A 
*	player doesn't necessarily have to make a 7-letter word; the word can 
*	be shorter. The only constraint is that the word must be made using the 
*	7 letters which the player has drawn. For example, with the letters  etaenhs, 
*	some possible words are: ethane, hates, sane, ant. Your objective is to 
*	find the word that scores the most points using the available letters 
*	(1 to 7 letters).
*
* Rules: 
*	In Scrabble©, each letter is weighted with a score depending on how 
*	difficult it is to place that letter in a word. You will see below a 
*	table showing the points corresponding to each letter:
*		Points		Letters
*		1			e, a, i, o, n, r, t, l, s, u
*		2			d,g
*		3			b, c, m, p
*		4			f, h, v, w, y
*		5			k
*		8			j, x
*		10			q, z
*
*	The word banjo earns you 3 + 1 + 1 + 8 + 1 = 14 points.
*	A dictionary of authorized words is provided as input for the program. 
*	The program must find the word in the dictionary which wins the most 
*	points for the seven given letters (a letter can only be used once). If 
*	two words win the same number of points, then the word which appears 
*	first in the order of the given dictionary should be chosen.
*	All words will only be composed of alphabetical characters in lower 
*	case. There will always be at least one possible word.
*
* Game Input: 
*	Line 1: the number N of words in the dictionary
*	N following lines: the words in the dictionary. One word per line.
*	Last line: the 7 letters available.
*
* Output: The word that scores the most points using the available letters 
*	(1 to 7 letters). The word must belong to the dictionary. Each letter 
*	must be used at most once in the solution. There is always a solution.
*
* Constraints:
*	0 < N < 100000
*	Words in the dictionary have a maximum length of 30 characters.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//score the character we use and add it to the current score tally
int addToScore(char c){
    switch(c){
        case 'e':
        case 'a':
        case 'i':
        case 'o':
        case 'n':
        case 'r':
        case 't':
        case 'l':
        case 's':
        case 'u':
            return 1;
            break; //no necessary but will include anyways
        case 'd':
        case 'g':
            return 2;
            break;
        case 'b':
        case 'c':
        case 'm':
        case 'p':
            return 3;
            break;
        case 'f':
        case 'h':
        case 'v':
        case 'w':
        case 'y':
            return 4;
            break;
        case 'k':
            return 5;
            break;
        case 'j':
        case 'x':
            return 8;
            break;
        case 'q':
        case 'z':
            return 10;
            break;
        default:
            return 0;
            break;
    };
}

int main(){
    int N; //number of words in dictionary
    cin >> N; cin.ignore();
    
    vector<string> word; //hold the dictionary
    for (int i = 0; i < N; i++) {
        string W;
        getline(cin, W);
        word.push_back(W);
    }
    
    string LETTERS; //The letters we own to play scrabble with
    getline(cin, LETTERS);
    cerr << "Our letters are: " << LETTERS << endl;
    
    int bestScore=0; //hold score of best word
    string bestWord=""; //hold best word
    int currentScore=0; //hold current score of word we are currently computing
    bool canMakeWord=false; //if we don't own a letter that matches a letter in the word we are checking then we can't make the word, break out of our loop early
    bool wordComplete=false; //did we complete the word?
    string letterPool=LETTERS; //allow us to reset after each word check
    bool letterFound = false; //is the letter we own part of the current word?
    
    for(int i=0;i<N;i++){ //for each word in dictionary
        currentScore=0; //reset current score tally
        wordComplete=false; //the current word starts out incomplete
        LETTERS=letterPool; //reset letter pool
        
        cerr << "The word in the dictionary is: " << word[i] << endl;
        for(int j=0; j<word[i].length(); j++){ //for each letter in dictionary word
            canMakeWord=false; //we have a new letter to check
            letterFound=false; //we have a new letter
            for(int k=0;k<LETTERS.length();k++){
                cerr << LETTERS[k];
                if(LETTERS[k]==word[i][j]){ //if one of our letters match a letter in current word of dictionary
                    currentScore+=addToScore(LETTERS[k]);
                    canMakeWord=true;
                    if(letterFound==false){
                        LETTERS[k]='*'; //write over current letter as found
                        letterFound=true; //ensure we don't write over the same letter if we have more than 1 of them
                    }
                    if(j==word[i].length()-1){ //if last letter of the dictionary word was matched and we own no more letters then we completed the word with our letters
                        wordComplete=true;
                    }
                }
            }
            cerr << endl;
            if(canMakeWord==false){ //we did not have that letter in the dictionary word so move on to the next word
                cerr << "Could not match " << word[i][j] << " to our letters" << endl;
                break;
            }
        }
        if(wordComplete==true){
            if(currentScore>bestScore){
                //cerr << "Best Score is: " << bestScore << endl;
                bestScore=currentScore;
                bestWord=word[i];
            }
        }
    }
    
    //cerr << "The letters you were given are: " << LETTERS << endl;
    cout << bestWord << endl;
}