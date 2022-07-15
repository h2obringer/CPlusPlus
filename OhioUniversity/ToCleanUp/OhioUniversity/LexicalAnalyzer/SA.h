#ifndef SA_H
#define SA_H
#include "LexicalAnalyzer.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class SA{
  public:
    SA(LexicalAnalyzer la);
    void error(LexicalAnalyzer la);
    float base(LexicalAnalyzer la);
    float factor(LexicalAnalyzer la);
    float term(LexicalAnalyzer la);
    float expr(LexicalAnalyzer la);
};

#endif
