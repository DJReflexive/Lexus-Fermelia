// tokens.hpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 01
// September 1, 2025
//
// Header file for token values.

#ifndef TOKENS_HPP
#define TOKENS_HPP

enum TokenType {
  TOK_EOF = 0,            // <<EOF>>
  TOK_COMPARE_OP = 1,     // == != >= <= > <
  TOK_LOGICAL_OP = 2,     // && ||
  TOK_MATH_OP = 3,        // + - * /
  TOK_ENCLOSING_OP = 4,   // () {} []
  TOK_PUNCTUATION = 5,    // , . ;
  TOK_KEYWORD = 6,        // this if else while
  TOK_IDENTIFIER = 7,     // Starts w/ '_' or letter...
  TOK_NUMBER = 8,         // An integer
  TOK_FLOAT = 9,          // Any variation of a float value
  TOK_UNRECOGNIZED = 10,  // Unrecognized Character
  TOK_NEWLINE = 11,       // '\n'

  TOK_SPACE = 12,         // ' '
  TOK_TAB = 13,           // '\t'

  TOK_OPENCOMMENT = 14,   // /*
  TOK_CLOSECOMMENT = 15   // */
};

#endif
