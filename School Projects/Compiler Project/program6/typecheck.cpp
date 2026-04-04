// typecheck.cpp
// Lexus Fermelia
// COSC 4785 Fall 2025
// December 7, 2025
//
// Implementation of type checking functions

#include "typecheck.hpp"
#include <iostream>

using namespace std;

// === Helper functions ===

bool isIntType(const string& type) {
  return type == "int";
}


bool isClassType(const string& type) {
  return !type.empty() && !isIntType(type) && type != "void";
}


bool isCompatible(const string& lhs, const string& rhs) {
  // Exact match
  if (lhs == rhs) {
    return true;
  }

  // Allow null for class types
  if (rhs == "null" && isClassType(lhs)) {
    return true;
  }

  return false;
}


bool isThisTypeValid(SymbolEntry* lhs, Node* rhsNode) {
  if (!rhsNode) {
    return false;
  }

  return rhsNode->getval() == "THIS" && lhs && isClassType(lhs->type);
}


string getFunctionReturnType(shared_ptr<Table> scope) {
  if (!scope) return "";

  if (!scope->functionReturnType.empty()) {
    return scope->functionReturnType;
  }

  // Search parent scopes for function return type
  return getFunctionReturnType(scope->parent);
}


SymbolEntry* resolveName(Node* nameNode, shared_ptr<Table> scope) {
  if (!nameNode) {
    return nullptr;
  }

  string id = nameNode->getval();
  if (id == "THIS") {
    if (nameNode->children.size() > 0) {
      cerr << "Error: 'this' cannot be used in a suffix chain" << endl;
      return nullptr;
    }
  }

  SymbolEntry* sym = scope->lookup(id);
  if (!sym) {
    cerr << "Error: Undefined symbol '" << id << "'" << endl;
    return nullptr;
  }

  // Handle suffix recursively
  for (Node* suffix : nameNode->children) {
    if (!suffix) {
      continue;
    }

    if (suffix->getval() == "THIS") {
      cerr << "Error: 'this' cannot appear in member access" << endl;
      return nullptr;
    }
  }

  return sym;
}


string checkExpType(Node* node, shared_ptr<Table> scope) {
  if (!node) {
    return "";
  }

  string val = node->getval();

  if (val == "call") {
    Node* funcNode = node->children[0];
    if (!funcNode) {
      return "unknown";
    }

    if (funcNode->getval() == "name" && funcNode->children.size() > 0) {
      Node* idNode = funcNode->children[0];
      string funcName = idNode->getval();

      if (funcName == "read") {
        return "int";
      }
      if (funcName == "print")  {
        return "void";
      }
    }

    SymbolEntry* sym = resolveName(funcNode, scope);
    if (!sym) {
      return "";
    }

    return "unknown";
  }

  if (val == "name") {
    Node* firstChild = node->children[0];
    if (!firstChild) {
      return "";}


    if (firstChild->getval() == "NUMBER") {
      return "int";
    }

    string id = firstChild->getval();
    if (id == "read") {
      return "int";
    }
    if (id == "print") {
      return "void";
    }

    if (id == "THIS") {
      string classType = scope->classType;
      shared_ptr<Table> classScope = scope;
      while (classScope->classType.empty() && classScope->parent) {
        classScope = classScope->parent;
      }

      if (node->children.size() > 1) {
        Node* suffixList = node->children[1];
        Node* firstSuffix = suffixList->children[0];
        string memberName = firstSuffix->getval();

        shared_ptr<Table> searchScope = classScope;
        SymbolEntry* entry = nullptr;
        while (searchScope) {
          if (searchScope->hasMember(memberName)) {
            entry = searchScope->lookup(memberName);
            break;
          }
          searchScope = searchScope->parent;
        }

        if (!entry) {
          cerr << "Error: Member '" << memberName << "' does not exist in class" << endl;
          return "error";
        }

        return entry->type;
      }

      return classType;
    }

    SymbolEntry* sym = resolveName(firstChild, scope);
    if (!sym) {
      return "";}


    return sym->type;
  }

  if (val == "(exp)") return checkExpType(node->children[0], scope);

  if (node->gettype() == "NUMBER") {
    return "int";
  }

  if (val == "NULL") {
    return "null";
  }

  if (val == "READ") {
    return "int";
  }

  if (val == "UMINUS" || val == "UPLUS" || val == "NOT") {
    string t = checkExpType(node->children[0], scope);
    return t;
  }

  if (val == "PLUS" || val == "MINUS" || val == "TIMES" ||
      val == "DIV" || val == "MOD") {
    return "int";
  }

  if (val == "AND" || val == "OR" || val == "EQ" || val == "NEQ" ||
      val == "LT" || val == "LEQ" || val == "GT" || val == "GEQ") {
    return "int";
  }

  if (val == "new") {
    if (node->children.empty()) {
      return "error";
    }

    Node* typeNode = node->children[0];
    return getTypeFromNode(typeNode);
  }

  return "unknown";
}


