#include "../include/Tree.h"

template <typename T>
Tree<T>::Tree() : root(nullptr) {}

template <typename T>
Tree<T>::~Tree() {
    clear(root);
}

template <typename T>
void Tree<T>::clear(TreeNode<T>* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename T>
TreeNode<T>* Tree<T>::insert(TreeNode<T>* node, const T& value) {
    if (!node) return new TreeNode<T>(value);
    
    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    
    return node;
}

template <typename T>
void Tree<T>::insert(const T& value) {
    root = insert(root, value);
}

template <typename T>
void Tree<T>::printInOrder(TreeNode<T>* node) {
    if (node) {
        printInOrder(node->left);
        std::cout << node->data << " ";
        printInOrder(node->right);
    }
}

template <typename T>
void Tree<T>::print() {
    std::cout << "Tree elements: ";
    printInOrder(root);
    std::cout << std::endl;
}

template <typename T>
bool Tree<T>::search(const T& value) {
    TreeNode<T>* current = root;
    while (current) {
        if (value == current->data)
            return true;
        else if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

template <typename T>
TreeIterator<T> Tree<T>::begin() {
    return TreeIterator<T>(root);
}

template <typename T>
TreeIterator<T> Tree<T>::end() {
    return TreeIterator<T>(nullptr);
}

template <typename T>
TreeNode<T>* Tree<T>::getRoot() {
    return root;
}

template class Tree<int>;
template class Tree<double>;