//******************************************************************
//  File: countLetters.cc
//
//  Author: Randy Obringer
//  Email: ro120908@ohio.edu
//
//  Description: Class implementation
//
//  Last Updated: 6/18/2011
//******************************************************************

#include "countLetters.h"

//******************************************************************
//  Function: count (public)
//  
//  Parameter: string (passed by reference)
//
//  Effects: returns the amount of letters in the word version of a
//    number.
//******************************************************************
int countLetters::count(string &word){
  int totalLetters=0;
  string w;
  istringstream in(word);
  if(!in.fail()){
    in >> w;    
    while(in){ 
      totalLetters+=w.length();
      in >> w;
    }
  }
  return totalLetters;
}

//******************************************************************
//  Function: numberToWord (public)
//
//  Parameter: an integer
//
//  Effect: Converts the given number into its word equivalent
//  Assumptions: The number is smaller than 10000
//******************************************************************
string countLetters::numberToWord(int n){
  string word="";
  int onesPlace=-1;
  int tensPlace=-1;
  int hundredsPlace=-1;
  int thousandsPlace=-1;
  int temp=-1;
  onesPlace=n%10;
  if(n>9){
    temp=n/10;
    tensPlace=temp%10;
    if(n>99){
      temp=temp/10;
      hundredsPlace=temp%10;
      if(n>999){
        temp=temp/10;
        thousandsPlace=temp%10;
      }
    }
  }
  if(thousandsPlace!=-1){
    if(thousandsPlace==1){
      word+="one thousand ";
    }else if(thousandsPlace==2){
      word+="two thousand ";
    }else if(thousandsPlace==3){
      word+="three thousand ";
    }else if(thousandsPlace==4){
      word+="four thousand ";
    }else if(thousandsPlace==5){
      word+="five thousand ";
    }else if(thousandsPlace==6){
      word+="six thousand ";
    }else if(thousandsPlace==7){
      word+="seven thousand ";
    }else if(thousandsPlace==8){
      word+="eight thousand ";
    }else if(thousandsPlace==9){
      word+="nine thousand ";
    }
  }
  if(hundredsPlace!=-1){
    if((hundredsPlace==1)&&(tensPlace==0)&&(onesPlace==0)){
      word+="one hundred";
    }else if((hundredsPlace==2)&&(tensPlace==0)&&(onesPlace==0)){
      word+="two hundred";
    }else if((hundredsPlace==3)&&(tensPlace==0)&&(onesPlace==0)){
      word+="three hundred";
    }else if((hundredsPlace==4)&&(tensPlace==0)&&(onesPlace==0)){
      word+="four hundred";
    }else if((hundredsPlace==5)&&(tensPlace==0)&&(onesPlace==0)){
      word+="five hundred";
    }else if((hundredsPlace==6)&&(tensPlace==0)&&(onesPlace==0)){
      word+="six hundred";
    }else if((hundredsPlace==7)&&(tensPlace==0)&&(onesPlace==0)){
      word+="seven hundred";
    }else if((hundredsPlace==8)&&(tensPlace==0)&&(onesPlace==0)){
      word+="eight hundred";
    }else if((hundredsPlace==9)&&(tensPlace==0)&&(onesPlace==0)){
      word+="nine hundred";
    }else if(hundredsPlace==1){
      word+="one hundred and ";
    }else if(hundredsPlace==2){
      word+="two hundred and ";
    }else if(hundredsPlace==3){
      word+="three hundred and ";
    }else if(hundredsPlace==4){
      word+="four hundred and ";
    }else if(hundredsPlace==5){
      word+="five hundred and ";
    }else if(hundredsPlace==6){
      word+="six hundred and ";
    }else if(hundredsPlace==7){
      word+="seven hundred and ";
    }else if(hundredsPlace==8){
      word+="eight hundred and ";
    }else if(hundredsPlace==9){
      word+="nine hundred and ";
    }
  }
  if(tensPlace!=-1){
    if((tensPlace==1)&&(onesPlace==0)){
      word+="ten";
      return word;
    }else if((tensPlace==1)&&(onesPlace==1)){
      word+="eleven";
      return word;
    }else if((tensPlace==1)&&(onesPlace==2)){
      word+="twelve";
      return word;
    }else if((tensPlace==1)&&(onesPlace==3)){
      word+="thirteen";
      return word;
    }else if((tensPlace==1)&&(onesPlace==4)){
      word+="fourteen";
      return word;
    }else if((tensPlace==1)&&(onesPlace==5)){
      word+="fifteen";
      return word;
    }else if((tensPlace==1)&&(onesPlace==6)){
      word+="sixteen";
      return word;
    }else if((tensPlace==1)&&(onesPlace==7)){
      word+="seventeen";
      return word;
    }else if((tensPlace==1)&&(onesPlace==8)){
      word+="eighteen";
      return word;
    }else if((tensPlace==1)&&(onesPlace==9)){
      word+="nineteen";
      return word;
    }else if(tensPlace==2){
      word+="twenty ";
    }else if(tensPlace==3){
      word+="thirty ";
    }else if(tensPlace==4){
      word+="forty ";
    }else if(tensPlace==5){
      word+="fifty ";
    }else if(tensPlace==6){
      word+="sixty ";
    }else if(tensPlace==7){
      word+="seventy ";
    }else if(tensPlace==8){
      word+="eighty ";
    }else if(tensPlace==9){
      word+="ninety ";
    }
  }
  if(onesPlace==1){
    word+="one";
  }else if(onesPlace==2){
    word+="two";
  }else if(onesPlace==3){
    word+="three";
  }else if(onesPlace==4){
    word+="four";
  }else if(onesPlace==5){
    word+="five";
  }else if(onesPlace==6){
    word+="six";
  }else if(onesPlace==7){
    word+="seven";
  }else if(onesPlace==8){
    word+="eight";
  }else if(onesPlace==9){
    word+="nine";
  }
  return word;
}

//*****************************************************************
//  Function: findAnswer
//
//  Effect: iterates over 1 through 1000 and counts the letters
//    of the word equivalent of the number
//*****************************************************************
long long countLetters::findAnswer(){
  long long totalLetters=0;
  string temp;
  for(int i=1000;i>0;i--){
    temp=numberToWord(i);
    totalLetters+=count(temp);
  }
  return totalLetters;
}
