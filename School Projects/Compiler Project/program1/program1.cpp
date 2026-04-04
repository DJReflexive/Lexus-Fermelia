// program1.cpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 01
// August 28, 2025
//
// The driver file for Program 1.


#include <FlexLexer.h>
#include <iostream>
#include <vector>

#include "LexData.hpp"
#include "tokens.hpp"

using namespace std;

int main () {
  yyFlexLexer myScanner;
  int rtn;

  vector<LexData> data;
  int currentColumn = 1;
  int currentLine = 1;
  bool commentingEnabled = false;

  while ((rtn=myScanner.yylex()) != TOK_EOF ) {
    LexData currentEntry;

    currentEntry.setLine(currentLine);
    currentEntry.setColumn(currentColumn);
    currentEntry.setLength(myScanner.YYLeng());
    currentEntry.setValue(myScanner.YYText());

    switch (rtn) {
      case TOK_COMPARE_OP:
        currentEntry.setType(TOK_COMPARE_OP);
        break;
      case TOK_LOGICAL_OP:
        currentEntry.setType(TOK_LOGICAL_OP);
        break;
      case TOK_MATH_OP:
        currentEntry.setType(TOK_MATH_OP);
        break;
      case TOK_ENCLOSING_OP:
        currentEntry.setType(TOK_ENCLOSING_OP);
        break;
      case TOK_PUNCTUATION:
        currentEntry.setType(TOK_PUNCTUATION);
        break;
      case TOK_KEYWORD:
        currentEntry.setType(TOK_KEYWORD);
        break;
      case TOK_IDENTIFIER:
        currentEntry.setType(TOK_IDENTIFIER);
        break;
      case TOK_NUMBER:
        currentEntry.setType(TOK_NUMBER);
        break;
      case TOK_FLOAT:
        currentEntry.setType(TOK_FLOAT);
        break;
      case TOK_NEWLINE:
        currentEntry.setType(TOK_NEWLINE);
        currentEntry.setValue(""); // Don't actually print '\n'

        currentColumn = 0;
        currentLine++;
        break;
      case TOK_UNRECOGNIZED:
        currentEntry.setType(TOK_UNRECOGNIZED);
        break;
      case TOK_SPACE:
        currentColumn++;
        continue; // Don't print spaces
        break;
      case TOK_TAB:
        currentColumn = currentColumn + ((currentColumn+1) % 8);
        continue; // Don't print tabs
        break;
    }

    currentColumn += myScanner.YYLeng();

    if (rtn == TOK_CLOSECOMMENT && commentingEnabled == true) {
      commentingEnabled = false;
      continue; // Don't print comment character
    }
    else if (commentingEnabled == true) {
      continue; // Comments will ignore everything within comment
    }
    else if (rtn == TOK_OPENCOMMENT && commentingEnabled == false) {
      commentingEnabled = true;
      continue; // Don't print comment character
    }

    data.push_back(currentEntry);
  }

  // Print Output
  cout << "Line\tColumn\tType\tLength\tValue" << endl;
  for (size_t i = 0; i < data.size(); i++) {
    cout << data[i].getLine() << "\t"
        << data[i].getColumn() << "\t"
        << data[i].getType() << "\t"
        << data[i].getLength() << "\t"
        << data[i].getValue() << endl;
  }
  
  return 0;
}