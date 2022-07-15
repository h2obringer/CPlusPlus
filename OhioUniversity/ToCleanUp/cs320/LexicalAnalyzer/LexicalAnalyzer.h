#ifndef LEXICAL_ANALYZER_H__
#define LEXICAL_ANALYZER_H__

#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

class LexicalAnalyzer
{
public:
  enum TokenType {
    EOF_, // 0
    UNKNOWN_, // 1
    DIGIT_, // 2
    PLUS_, // 3
    MINUS_, // 4
    STAR_, // 5
    SLASH_, // 6
    LPAR_, // 7
    RPAR_, // 8
    NUMBER_, // 9
    HASH_  //10 I added this
  };

  static const char* MATH_SYMBOLS_;
  
public:
  LexicalAnalyzer(string input);
  void lex();
  
  TokenType nextToken_;
  string nextLexeme_;

private:
  vector<string> lexemes_;
  int pos_;
};

#endif // LEXICAL_ANALYZER_H__
