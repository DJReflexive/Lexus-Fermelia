// LexData.cpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// Program 02
// September 13, 2025
//
// Simple Data Structure to help keep track of data.

#include <string>
#include "LexData.hpp"


int LexData::getLine() { return line; }
int LexData::getColumn() { return column; }
string LexData::getToken() { return token; }
string LexData::getValue() { return value; }

void LexData::setLine(int i) { line = i; }
void LexData::setColumn(int i) { column = i; }
void LexData::setToken(string str) { token = str; }
void LexData::setValue(string str) { value = str; }
