// program3.cpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 03
// October 8, 2025
//
// The driver file for Program 3.


#include <FlexLexer.h>
#include <iostream>

#include "nodes.hpp"
#include "program3.tab.hpp"

using namespace std;

yyFlexLexer myScanner;

int main () {
  Node* tree = nullptr;
  yyparse(tree);

  // Print the parse tree
  if (tree) {
    tree->print(&cout);
  }

  return 0;
}
