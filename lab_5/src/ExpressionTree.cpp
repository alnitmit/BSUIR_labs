#include "../include/ExpressionTree.h"
#include <cctype>
#include <functional>
#include <iostream>


void clearTree(TreeNode<std::string> *node) {
  if (!node)
    return;
  clearTree(node->left);
  clearTree(node->right);
  delete node;
}

void printString(const std::string &str) { std::cout << str << " "; }

void printInt(const int &value) { std::cout << value << " "; }

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

  result = processIntegerPart(str, i, hasFraction);

  if (hasFraction) {
    fraction = processFractionalPart(str, i, divisor);
  }

  result += fraction / divisor;
  return negative ? -result : result;
}

double ExpressionTree::processIntegerPart(const char *str, int &index,
                                          bool &hasFraction) const {
  double result = 0.0;

  while (str[index] != '\0' && str[index] != '.') {
    if (std::isdigit(str[index])) {
      result = result * 10 + (str[index] - '0');
    }
    index++;
  }

  if (str[index] == '.') {
    hasFraction = true;
    index++;
  }

  return result;
}

double ExpressionTree::processFractionalPart(const char *str, int &index,
                                             double &divisor) const {
  double fraction = 0.0;

  while (str[index] != '\0') {
    if (std::isdigit(str[index])) {
      fraction = fraction * 10 + (str[index] - '0');
      divisor *= 10;
    }
    index++;
  }

  return fraction;
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
    return handleDivision(left, right);
  }

  std::cout << "Error: Unknown operator: " << node->data << std::endl;
  return 0.0;
}

double ExpressionTree::handleDivision(double left, double right) const {
  if (right == 0) {
    std::cout << "Error: Division by zero!" << std::endl;
    return 0.0;
  }
  return left / right;
}

class SimpleStack {
private:
  struct Node {
    std::string data;
    Node *next = nullptr;
    explicit Node(const std::string &value) : data(value) {}
  };

  Node *topNode = nullptr;
  SimpleStack(const SimpleStack &) = delete;
  SimpleStack &operator=(const SimpleStack &) = delete;

public:
  SimpleStack() = default;

  SimpleStack(SimpleStack &&other) noexcept : topNode(other.topNode) {
    other.topNode = nullptr;
  }

  SimpleStack &operator=(SimpleStack &&other) noexcept {
    if (this != &other) {
      while (!empty()) {
        pop();
      }
      topNode = other.topNode;
      other.topNode = nullptr;
    }
    return *this;
  }

  ~SimpleStack() {
    while (!empty()) {
      pop();
    }
  }

  void push(const std::string &value) {
    auto newNode = new Node(value);
    newNode->next = topNode;
    topNode = newNode;
  }

  void pop() {
    if (topNode) {
      Node *temp = topNode;
      topNode = topNode->next;
      delete temp;
    }
  }

  std::string &top() { return topNode->data; }

  const std::string &top() const { return topNode->data; }

  bool empty() const { return topNode == nullptr; }
};

void ExpressionTree::infixToPostfix(const TokenList &infix,
                                    TokenList &postfix) const {
  SimpleStack operators;

  for (int i = 0; i < infix.count; i++) {
    const std::string &token = infix.tokens[i];
    if (token == "(") {
      operators.push(token);
    } else if (token == ")") {
      while (!operators.empty() && operators.top() != "(") {
        postfix.addToken(operators.top());
        operators.pop();
      }
      if (operators.empty()) {
        std::cout << "Error: Mismatched parentheses!" << std::endl;
        return;
      }
      operators.pop();
    } else if (isOperator(token)) {
      while (!operators.empty() && operators.top() != "(" &&
             getPriority(operators.top()) >= getPriority(token)) {
        postfix.addToken(operators.top());
        operators.pop();
      }
      operators.push(token);
    } else {
      postfix.addToken(token);
    }
  }

  while (!operators.empty()) {
    if (operators.top() == "(") {
      std::cout << "Error: Mismatched parentheses!" << std::endl;
      return;
    }
    postfix.addToken(operators.top());
    operators.pop();
  }
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

bool ExpressionTree::buildTreeFromPostfix(const TokenList &postfix) {
  struct StackNode {
    TreeNode<std::string> *treeNode;
    StackNode *next = nullptr;
    explicit StackNode(TreeNode<std::string> *node) : treeNode(node) {}
  };

  StackNode *stackTop = nullptr;

  auto push = [&stackTop](TreeNode<std::string> *node) {
    auto newNode = new StackNode(node);
    newNode->next = stackTop;
    stackTop = newNode;
  };

  auto pop = [&stackTop]() -> TreeNode<std::string> * {
    if (!stackTop)
      return nullptr;
    StackNode *temp = stackTop;
    TreeNode<std::string> *node = temp->treeNode;
    stackTop = stackTop->next;
    delete temp;
    return node;
  };

  auto cleanup = [&]() {
    while (stackTop) {
      clearTree(pop());
    }
  };

  for (int i = 0; i < postfix.count; i++) {
    const std::string &token = postfix.tokens[i];
    auto node = new TreeNode<std::string>(token);

    if (isOperator(token)) {
      node->right = pop();
      node->left = pop();

      if (!node->left || !node->right) {
        std::cout << "Error: Not enough operands for operator: " << token
                  << std::endl;
        clearTree(node);
        cleanup();
        return false;
      }
    }

    push(node);
  }

  TreeNode<std::string> *root = pop();
  if (stackTop != nullptr) {
    std::cout << "Error: Too many operands in expression!" << std::endl;
    clearTree(root);
    cleanup();
    return false;
  }

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
  tree.inorderTraversal(printString);
  std::cout << std::endl;
}