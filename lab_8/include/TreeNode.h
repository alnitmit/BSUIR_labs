#ifndef LAB8_TREENODE_H
#define LAB8_TREENODE_H

template <typename T> class TreeNode {
public:
  T data;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
  explicit TreeNode(const T &value) : data(value) {}
};

#endif