// program6.cpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 06
// December 2, 2025
//
// The driver file for Program 6.


#include <FlexLexer.h>
#include <iostream>
#include <string>

#include "nodes.hpp"
#include "tables.hpp"
#include "program6.tab.hpp"

using namespace std;

yyFlexLexer myScanner;

extern shared_ptr<Table> globalScope;

int main () {
  cout << endl;

  Node* tree = nullptr;
  yyparse(tree);

  cout << endl;

  // Print the symbol table
  if (globalScope) {
    globalScope->print();
  }

  cout << endl;

  return 0;
}
