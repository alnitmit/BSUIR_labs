#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include <iostream>
#include <utility>
#include <functional>

template <typename T> class Tree {
private:
  TreeNode<T> *root = nullptr;

  void clear(TreeNode<T> *node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  TreeNode<T>* clone(TreeNode<T>* node) const {
    if (!node) return nullptr;
    auto newNode = new TreeNode<T>(node->data);
    newNode->left = clone(node->left);
    newNode->right = clone(node->right);
    return newNode;
  }

  template<typename Callback>
  void inorder(TreeNode<T> *node, Callback&& callback) const {
    if (!node)
      return;
    inorder(node->left, std::forward<Callback>(callback));
    callback(node->data);
    inorder(node->right, std::forward<Callback>(callback));
  }

  TreeNode<T> *find(TreeNode<T> *node, const T &value) const {
    if (!node)
      return nullptr;
    if (node->data == value)
      return node;

    TreeNode<T> *leftResult = find(node->left, value);
    if (leftResult)
      return leftResult;

    return find(node->right, value);
  }

  bool addRecursive(TreeNode<T> *node, const T &value, int level) {
    if (level == 1) {
      if (!node->left) {
        node->left = new TreeNode<T>(value);
        return true;
      }
      if (!node->right) {
        node->right = new TreeNode<T>(value);
        return true;
      }
      return false;
    }

    if (node->left && addRecursive(node->left, value, level - 1)) {
      return true;
    }
    if (node->right && addRecursive(node->right, value, level - 1)) {
      return true;
    }
    return false;
  }

  int getDepth(TreeNode<T> *node) const {
    if (!node)
      return 0;
    int leftDepth = getDepth(node->left);
    int rightDepth = getDepth(node->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
  }

public:
  Tree() = default;

  Tree(const Tree& other) : root(clone(other.root)) {}

  Tree& operator=(Tree other) {
    swap(*this, other);
    return *this;
  }

  Tree(Tree&& other) noexcept : root(nullptr) {
    swap(*this, other);
  }

  Tree& operator=(Tree&& other) noexcept {
    if (this != &other) {
      clear(root);
      root = other.root;
      other.root = nullptr;
    }
    return *this;
  }

  ~Tree() { clear(root); }

  friend void swap(Tree& first, Tree& second) noexcept {
    using std::swap;
    swap(first.root, second.root);
  }

  void add(const T &value) {
    if (!root) {
      root = new TreeNode<T>(value);
      return;
    }

    int depth = getDepth(root);
    for (int level = 1; level <= depth; level++) {
      if (addRecursive(root, value, level)) {
        return;
      }
    }

    TreeNode<T> *current = root;
    while (current->left) {
      current = current->left;
    }
    current->left = new TreeNode<T>(value);
  }

  template<typename Callback>
  void inorderTraversal(Callback&& callback) const {
    inorder(root, std::forward<Callback>(callback));
  }

  bool contains(const T &value) const { return find(root, value) != nullptr; }

  TreeNode<T> *getRoot() const { return root; }

  void setRoot(TreeNode<T> *newRoot) { 
    clear(root);
    root = newRoot; 
  }
};

#endif