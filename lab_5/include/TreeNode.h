#ifndef TREENODE_H
#define TREENODE_H

template <typename T> class TreeNode {
public:
  T data;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;

  explicit TreeNode(const T &value) : data(value) {}
};

#endif