void annotateNodeType(Node* node, const string& type) {
  if (!node) {
    return;
  }
  node->type = type;
}


void typeCheck(Node* root, shared_ptr<Table> scope) {
  if (!root) {
    return;
  }

  string val = root->getval();

  if (val == "assign") {
    string lhsType = checkExpType(root->children[0], scope);
    Node* rhsNode = root->children[2];

    if (!rhsNode) {
      cerr << "Error: Assignment RHS missing" << endl;
      return;
    }

    string rhsType = checkExpType(rhsNode, scope);

    if (lhsType == "error" || rhsType == "error") {
      annotateNodeType(root, "error");
    }
    else if (rhsNode->getval() == "THIS") {
      if (!isThisTypeValid(resolveName(root->children[0], scope), rhsNode)) {
        cerr << "Error: 'this' type does not match LHS type" << endl;
      }
      annotateNodeType(root, lhsType);
    }
    else if (!isCompatible(lhsType, rhsType)) {
      cerr << "Error: Type mismatch in assignment. LHS=" << lhsType
           << ", RHS=" << rhsType << endl;
      annotateNodeType(root, "error");
    }
    else {
      annotateNodeType(root, lhsType);
    }
  }
  else if (val == "return") {
    string funcReturnType = getFunctionReturnType(scope);

    if (funcReturnType.empty()) {
      cerr << "Error: return statement outside of function" << endl;
      return;
    }

    Node* returnExpr = (root->children.size() > 1) ? root->children[1] : nullptr;

    if (funcReturnType == "void") {
      if (returnExpr) {
        cerr << "Error: void method/constructor cannot return a value" << endl;
      }
      return;
    }

    if (!returnExpr) {
      cerr << "Error: non-void method must return a value" << endl;
      return;
    }

    string returnType = checkExpType(returnExpr, scope);

    if (returnType == "error") {
      annotateNodeType(root, "error");
    }
    else if (!isCompatible(funcReturnType, returnType)) {
      cerr << "Error: return type mismatch. Expected " << funcReturnType
           << ", got " << returnType << endl;
      annotateNodeType(root, "error");
    }
    else {
      annotateNodeType(root, funcReturnType);
    }
  }

  for (Node* c : root->children) {
    if (!c) {
      continue;
    }

    if (c->getval() == "method" || c->getval() == "constdec") {
      string methodName;

      if (c->getval() == "method" && c->children.size() > 2)
        methodName = c->children[2]->getval();
      else if (c->getval() == "constdec" && c->children.size() > 0)
        methodName = c->children[0]->getval();

      if (!methodName.empty() && scope->subtables.count(methodName)) {
        shared_ptr<Table> methodScope = scope->subtables[methodName];

        if (methodScope->functionReturnType.empty()) {
          if (c->getval() == "method" && c->children.size() > 1) {
            Node* returnTypeNode = c->children[1];
            if (returnTypeNode) {
              methodScope->functionReturnType = getTypeFromNode(returnTypeNode);
            }
          }
          else if (c->getval() == "constdec") {
            methodScope->functionReturnType = "void";
          }
        }

        typeCheck(c, methodScope);
        continue;
      }
    }

    if (c->getval() == "block") {
      if (scope->subtables.count("<block>")) {
        typeCheck(c, scope->subtables["<block>"]);
        continue;
      }
    }

    typeCheck(c, scope);
  }
}
