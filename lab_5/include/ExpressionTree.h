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
    TokenList(const TokenList& other);
    TokenList& operator=(const TokenList& other);
    ~TokenList();
    void addToken(const std::string &token);
  };

  bool isOperator(const std::string &s) const;
  int getPriority(const std::string &op) const;
  double evaluate(TreeNode<std::string> *node) const;
  void infixToPostfix(const TokenList &infix, TokenList &postfix) const;
  double parseNumber(const std::string& numStr) const;
  double processIntegerPart(const char* str, int& index, bool& hasFraction) const;
  double processFractionalPart(const char* str, int& index, double& divisor) const;
  double evaluateOperator(TreeNode<std::string>* node) const;
  double handleDivision(double left, double right) const;
  bool buildTreeFromPostfix(const TokenList& postfix);
  bool processTokenAsOperator(const std::string& token, TreeNode<std::string>* node, TreeNode<std::string>*(*pop)());
  void cleanupStack(struct StackNode* stackTop, TreeNode<std::string>*(*pop)());
  bool finalizeTree(struct StackNode* stackTop, TreeNode<std::string>*(*pop)());

public:
  bool buildFromExpression(const std::string &expression);
  TokenList tokenize(const std::string &expression) const;
  double evaluate() const;
  void printTree() const;
};

#endif