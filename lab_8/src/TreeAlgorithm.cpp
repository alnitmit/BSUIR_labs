#include "../include/TreeAlgorithm.h"
#include "../include/Stack.h"

template <typename T>
void TreeAlgorithm<T>::inOrderTraversal(TreeNode<T>* root) {
    if (root) {
        inOrderTraversal(root->left);
        std::cout << root->data << " ";
        inOrderTraversal(root->right);
    }
}

template <typename T>
void TreeAlgorithm<T>::iterativeInOrder(TreeNode<T>* root) {
    Stack<TreeNode<T>*> stack;
    TreeNode<T>* current = root;
    
    while (current || !stack.empty()) {
        while (current) {
            stack.push(current);
            current = current->left;
        }
        
        current = stack.peek();
        stack.pop();
        std::cout << current->data << " ";
        current = current->right;
    }
}

template <typename T>
TreeNode<T>* TreeAlgorithm<T>::search(TreeNode<T>* root, const T& value) {
    TreeNode<T>* current = root;
    while (current) {
        if (value == current->data)
            return current;
        else if (value < current->data)
            current = current->left;
        else
            current = current->right;
    }
    return nullptr;
}

template class TreeAlgorithm<int>;
template class TreeAlgorithm<double>;