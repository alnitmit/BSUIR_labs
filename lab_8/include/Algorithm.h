#ifndef LAB8_ALGORITHM_H
#define LAB8_ALGORITHM_H

#include "Tree.h"
#include <iostream>
#include <queue>
#include <stack>
#include <string>

template <typename T> class Algorithm {
public:
  void inorderTraversal(TreeNode<T> *root) const {
    if (!root)
      return;
    std::stack<TreeNode<T> *> stk;
    TreeNode<T> *current = root;
    while (current || !stk.empty()) {
      while (current) {
        stk.push(current);
        current = current->left;
      }
      current = stk.top();
      stk.pop();
      std::cout << current->data << " ";
      current = current->right;
    }
    std::cout << std::endl;
  }

  void levelOrderTraversal(TreeNode<T> *root) const {
    if (!root)
      return;
    std::queue<TreeNode<T> *> q;
    q.push(root);
    while (!q.empty()) {
      TreeNode<T> *node = q.front();
      q.pop();
      std::cout << node->data << " ";
      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
    }
    std::cout << std::endl;
  }

  TreeNode<T> *search(TreeNode<T> *root, const T &value) {
    if (!root)
      return nullptr;
    std::queue<TreeNode<T> *> q;
    q.push(root);
    while (!q.empty()) {
      TreeNode<T> *node = q.front();
      q.pop();
      if (node->data == value)
        return node;
      if (node->left)
        q.push(node->left);
      if (node->right)
        q.push(node->right);
    }
    return nullptr;
  }
};

#endif