#pragma once
#include "../include/TreeNode.h"
#include "../include/Stack.h"

template <typename T>
class TreeIterator {
private:
    Stack<TreeNode<T>*> stack;
    void pushLeft(TreeNode<T>* node);

public:
    TreeIterator(TreeNode<T>* root);
    T& operator*();
    TreeIterator& operator++();
    bool operator!=(const TreeIterator& other);
};