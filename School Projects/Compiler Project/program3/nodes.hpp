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

class Node {
public:
  Node();
  Node(Node* child);
  Node(Node* left, Node* right);
  virtual ~Node();

  void addChild(Node* child);
  void setnext(Node* n);
  void setval(const std::string& v);
  void setval(const std::string& v, const std::string& t);

  void print(std::ostream* out) const;

protected:
  std::vector<Node*> children;
  Node* next;
  std::string value;
  std::string type;

  void printRecursive(std::ostream* out) const;
  virtual void printProduction(std::ostream* out) const;
};

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
