#include <iostream>
#include "../include/Tree.h"
#include "../include/TreeAlgorithm.h"

using namespace std;

void displayMenu() {
    cout << "\n=== Binary Tree Menu ===" << endl;
    cout << "1. Insert element" << endl;
    cout << "2. Print tree (recursive in-order)" << endl;
    cout << "3. Search element" << endl;
    cout << "4. Print using iterator" << endl;
    cout << "5. Use recursive algorithm traversal" << endl;
    cout << "6. Use iterative algorithm traversal" << endl;
    cout << "7. Use algorithm search" << endl;
    cout << "8. Exit" << endl;
    cout << "Choose option: ";
}

int main() {
    Tree<int> tree;
    int choice, value;
    
    do {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                cout << "Value " << value << " inserted." << endl;
                break;
                
            case 2:
                tree.print();
                break;
                
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (tree.search(value)) {
                    cout << "Value " << value << " found in tree." << endl;
                } else {
                    cout << "Value " << value << " not found in tree." << endl;
                }
                break;
                
            case 4:
                cout << "Tree elements using iterator: ";
                for (auto it = tree.begin(); it != tree.end(); ++it) {
                    cout << *it << " ";
                }
                cout << endl;
                break;
                
            case 5:
                cout << "Recursive algorithm in-order traversal: ";
                TreeAlgorithm<int>::inOrderTraversal(tree.getRoot());
                cout << endl;
                break;
                
            case 6:
                cout << "Iterative algorithm in-order traversal: ";
                TreeAlgorithm<int>::iterativeInOrder(tree.getRoot());
                cout << endl;
                break;
                
            case 7:
                cout << "Enter value to search with algorithm: ";
                cin >> value;
                if (TreeAlgorithm<int>::search(tree.getRoot(), value)) {
                    cout << "Value " << value << " found using algorithm." << endl;
                } else {
                    cout << "Value " << value << " not found using algorithm." << endl;
                }
                break;
                
            case 8:
                cout << "Exiting program." << endl;
                break;
                
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);
    
    return 0;
}