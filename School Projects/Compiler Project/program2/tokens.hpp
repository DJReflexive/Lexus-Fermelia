// tokens.hpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 02
// September 13, 2025
//
// Header file for token values.

#ifndef TOKENS_HPP
#define TOKENS_HPP

enum TokenType {
  EOFT = 0,           // <<EOF>>

  IDENT = 1,          // Starts w/ '_' or letter...
  NUMBER = 2,         // An integer

  // Symbol Operators
  LBRACK = 3,         // [
  RBRACK = 4,         // ]
  LBRACE = 5,         // {
  RBRACE = 6,         // }
  NEQ = 7,            // !=
  EQ = 8,             // ==
  LT = 9,             // <
  GT = 10,            // >
  LEQ = 11,           // <=
  GEQ = 12,           // >=
  AND = 13,           // &&
  OR = 14,            // ||
  NOT = 15,           // !
  PLUS = 16,          // +
  MINUS = 17,         // -
  TIMES = 18,         // *
  DIV = 19,           // /
  MOD = 20,           // %
  SEMI = 21,          // ;
  COMMA = 22,         // ,
  LPARAN = 23,        // (
  RPARAN = 24,        // )
  ASSIGN = 25,        // =
  DOT = 26,           // .

  // Keywords
  INT = 27,           // int
  VOID = 28,          // void
  CLASS = 29,         // class
  NEW = 30,           // new
  PRINT = 31,         // print
  READ = 32,          // read
  RETURN = 33,        // return
  WHILE = 34,         // while
  IF = 35,            // if
  ELSE = 36,          // else
  THIS = 37,          // this
  NULLT = 38,         // null

  // Whitespace
  SPACE = 39,         // ' '
  TAB = 40,           // '\t'
  NEWLINE = 41,       // '\n'

  // Comments
  COMMENT = 42,       // //
  OPENCOMMENT = 43,   // /*
  CLOSECOMMENT = 44,  // */

  // Errors
  ER_CH = 45,         // Single character error
  ER_WD = 46,         // Multi-character word error
  ERRORS = 47         // Thrown when 21st error is reached
};

#endif
