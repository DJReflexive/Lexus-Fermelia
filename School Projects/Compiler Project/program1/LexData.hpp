// LexData.hpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 01
// September 3, 2025
//
// Simple Data Structure to help keep track of data.

#ifndef LEXDATA_HPP
#define LEXDATA_HPP

#include <string>

using namespace std;

class LexData {
private:
  int line;
  int column;
  int type;
  int length;
  string value;

public:
  int getLine() { return line; }
  int getColumn() { return column; }
  int getType() { return type; }
  int getLength() { return length; }
  string getValue() { return value; }

  void setLine(int i) { line = i; }
  void setColumn(int i) { column = i; }
  void setType(int i) { type = i; }
  void setLength(int i) { length = i; }
  void setValue(string str) { value = str; }
};


#endif
