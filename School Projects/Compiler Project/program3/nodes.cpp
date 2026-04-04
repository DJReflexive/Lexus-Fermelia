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

// Print production for this node
void Node::printProduction(ostream* out) const {
    if (value.empty()) { 
      return;
    }

    // Terminals
    if (!type.empty()) {
        *out << type;
        if (!value.empty()) {
            *out << " --> " << value;
        }
        *out << endl;
        return;
    }

    // Empty nonterminals (no type, no children)
    if (children.empty()) {
        *out << value << endl; // Just the name, no arrows or <>
        return;
    }

    // Nonterminals with children
    *out << "<" << value << "> --> ";

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
            *out << c->type;          // Terminal: just type
        } else if (!c->value.empty()) {
            *out << "<" << c->value << ">";  // Nonterminal: angle brackets
        }
    }

    *out << endl;
}


// Public print function
void Node::print(ostream* out) const {
  cout << endl;
  printRecursive(out);
}

void Node::printRecursive(ostream* out) const {
    printProduction(out);

    for (auto c : children) {
        if (c) {
          c->printRecursive(out);
        }
    }

    if (next) {
        next->printRecursive(out);
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
