#include "../include/ExpressionTree.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void displayMenu() {
  cout << "\n\tArithmetic Expression Calculator" << endl;
  cout << "1. Enter expression" << endl;
  cout << "2. Evaluate expression" << endl;
  cout << "3. Show tree" << endl;
  cout << "4. Demo with integers" << endl;
  cout << "5. Exit" << endl;
  cout << "Choose an option: ";
}

void clearInput() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void demoIntTree() {
  cout << "\n\tInteger Tree Demo" << endl;
  Tree<int> intTree;

  intTree.add(5);
  intTree.add(3);
  intTree.add(7);
  intTree.add(2);
  intTree.add(4);
  intTree.add(6);
  intTree.add(8);

  cout << "Inorder traversal: ";
  intTree.inorderTraversal(printInt);
  cout << endl;

  cout << "Search for 5: " << (intTree.contains(5) ? "found" : "not found")
       << endl;
  cout << "Search for 10: " << (intTree.contains(10) ? "found" : "not found")
       << endl;
}

int main() {
  ExpressionTree exprTree;
  string expression;
  int choice = 0;
  bool expressionBuilt = false;

  do {
    displayMenu();

    if (!(cin >> choice)) {
      cout << "Error: Please enter a valid integer!" << endl;
      clearInput();
      continue;
    }
    clearInput();

    switch (choice) {
    case 1: {
      cout << "Enter arithmetic expression: ";
      getline(cin, expression);
      if (expression.empty()) {
        cout << "Error: Empty expression!" << endl;
        break;
      }
      expressionBuilt = exprTree.buildFromExpression(expression);
      break;
    }

    case 2: {
      if (!expressionBuilt) {
        cout << "Error: No expression built yet. Please enter an expression "
                "first."
             << endl;
        break;
      }
      double result = exprTree.evaluate();
      cout << "Result: " << result << endl;
      break;
    }

    case 3: {
      if (!expressionBuilt) {
        cout << "Error: No expression built yet. Please enter an expression "
                "first."
             << endl;
        break;
      }
      exprTree.printTree();
      break;
    }

    case 4: {
      demoIntTree();
      break;
    }

    case 5: {
      cout << "Exiting program." << endl;
      break;
    }

    default: {
      cout << "Invalid choice. Please try again." << endl;
      break;
    }
    }

  } while (choice != 5);

  return 0;
}