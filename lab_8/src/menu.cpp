#include "../include/menu.h"
#include "../include/Algorithm.h"
#include "../include/Tree.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

template <typename T> T getInput(const char *msg) {
  T value;
  cout << msg;

  while (true) {
    if (cin >> value) {
      if (cin.get() == '\n') {
        return value;
      }
      cin.clear();
      while (cin.get() != '\n' && !cin.eof())
        ;
      cout << "Error, invalid input. Please try again: ";
    } else {
      cin.clear();
      while (cin.get() != '\n' && !cin.eof())
        ;
      cout << "Error, invalid input. Please try again: ";
    }
  }
}

void clearInputBuffer() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

template <typename T> void runProgram() {
  Tree<T> tree;
  Algorithm<T> alg;
  int choice;
  bool running = true;

  while (running) {
    cout << "\n=== Binary Tree Menu ===\n";
    cout << "1. Insert a value\n";
    cout << "2. Perform inorder traversal\n";
    cout << "3. Perform level order traversal\n";
    cout << "4. Search for a value\n";
    cout << "5. Exit\n";
    cout << "Enter your choice (1-5): ";
    cin >> choice;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
    case 1: {
      T value;
      cout << "Enter the value to insert: ";
      value = getInput<T>("");
      if (cin.fail()) {
        cout << "Invalid input. Please enter a valid value.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
      }
      tree.insert(value);
      cout << "Value " << value << " inserted successfully.\n";
      break;
    }
    case 2: {
      cout << "Inorder traversal result:\n";
      alg.inorderTraversal(tree.getRoot());
      break;
    }
    case 3: {
      cout << "Level order traversal result:\n";
      alg.levelOrderTraversal(tree.getRoot());
      break;
    }
    case 4: {
      T value;
      cout << "Enter the value to search: ";
      value = getInput<T>("");
      if (cin.fail()) {
        cout << "Invalid input. Please enter a valid value.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        break;
      }
      if (TreeNode<T> *found = alg.search(tree.getRoot(), value)) {
        cout << "Value " << value << " found in the tree.\n";
      } else {
        cout << "Value " << value << " not found in the tree.\n";
      }
      break;
    }
    case 5: {
      cout << "Exiting program.\n";
      running = false;
      break;
    }
    default: {
      cout << "Invalid choice. Please select a number between 1 and 5.\n";
      break;
    }
    }
  }
}

void menu() {
  bool programRunning = true;
  while (programRunning) {
    cout << "\n=== Data Type Selection ===\n";
    cout << "Select the data type for the binary tree:\n";
    cout << "1. Integer (int)\n";
    cout << "2. Double (double)\n";
    cout << "3. String (string)\n";
    cout << "4. Exit program\n";
    cout << "Enter your choice (1-4): ";
    int typeChoice;
    typeChoice = getInput<int>("");
    clearInputBuffer();
    switch (typeChoice) {
    case 1: {
      cout << "Starting binary tree with int data type.\n";
      runProgram<int>();
      break;
    }
    case 2: {
      cout << "Starting binary tree with double data type.\n";
      runProgram<double>();
      break;
    }
    case 3: {
      cout << "Starting binary tree with string data type.\n";
      runProgram<string>();
      break;
    }
    case 4: {
      cout << "Exiting program.\n";
      programRunning = false;
      break;
    }
    default: {
      cout << "Invalid choice. Please select a number between 1 and 4.\n";
      break;
    }
    }
  }
}