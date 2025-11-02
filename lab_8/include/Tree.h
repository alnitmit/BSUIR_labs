#pragma once
#include <iostream>
#include "../include/TreeNode.h"
#include "../include/TreeIterator.h"

template <typename T>
class Tree {
private:
    TreeNode<T>* root;
    void clear(TreeNode<T>* node);
    TreeNode<T>* insert(TreeNode<T>* node, const T& value);
    void printInOrder(TreeNode<T>* node);

public:
    Tree();
    ~Tree();
    void insert(const T& value);
    void print();
    bool search(const T& value);
    TreeIterator<T> begin();
    TreeIterator<T> end();
    TreeNode<T>* getRoot();
};