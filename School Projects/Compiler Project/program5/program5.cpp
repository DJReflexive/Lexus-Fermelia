// program5.cpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 05
// November 5, 2025
//
// The driver file for Program 5.


#include <FlexLexer.h>
#include <iostream>
#include <string>

#include "nodes.hpp"
#include "tables.hpp"
#include "program5.tab.hpp"

using namespace std;

yyFlexLexer myScanner;

extern shared_ptr<Table> globalScope;

int main () {
  Node* tree = nullptr;
  yyparse(tree);

  // Print the parse tree. Don't print for this assignment
  // if (tree) {  
  //   tree->print(&cout);
  // }

  // Print the symbol table
  if (globalScope) {
    globalScope->print();
  }

  return 0;
}
