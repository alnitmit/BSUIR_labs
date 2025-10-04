#ifndef TREENODE_H
#define TREENODE_H

template <typename T> class TreeNode {
public:
  T data;
  TreeNode *left;
  TreeNode *right;

  TreeNode(const T &value) : data(value), left(nullptr), right(nullptr) {}
};

#endif