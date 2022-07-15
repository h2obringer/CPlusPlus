#include <iostream>
#include <sstream>
#include <cctype>

#include "LexicalAnalyzer.h"

const char* LexicalAnalyzer::MATH_SYMBOLS_ = "+-*/()^";  //I added ^

LexicalAnalyzer::LexicalAnalyzer(string input)
  : pos_(0)
{
  istringstream ss(input);
  string chunk;

  // Read first chunk of non-whitespace characters.
  ss >> chunk;
  while (chunk.length() > 0) {
    size_t last_pos = 0;
    // Find position of first math symbol.
    size_t pos = chunk.find_first_of(MATH_SYMBOLS_, last_pos);
    while (pos != string::npos) {
      if (pos > last_pos)
        lexemes_.push_back(chunk.substr(last_pos, pos - last_pos));
      lexemes_.push_back(chunk.substr(pos, 1));
      last_pos = pos + 1;

      // Find position of next math symbol.
      pos = chunk.find_first_of(MATH_SYMBOLS_, last_pos);
    }
    if (last_pos < chunk.length())
      lexemes_.push_back(chunk.substr(last_pos, chunk.length() - last_pos));

    // Read next chunk of non-whitespace characters.
    chunk = ""; ss >> chunk;
  }
  
  lex();
}


void LexicalAnalyzer::lex()
{
  if (pos_ == lexemes_.size()) {
    nextToken_ = EOF_;
    nextLexeme_ = "";
    return;
  }

  nextLexeme_ = lexemes_[pos_++];
  
  if (nextLexeme_ == "+")
    nextToken_ = PLUS_;
  else if (nextLexeme_ == "-")
    nextToken_ = MINUS_;
  else if (nextLexeme_ == "*")
    nextToken_ = STAR_;
  else if (nextLexeme_ == "/")
    nextToken_ = SLASH_;
  else if (nextLexeme_ == "(")
    nextToken_ = LPAR_;
  else if (nextLexeme_ == ")")
    nextToken_ = RPAR_;
  else if (nextLexeme_ == "^")
    nextToken_ = HASH_;
  else {
    bool bNumber = true;
    size_t pos = 0;
    while (bNumber && pos < nextLexeme_.length()) {
      if (!isdigit(nextLexeme_[pos++]))
        bNumber = false;
    }
    
    if (bNumber)
      nextToken_ = NUMBER_;
    else
      nextToken_ = UNKNOWN_;
  }
}
