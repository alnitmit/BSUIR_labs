#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include <iostream>

template <typename T> class Tree {
private:
  TreeNode<T> *root;

  void clear(TreeNode<T> *node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  void inorder(TreeNode<T> *node, void (*callback)(const T &)) const {
    if (!node)
      return;
    inorder(node->left, callback);
    callback(node->data);
    inorder(node->right, callback);
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
  Tree() : root(nullptr) {}

  ~Tree() { clear(root); }

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

  void inorderTraversal(void (*callback)(const T &)) const {
    inorder(root, callback);
  }

  bool contains(const T &value) const { return find(root, value) != nullptr; }

  TreeNode<T> *getRoot() const { return root; }

  void setRoot(TreeNode<T> *newRoot) { root = newRoot; }
};

#endif