// tables.hpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// November 11, 2025
//
// Symbol Table Class File

#include <iostream>

#include "nodes.hpp"
#include "tables.hpp"


// --- Symbol Entry ---

// Constructors
SymbolEntry::SymbolEntry() : isFunction(false) { }
SymbolEntry::SymbolEntry(const string& name, const string& type)
  : name(name), type(type), isFunction(false) { }
SymbolEntry::SymbolEntry(const string& name, const string& returnType,
                         const vector<string>& params)
  : name(name), type(returnType), paramTypes(params), isFunction(true) { }

// Print Entry
void SymbolEntry::print(int indent) const {
  string ind(indent, ' ');

  cout << ind << name << " ";

  if (isFunction) {
    cout << type << " <- ";

    for (size_t i = 0; i < paramTypes.size(); ++i) {
      cout << paramTypes[i];

      if (i + 1 < paramTypes.size()) {
        cout << " ";
      }
    }
  }
  else {
    cout << type;
  }

  cout << "\n";
}



// --- Table ---

// Constructor
Table::Table(shared_ptr<Table> parentScope) : parent(parentScope) { }

// Insert New Entry (check only current scope)
bool Table::insert(const SymbolEntry& sym, shared_ptr<Table>& t) {

  if (symbols.count(sym.name) > 0) {
    cerr << "Error: Symbol '" << sym.name
         << "' already declared in this scope." << endl;
    return false;
  }

  insertionOrder.push_back(sym.name);
  symbols[sym.name] = sym;

  return true;
}

// Lookup Existing Entry (from parent scopes too)
SymbolEntry* Table::lookup(const string& name) {
  auto it = symbols.find(name);

  if (it != symbols.end()) {
    return &it->second;
  }

  if (parent) {
    return parent->lookup(name);
  }

  return nullptr;
}

// Check if symbol exists in the current table (class) only, not parent scopes
bool Table::hasMember(const std::string& name) const {
  return symbols.find(name) != symbols.end();
}

// Print Tables and Any Subtables
void Table::print(int indent) const {
  string ind(indent, ' ');

  for (const auto& name : insertionOrder) {
    symbols.at(name).print(indent);

    auto it = subtables.find(name);
    if (it != subtables.end()) {
      it->second->print(indent + 2);
    }
  }
}


vector<string> extractParamNodes(Node* node) {
  vector<string> types;
  if (!node) {
    return types;
  }

  // If this node is a param, grab its type
  if (node->getval() == "param") {
    if (!node->children.empty()) {
      types.push_back(getTypeFromNode(node->children[0]));
    }
  }

  // Recursion
  for (Node* child : node->children) {
    vector<string> childTypes = extractParamNodes(child);
    types.insert(types.end(), childTypes.begin(), childTypes.end());
  }

  return types;
}

void insertParamsToScope(Node* paramNode, shared_ptr<Table> scope) {
  if (!paramNode) { 
    return;
  }

  if (paramNode->getval() == "param") {
    Node* typeNode = paramNode->children[0];
    Node* idNode   = paramNode->children[1];
    if (!idNode) { 
      return;
    }

    string paramName = idNode->getval();
    string paramType = getTypeFromNode(typeNode);

    SymbolEntry sym(paramName, paramType);
    scope->insert(sym, scope);
  }
  else {
    for (Node* child : paramNode->children) {
      insertParamsToScope(child, scope);
    }
  }
}
