// tables.hpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// November 11, 2025
//
// Symbol Table Header File



#ifndef TABLES_HPP
#define TABLES_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "nodes.hpp"

using namespace std;

// --- SymbolEntry ---
class SymbolEntry {
public:
  string name;
  string type;
  vector<string> paramTypes;
  bool isFunction;

  SymbolEntry();
  SymbolEntry(const string& name, const string& type);
  SymbolEntry(const string& name, const string& returnType,
              const vector<string>& params);

  void print(int indent = 0) const;
};


// --- Table ---
class Table {
public:
  vector<string> insertionOrder;
  map<string, SymbolEntry> symbols;
  map<string, shared_ptr<Table>> subtables;
  shared_ptr<Table> parent;
  string classType;
  string functionReturnType;

  Table(shared_ptr<Table> parentScope = nullptr);

  bool insert(const SymbolEntry& sym, shared_ptr<Table>& t);
  SymbolEntry* lookup(const string& name);
  bool hasMember(const std::string& name) const;
  void print(int indent = 0) const;
};

vector<string> extractParamNodes(Node* paramListNode);
void insertParamsToScope(Node* paramNode, shared_ptr<Table> scope);

#endif
