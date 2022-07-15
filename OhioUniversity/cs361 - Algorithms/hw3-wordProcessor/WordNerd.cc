//*********************************************************************
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Program: WordNerd.cc
//
//  Description: This is the class implementation of WordNerd, a class
//    that analyses words and gives functions to tell you information
//    about those words.
//
//  Assumptions:You are given lines from a paragraph one at a time.
//    The sentences have words in all lowercase letters.
//
//  Last updated: 5/1/2011
//
//*********************************************************************

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
using namespace std;

class WordNerd{
  public:
    vector<string> commonWords(vector<string> &paragraph,int k);
    vector<string> commonPalindromes(vector<string> &paragraph,int k);
    vector<list<string> > commonAnagrams(vector<string> &paragraph,int k);
  private:
};


//***********************************************************************
//  Function: commonWords (public)
//
//  Parameters: 
//    1. a vector of strings (lines of the paragraph)(passed by reference)
//    2. an integer for how long the word has to be in order to be in the
//      output
//
//  Methods: seperates words of each string in the paragraph(each line)
//    into stringstreams to seperate each word of each line individually.
//    A map is kept that counts each time the word is seen. The map is 
//    iterated through to find the most occurrences of a word. Iterates 
//    through a final time to put the most occurred words in a vector and
//    returns it
//
//  Output: gives a sorted vector of the most common words in a paragraph
//
//***********************************************************************
vector<string> WordNerd::commonWords(vector<string> &paragraph,int k){ 
  vector<string> words; 
  map<string,int> word_count;

  for(int i=0;i<paragraph.size();i++){
    istringstream in(paragraph[i]);
    while(!in.fail()){ 
      string word;
      in >> word;
      if(word.length()>=k){
        if(word_count[word]>0){
          word_count[word]++;
        }else{
          word_count[word]=1;
        }
      }
    }
  } //map(word,occurrences)
  
  map<string,int>::iterator p;
  int max=0;
  int temp;
  for(p=word_count.begin();p!=word_count.end();++p){
    temp=p->second;
    if(temp>max){
      max=temp;
    }
  } //max=most occurrences

  for(p=word_count.begin();p!=word_count.end();++p){
      if(p->second==max){
        words.push_back(p->first);
      }
      //words=list(max words)
  }return words;
}

//***********************************************************************
//  Function: commonPalindromes (public)
//
//  Parameters: 
//    1. a vector of strings (lines of the paragraph)(passed by reference)
//    2. an integer for how long the word has to be in order to be in the
//      output
//
//  Methods: seperates words of each string in the paragraph(each line)
//    into stringstreams to seperate each word of each line individually.
//    Uses half the length of the string to compare the beginning and end 
//    parts of the string for equality to check if word is a palindrome or not.
//    All palindromes are put into a map with the number of times it occurred.
//    Iterates to find the most occurrences and again to add those words to
//    the outputted vector.
//
//  Output:gives a sorted vector of the most commonw palindromes in a paragraph
//
//***********************************************************************
vector<string> WordNerd::commonPalindromes(vector<string> &paragraph,int k){ 
  vector<string> words; 
  map<string,int> palindromes;

  for(int i=0;i<paragraph.size();i++){
    istringstream in(paragraph[i]);
    while(!in.fail()){ 
      string word;
      in >> word;
      if(word.length()>=k){
        int wl=word.length();
        int steps;
        if(wl%2==1){
          steps=(wl/2)+1;
        }else{
          steps=wl/2;
        }//min steps necessary
        bool palin=true;
        for(int i=0;i<=steps;i++){
          if(word[i]!=word[wl-i-1]){
            palin=false;
            break;
          }
        }//checks if palindrome

        if(palin==true){
          if(palindromes[word]>0){
            palindromes[word]++;
          }else{
            palindromes[word]=1;
          }
        }
      }
    }
  } //map(wordPalin,occurrences)
  map<string,int>::iterator p;
  int max=0;
  for(p=palindromes.begin();p!=palindromes.end();++p){
    int temp=p->second;
    if(temp>max){
      max=temp;
    }
  } //max=most occurrences

  for(p=palindromes.begin();p!=palindromes.end();++p){
    if(p->second==max){
      words.push_back(p->first);
    }
  }//words=list(max palindromes)

  return words;
  
}

//***********************************************************************
//  Function: commonAnagrams (public)
//
//  Parameters: 
//    1. a vector of strings (lines of the paragraph)(passed by reference)
//    2. an integer for how long the word has to be in order to be in the
//      output
//
//  Methods: seperates words of each string in the paragraph(each line)
//    into stringstreams to seperate each word of each line individually.
//    Creates a map from each word and the occurrences of each. Then it
//    iterates through the map twice finding the "key" or "baseword"
//    and comparing it with the "key" or "baseword" of each word in the map.
//    A local maximum is kept in order to count the amount of times a
//    set of anagrams occurs. If the local maximum is bigger than the current max,
//    the max is set to the local max. The current vector is reset and a list 
//    will be added to the vector. If the local max and max are equal a list
//    will be added to the vector.
//
//  Output:gives a vector of lists of the most common words that are anagrams 
//    of eachother.
//
//***********************************************************************
vector<list<string> > WordNerd::commonAnagrams(vector<string> &paragraph,int k){
  vector<list<string> > wordsets; 
  map<string,int> words;
  for(int i=0;i<paragraph.size();i++){
    istringstream in(paragraph[i]);
    while(!in.fail()){ 
      string word;
      in >> word;
      if(word.length()>=k){
        if(words[word]>0){
          words[word]++;
        }else{
          words[word]=1;
        }
      }
    }
  } //so far we have a map of words and occurrences


  map<string,int>::iterator p1;
  map<string,int>::iterator p2;
  int max=0; //used to find most common anagrams with lmax's help
  
  for(p1=words.begin();p1!=words.end();++p1){
    int lmax=0;
    list<string> anagrams;
    string current=p1->first;
    string temp=current;
    sort(temp.begin(),temp.end());

//start loop
    for(p2=words.begin();p2!=words.end();++p2){ //iterates for all words in map
      if(p2->first==p1->first){ //don't count the same word as an anagram of itself
        //++p2; this was the problem in my code
        lmax=-1;
      }else{
        string other=p2->first;
        string temp2=other;
        sort(temp2.begin(),temp2.end());
        if(temp==temp2){//if current word contains same letters
          if(anagrams.empty()){
            anagrams.push_back(p1->first); //add current word to list if not already
            lmax=p1->second; 
          }
          anagrams.push_back(p2->first);//add other word to list
          lmax+=p2->second;
        }
      }
    }
//end loop

    if(max==lmax){
      if(wordsets.empty()){
        wordsets.push_back(anagrams);
      }else{
        wordsets.push_back(anagrams);
      }
    }else if(max<lmax){
      max=lmax;
      if(wordsets.empty()){
        wordsets.push_back(anagrams);
      }else{
        wordsets.clear();
        wordsets.push_back(anagrams);
      }
    }//end second for loop
  }//end first for loop
  return wordsets;
}

