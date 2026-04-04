// program2.cpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 02
// September 13, 2025
//
// The driver file for Program 2.


#include <FlexLexer.h>
#include <iostream>
#include <vector>

#include "LexData.hpp"
#include "tokens.hpp"

using namespace std;

int main () {
  yyFlexLexer myScanner;
  int rtn;

  // Token names for printing, index value corresponds to enum value
  const char* tokenNames[] = {
    "EOFT", "IDENT", "NUMBER", "LBRACK", "RBRACK", "LBRACE", "RBRACE", "NEQ",
    "EQ", "LT", "GT", "LEQ", "GEQ", "AND", "OR", "NOT", "PLUS", "MINUS", 
    "TIMES", "DIV", "MOD", "SEMI", "COMMA", "LPARAN", "RPARAN", "ASSIGN", 
    "DOT", "INT", "VOID", "CLASS", "NEW", "PRINT", "READ", "RETURN", "WHILE", 
    "IF", "ELSE", "THIS", "NULLT", "SPACE", "TAB", "NEWLINE", "COMMENT", 
    "OPENCOMMENT", "CLOSECOMMENT", "ER_CH", "ER_WD", "ERRORS"
  };

  vector<LexData> data;
  int quitErrorCount = 0;
  int currentColumn = 1;
  int currentLine = 1;
  bool commentingEnabled = false;

  while ((rtn=myScanner.yylex()) != EOFT ) {
    LexData currentEntry;
    currentEntry.setLine(currentLine);
    currentEntry.setColumn(currentColumn);
    currentEntry.setToken(tokenNames[rtn]);
    currentEntry.setValue("");

    // Handle special-case tokens
    switch (rtn) {
      case IDENT:
        currentEntry.setValue(myScanner.YYText());
        break;
      case NUMBER:
        currentEntry.setValue(myScanner.YYText());
        break;
      case COMMENT:
        currentColumn = 1;
        currentLine++;
        continue; // Don't print
        break;
      case SPACE:
        currentColumn++;
        continue; // Don't print
        break;
      case TAB:
        currentColumn = currentColumn + ((currentColumn+1) % 8);
        continue; // Don't print
        break;
      case NEWLINE:
        currentColumn = 1;
        currentLine++;
        continue; // Don't print
        break;
      case ER_CH:
        currentEntry.setValue(myScanner.YYText());
        quitErrorCount++;
        break;
      case ER_WD:
        currentEntry.setValue(myScanner.YYText());
        quitErrorCount++;
        break;
    }

    currentColumn += myScanner.YYLeng();

    // Handle errors
    if (quitErrorCount >= 21) {
      currentEntry.setToken("ERRORS");
      data.push_back(currentEntry);
      return 1;
    }

    // Handle /* ... */ comments
    if (rtn == CLOSECOMMENT && commentingEnabled == true) {
      commentingEnabled = false;
      continue; // Don't print
    }
    else if (commentingEnabled == true) {
      continue; // Don't print
    }
    else if (rtn == OPENCOMMENT && commentingEnabled == false) {
      commentingEnabled = true;
      continue; // Don't print
    }
    
    data.push_back(currentEntry);
  }

  // Print Output
  cout << "Line\tColumn\tToken\tValue" << endl;
  for (size_t i = 0; i < data.size(); i++) {
    cout << data[i].getLine() << "\t" << data[i].getColumn() << "\t"
        << data[i].getToken() << "\t" << data[i].getValue() << endl;
  }
  
  return 0;
}