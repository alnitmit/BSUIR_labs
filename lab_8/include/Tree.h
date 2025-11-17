#ifndef LAB8_TREE_H
#define LAB8_TREE_H

#include "TreeNode.h"
#include <functional>
#include <iostream>

template <typename T> class Iterator;

template <typename T> class Tree {
private:
  TreeNode<T> *root = nullptr;

  void deleteNode(TreeNode<T> *node) {
    if (node) {
      deleteNode(node->left);
      deleteNode(node->right);
      delete node;
    }
  }

  TreeNode<T> *copyTree(TreeNode<T> *node) {
    if (!node)
      return nullptr;
    auto *newNode = new TreeNode<T>(node->data);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
  }

public:
  Tree() = default;
  ~Tree() { deleteNode(root); }

  Tree(const Tree &other) {
    if (other.root) {
      root = copyTree(other.root);
    }
  }

  Tree &operator=(const Tree &other) {
    if (this != &other) {
      Tree temp(other);
      std::swap(root, temp.root);
    }
    return *this;
  }

  void insert(const T &value) {
    if (!root) {
      root = new TreeNode<T>(value);
      return;
    }
    TreeNode<T> *current = root;
    while (true) {
      if (value < current->data) {
        if (!current->left) {
          current->left = new TreeNode<T>(value);
          return;
        }
        current = current->left;
      } else {
        if (!current->right) {
          current->right = new TreeNode<T>(value);
          return;
        }
        current = current->right;
      }
    }
  }

  TreeNode<T> *getRoot() const { return root; }

  Iterator<T> begin();
  Iterator<T> end();
};

#endif