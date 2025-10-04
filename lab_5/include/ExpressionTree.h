#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H

#include "Tree.h"
#include <cctype>
#include <string>

void printString(const std::string &str);
void printInt(const int &value);

class ExpressionTree {
private:
  Tree<std::string> tree;

  struct TokenList {
    std::string *tokens;
    int count;
    int capacity;

    TokenList();
    ~TokenList();
    void addToken(const std::string &token);
  };

  bool isOperator(const std::string &s) const;
  int getPriority(const std::string &op) const;
  double evaluate(TreeNode<std::string> *node) const;
  void infixToPostfix(const TokenList &infix, TokenList &postfix) const;

public:
  bool buildFromExpression(const std::string &expression);
  TokenList tokenize(const std::string &expression) const;
  double evaluate() const;
  void printTree() const;
};

#endif