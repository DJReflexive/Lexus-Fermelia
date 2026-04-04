// LexData.hpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 02
// September 13, 2025
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
  string token;
  string value;

public:
  int getLine();
  int getColumn();
  string getToken();
  string getValue();

  void setLine(int i);
  void setColumn(int i);
  void setToken(string str);
  void setValue(string str);
};


#endif
