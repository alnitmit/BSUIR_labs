#ifndef LAB8_ITERATOR_H
#define LAB8_ITERATOR_H

#include "Tree.h"
#include <stack>

template <typename T> class Iterator {
private:
  std::stack<TreeNode<T> *> stk;
  TreeNode<T> *current;

  void pushLeft(TreeNode<T> *node) {
    while (node) {
      stk.push(node);
      node = node->left;
    }
  }

public:
  explicit Iterator(TreeNode<T> *root) {
    pushLeft(root);
    if (!stk.empty()) {
      current = stk.top();
      stk.pop();
    } else {
      current = nullptr;
    }
  }

  Iterator() : current(nullptr) {}

  T &operator*() { return current->data; }

  Iterator &operator++() {
    if (current) {
      pushLeft(current->right);
      if (!stk.empty()) {
        current = stk.top();
        stk.pop();
      } else {
        current = nullptr;
      }
    }
    return *this;
  }

  bool operator!=(const Iterator &other) const {
    return current != other.current;
  }
};

// Определения методов Tree после определения Iterator
template <typename T> Iterator<T> Tree<T>::begin() { return Iterator<T>(root); }

template <typename T> Iterator<T> Tree<T>::end() { return Iterator<T>(); }

#endif