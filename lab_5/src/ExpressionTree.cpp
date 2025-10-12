#include "../include/ExpressionTree.h"
#include <cctype>
#include <iostream>

void clearTree(TreeNode<std::string> *node) {
  if (!node)
    return;
  clearTree(node->left);
  clearTree(node->right);
  delete node;
}

ExpressionTree::TokenList::TokenList() = default;

ExpressionTree::TokenList::TokenList(const TokenList &other)
    : count(other.count), capacity(other.capacity) {
  if (capacity > 0) {
    auto newTokens = new std::string[capacity];
    for (int i = 0; i < count; i++) {
      newTokens[i] = other.tokens[i];
    }
    tokens = newTokens;
  }
}

ExpressionTree::TokenList &
ExpressionTree::TokenList::operator=(const TokenList &other) {
  if (this != &other) {
    delete[] tokens;
    count = other.count;
    capacity = other.capacity;
    if (capacity > 0) {
      tokens = new std::string[capacity];
      for (int i = 0; i < count; i++) {
        tokens[i] = other.tokens[i];
      }
    } else {
      tokens = nullptr;
    }
  }
  return *this;
}

ExpressionTree::TokenList::~TokenList() {
  delete[] tokens;
  tokens = nullptr;
}

void ExpressionTree::TokenList::addToken(const std::string &token) {
  if (count >= capacity) {
    int newCapacity = capacity == 0 ? 10 : capacity * 2;
    auto newTokens = new std::string[newCapacity];
    for (int i = 0; i < count; i++) {
      newTokens[i] = tokens[i];
    }
    delete[] tokens;
    tokens = newTokens;
    capacity = newCapacity;
  }
  tokens[count++] = token;
}

bool ExpressionTree::isOperator(const std::string &s) const {
  return s == "+" || s == "-" || s == "*" || s == "/";
}

int ExpressionTree::getPriority(const std::string &op) const {
  if (op == "+" || op == "-")
    return 1;
  if (op == "*" || op == "/")
    return 2;
  return 0;
}

double ExpressionTree::evaluate(TreeNode<std::string> *node) const {
  if (!node)
    return 0.0;
  if (!isOperator(node->data)) {
    return parseNumber(node->data);
  }
  return evaluateOperator(node);
}

double ExpressionTree::parseNumber(const std::string &numStr) const {
  double result = 0.0;
  double fraction = 0.0;
  bool negative = false;
  bool hasFraction = false;
  double divisor = 1.0;

  const char *str = numStr.c_str();
  int i = 0;

  if (str[0] == '-') {
    negative = true;
    i++;
  }

  while (str[i] != '\0' && str[i] != '.') {
    if (std::isdigit(str[i])) {
      result = result * 10 + (str[i] - '0');
    }
    i++;
  }

  if (str[i] == '.') {
    hasFraction = true;
    i++;
  }

  if (hasFraction) {
    while (str[i] != '\0') {
      if (std::isdigit(str[i])) {
        fraction = fraction * 10 + (str[i] - '0');
        divisor *= 10;
      }
      i++;
    }
  }

  result += fraction / divisor;
  return negative ? -result : result;
}

double ExpressionTree::evaluateOperator(TreeNode<std::string> *node) const {
  double left = evaluate(node->left);
  double right = evaluate(node->right);

  if (node->data == "+")
    return left + right;
  if (node->data == "-")
    return left - right;
  if (node->data == "*")
    return left * right;
  if (node->data == "/") {
    if (right == 0) {
      std::cout << "Error: Division by zero!" << std::endl;
      return 0.0;
    }
    return left / right;
  }

  std::cout << "Error: Unknown operator: " << node->data << std::endl;
  return 0.0;
}

void ExpressionTree::infixToPostfix(const TokenList &infix,
                                    TokenList &postfix) const {
  auto operators = new std::string[infix.count];
  int opTop = -1;

  for (int i = 0; i < infix.count; i++) {
    const std::string &token = infix.tokens[i];
    if (token == "(") {
      operators[++opTop] = token;
    } else if (token == ")") {
      while (opTop >= 0 && operators[opTop] != "(") {
        postfix.addToken(operators[opTop]);
        opTop--;
      }
      if (opTop < 0) {
        std::cout << "Error: Mismatched parentheses!" << std::endl;
        delete[] operators;
        return;
      }
      opTop--;
    } else if (isOperator(token)) {
      while (opTop >= 0 && operators[opTop] != "(" &&
             getPriority(operators[opTop]) >= getPriority(token)) {
        postfix.addToken(operators[opTop]);
        opTop--;
      }
      operators[++opTop] = token;
    } else {
      postfix.addToken(token);
    }
  }

  while (opTop >= 0) {
    if (operators[opTop] == "(") {
      std::cout << "Error: Mismatched parentheses!" << std::endl;
      delete[] operators;
      return;
    }
    postfix.addToken(operators[opTop]);
    opTop--;
  }

  delete[] operators;
}

bool ExpressionTree::buildFromExpression(const std::string &expression) {
  TokenList tokens = tokenize(expression);
  if (tokens.count == 0) {
    std::cout << "Error: Empty expression!" << std::endl;
    return false;
  }

  TokenList postfix;
  infixToPostfix(tokens, postfix);

  if (postfix.count == 0) {
    std::cout << "Error: Could not convert to postfix!" << std::endl;
    return false;
  }

  return buildTreeFromPostfix(postfix);
}

void cleanupStack(TreeNode<std::string> **stack, int stackTop) {
  for (int j = 0; j <= stackTop; j++) {
    clearTree(stack[j]);
  }
}

bool ExpressionTree::buildTreeFromPostfix(const TokenList &postfix) {
  auto stack = new TreeNode<std::string>*[postfix.count];
  int stackTop = -1;

  for (int i = 0; i < postfix.count; i++) {
    const std::string &token = postfix.tokens[i];
    auto node = new TreeNode<std::string>(token);

    if (isOperator(token)) {
      if (stackTop < 1) {
        std::cout << "Error: Not enough operands for operator: " << token
                  << std::endl;
        clearTree(node);
        cleanupStack(stack, stackTop);
        delete[] stack;
        return false;
      }
      node->right = stack[stackTop--];
      node->left = stack[stackTop--];
    }

    stack[++stackTop] = node;
  }

  TreeNode<std::string> *root = stackTop >= 0 ? stack[stackTop] : nullptr;
  
  if (stackTop != 0) {
    std::cout << "Error: Too many operands in expression!" << std::endl;
    clearTree(root);
    cleanupStack(stack, stackTop - 1);
    delete[] stack;
    return false;
  }

  delete[] stack;
  tree.setRoot(root);
  return true;
}

ExpressionTree::TokenList
ExpressionTree::tokenize(const std::string &expression) const {
  TokenList tokens;
  std::string current;

  for (char c : expression) {
    if (std::isspace(c)) {
      if (!current.empty()) {
        tokens.addToken(current);
        current.clear();
      }
    } else if (c == '(' || c == ')' || isOperator(std::string(1, c))) {
      if (!current.empty()) {
        tokens.addToken(current);
        current.clear();
      }
      tokens.addToken(std::string(1, c));
    } else {
      current += c;
    }
  }

  if (!current.empty()) {
    tokens.addToken(current);
  }

  return tokens;
}

double ExpressionTree::evaluate() const { return evaluate(tree.getRoot()); }

void ExpressionTree::printTree() const {
  if (!tree.getRoot()) {
    std::cout << "Tree is empty!" << std::endl;
    return;
  }

  std::cout << "Expression tree: ";
  tree.inorderTraversal();
  std::cout << std::endl;
}