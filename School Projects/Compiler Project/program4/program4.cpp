// program4.cpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 04
// October 28, 2025
//
// The driver file for Program 4.


#include <FlexLexer.h>
#include <iostream>

#include "nodes.hpp"
#include "program4.tab.hpp"

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

/* ================================= TODO LIST =================================

  ------------------- Program 4 Instruction Notes (In Order) -------------------
  1. Check to see if parse tree is printing like Kim's example (in assignment)



  ------------------------ Once Most Everything is Done ------------------------
  - Test with Kim's inputs in program3 .txt feedback

  
  ---------------------------- Getting Ready Submit ----------------------------
  - Reread the whole instruction doc
  
  ==============================================================================
*/ 
