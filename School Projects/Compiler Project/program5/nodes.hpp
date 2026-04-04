// nodes.hpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// October 15, 2025
//
// Node class for parse tree with automatic production printing

#ifndef NODES_HPP
#define NODES_HPP

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Node {
public:
  vector<Node*> children;
  Node* next;
  string value;
  string type;

  Node();
  Node(Node* child);
  Node(Node* left, Node* right);
  virtual ~Node();

  void addChild(Node* child);
  void setnext(Node* n);
  void setval(const string& v);
  void setval(const string& v, const string& t);
  string getval() const;

  void print(ostream* out) const;

protected:
  void printRecursive(ostream* out, int depth = 0) const;
  virtual void printProduction(ostream* out, int depth) const;
};

string getNameFromNode(Node* node);
string getTypeFromNode(Node* node);

// Specialized nodes for expressions
class nodeExpExp : public Node {
public:
  nodeExpExp(Node* left, Node* right);
};

class nodeParExp : public Node {
public:
  nodeParExp(Node* inner);
};

class nodeMinus : public Node {
public:
  nodeMinus(Node* inner);
};

#endif
