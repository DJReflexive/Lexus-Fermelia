// typecheck.hpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// December 7, 2025
//
// Type checking functions for Program 6

#ifndef TYPECHECK_HPP
#define TYPECHECK_HPP

#include <memory>
#include <string>
#include "nodes.hpp"
#include "tables.hpp"

void typeCheck(Node* root, std::shared_ptr<Table> scope);

// Evaluate expression type
std::string checkExpType(Node* node, std::shared_ptr<Table> scope);

// Resolve variable/function names
SymbolEntry* resolveName(Node* nameNode, std::shared_ptr<Table> scope);

void annotateNodeType(Node* node, const std::string& type);

bool isIntType(const std::string& type);
bool isClassType(const std::string& type);
bool isCompatible(const std::string& lhs, const std::string& rhs);
bool isThisTypeValid(SymbolEntry* lhs, Node* rhsNode);

std::string getFunctionReturnType(std::shared_ptr<Table> scope);

#endif
