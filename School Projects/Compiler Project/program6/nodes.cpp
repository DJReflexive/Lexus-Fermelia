// nodes.cpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// October 15, 2025
//
// Implementation of Node class for parse tree printing

#include "nodes.hpp"
#include <iostream>
#include <string>

using namespace std;

// Constructors
Node::Node() : children(), next(nullptr), value(""), type("") {}
Node::Node(Node* child) : children(), next(nullptr) {
  if (child) { 
    children.push_back(child);
  }
}
Node::Node(Node* left, Node* right) : children(), next(nullptr) {
  if (left) { 
    children.push_back(left);
  }
  if (right) {
    children.push_back(right);
  }
}

// Destructor
Node::~Node() {
  for (auto c : children) { 
    delete c;
  }
  delete next;
}

void Node::addChild(Node* child) {
  if (child) { 
    children.push_back(child);
  }
}

void Node::setnext(Node* n) {
  next = n;
}

void Node::setval(const string& v) {
  value = v; 
  type = "";
}

void Node::setval(const string& v, const string& t) {
  value = v;
  type = t;
}

string Node::getval() const {
  return value;
}

string Node::gettype() const {
  return type;
}

string getNameFromNode(Node* node) {
  if (!node) {
    return "";
  }

  if (node->getval() == "ID") {
    return node->getval();
  }

  // recursively check children
  for (Node* child : node->children) {
    string n = getNameFromNode(child);

    if (!n.empty()) {
      return n;
    }
  }

  return "";
}


string getTypeFromNode(Node* node) {
  if (!node) {
    return "";
  }

  Node* cur = node;

  int dims = 0;
  while (cur && cur->getval() == "arraytype") {
    dims++;

    if (cur->children.size() > 0) {
      cur = cur->children[0];
    }
    else {
      break;
    }
  }

  // At this point, cur should be the base type: INT or ID
  string base = cur->getval();

  if (base == "INT") {
    base = "int";
  }

  for (int i = 0; i < dims; i++) {
    base += "[]";
  }

  return base;
}

// Print production for this node
void Node::printProduction(ostream* out, int depth) const {
  if (value.empty()) { 
    return;
  }

  if (type == value) {
    return;
  }

  string indent(depth*2, ' ');

  if (!type.empty()) {
    *out << indent << type;

    if (!value.empty()) {
      *out << " --> " << value;
    }

    *out << endl;
    return;
  }

  if (children.empty()) {
    *out << indent << value << endl;
    return;
  }

  *out << indent << "<" << value << "> --> ";

  bool first = true;
  for (auto c : children) {
    if (!c) { 
      continue;
    }

    if (!first) {
      *out << " ";
    }
    first = false;

    if (!c->type.empty()) {
      *out << c->type;
    }
    else if (!c->value.empty()) {
      *out << "<" << c->value << ">";
    }
  }

  *out << endl;
}


// Public print function
void Node::print(ostream* out) const {
  cout << endl;
  printRecursive(out);
}

void Node::printRecursive(ostream* out, int depth) const {
  printProduction(out, depth);

  for (auto c : children) {
    if (c) {
      c->printRecursive(out, depth+1);
    }
  }

  if (next) {
    next->printRecursive(out, depth);
  }
}

// Specialized nodes
nodeExpExp::nodeExpExp(Node* left, Node* right) : Node(left, right) {}
nodeParExp::nodeParExp(Node* inner) : Node(inner) { 
  value = "(exp)";
}
nodeMinus::nodeMinus(Node* inner) : Node(inner) {
  value = "UMINUS";
}
