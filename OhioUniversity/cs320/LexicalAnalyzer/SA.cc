//Author: Randal Obringer
//File: <Obringer>-<Randal>.cc
//Description: This is the syntactic analyzer

#include "SA.h"
#include "LexicalAnalyzer.h"
#include <math.h>

//below is the grammar
SA::SA(LexicalAnalyzer::LexicalAnalyzer la){
  float result = expr(la);
  cout << "The answer is " << result << "." << endl;
}

void SA::error(LexicalAnalyzer::LexicalAnalyzer la){
  cout << "Syntactic Error" << endl;
  if(la.nextToken_ == LexicalAnalyzer::EOF_){
    cout << "Unexpected end to the expression" << endl;
  }
  exit(-1); //end the program
}

float SA::expr(LexicalAnalyzer::LexicalAnalyzer la){
  float result = term(la);
  while(la.nextToken_ == LexicalAnalyzer::PLUS_ || la.nextToken_ == LexicalAnalyzer::MINUS_){
    if(la.nextToken_ == LexicalAnalyzer::PLUS_){
      la.lex();
      result+=term(la);
    }else if(la.nextToken_ == LexicalAnalyzer::MINUS_){
      la.lex();
      result-=term(la);
    }
  }
  return result;
}

float SA::term(LexicalAnalyzer::LexicalAnalyzer la){
  float result=factor(la);
  while(la.nextToken_ == LexicalAnalyzer::STAR_ || la.nextToken_ == LexicalAnalyzer::SLASH_){
    if(la.nextToken_ == LexicalAnalyzer::STAR_){
      la.lex();
      result*=factor(la);
    }else if(la.nextToken_ == LexicalAnalyzer::SLASH_){
      la.lex();
      result/=factor(la);
    }
  }
  return result;
}

float SA::factor(LexicalAnalyzer::LexicalAnalyzer la){
  float result;
  if((la.nextToken_ == LexicalAnalyzer::NUMBER_)||(la.nextToken_ == LexicalAnalyzer::UNKNOWN_)){
    result=base(la);
    if(la.nextToken_ == LexicalAnalyzer::HASH_){
      la.lex();
      result=pow(result,factor(la));
    }else if(la.nextToken_ == LexicalAnalyzer::LPAR_){
      error(la);
    }
  }else if(la.nextToken_ == LexicalAnalyzer::LPAR_){
    la.lex();
    if(la.nextToken_ == LexicalAnalyzer::EOF_){
      error(la);
    }else{
      result=expr(la);
    }
    if(la.nextToken_ == LexicalAnalyzer::RPAR_){
      la.lex();
    }else{
      error(la);
    }
  }else if(la.nextToken_ == LexicalAnalyzer::MINUS_){
    la.lex();
    if(la.nextToken_ == LexicalAnalyzer::EOF_){
      error(la);
    }else{
      result=-factor(la); 
    }
  }else{
    error(la);
  }
  return result;
}

float SA::base(LexicalAnalyzer::LexicalAnalyzer la){
  float result;
  if(la.nextToken_ == LexicalAnalyzer::UNKNOWN_){
    cout << "Lexical Error" << endl;
    exit(-1); // Exit the program
  }else if(la.nextToken_ == LexicalAnalyzer::NUMBER_){
    result = int(la.nextLexeme_[0]-'0');  //convert string to integer value
    la.lex();
    if(la.nextToken_ == LexicalAnalyzer::LPAR_){
      error(la);
    }
  }
  return result;
}
