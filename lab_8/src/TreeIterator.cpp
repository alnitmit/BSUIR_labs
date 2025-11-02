#include "../include/TreeIterator.h"

template <typename T>
TreeIterator<T>::TreeIterator(TreeNode<T>* root) {
    pushLeft(root);
}

template <typename T>
void TreeIterator<T>::pushLeft(TreeNode<T>* node) {
    while (node) {
        stack.push(node);
        node = node->left;
    }
}

template <typename T>
T& TreeIterator<T>::operator*() {
    return stack.peek()->data;
}

template <typename T>
TreeIterator<T>& TreeIterator<T>::operator++() {
    TreeNode<T>* node = stack.peek()->right;
    stack.pop();
    pushLeft(node);
    return *this;
}

template <typename T>
bool TreeIterator<T>::operator!=(const TreeIterator& other) {
    return !stack.empty() || !other.stack.empty();
}

template class TreeIterator<int>;
template class TreeIterator<double>;