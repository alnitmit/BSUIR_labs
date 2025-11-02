#pragma once
#include <iostream>
#include "../include/Tree.h"

template <typename T>
class TreeAlgorithm {
public:
    static void inOrderTraversal(TreeNode<T>* root);
    static void iterativeInOrder(TreeNode<T>* root);
    static TreeNode<T>* search(TreeNode<T>* root, const T& value);
};