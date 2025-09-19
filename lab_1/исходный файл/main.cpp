#include "../заголовочный файл/Matrix.h"
#include <iostream>
#include <limits>

void fillMatrices(const Matrix &m1,const Matrix &m2) {
  int choice;
  bool validChoice = false;

  while (!validChoice) {
    std::cout << "Choose matrix input method:\n";
    std::cout << "1. Manual input\n";

    if (!(std::cin >> choice)) {
      std::cout << "Invalid input. Please enter a number (1).\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }

    if (choice == 1) {
      validChoice = true;
    } else {
      std::cout << "Invalid choice. Please select 1.\n";
    }
  }

  std::cout << "Enter values for matrix A:" << std::endl;
  m1.fillFromInput();
  std::cout << "Enter values for matrix B:" << std::endl;
  m2.fillFromInput();

  std::cout << "\nMatrix A:" << std::endl;
  m1.print();
  std::cout << "\nMatrix B:" << std::endl;
  m2.print();
}

void performMatrixOperations(const Matrix &m1, const Matrix &m2) {
  while (true) {
    std::cout << "\nChoose operation:\n";
    std::cout << "1. Addition\n";
    std::cout << "2. Multiplication\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";

    int opChoice;
    if (!(std::cin >> opChoice)) {
      std::cout << "Invalid input. Please enter a number (1-3).\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }

    std::cin.ignore(10000, '\n');

    if (opChoice == 1) {
      if (m1.getRows() == m2.getRows() && m1.getCols() == m2.getCols()) {
        Matrix sum = Matrix::addMatrices(m1, m2);
        std::cout << "\nSum of A and B:" << std::endl;
        sum.print();
      } else {
        std::cout << "Cannot add matrices - dimensions don't match"
                  << std::endl;
      }
    } else if (opChoice == 2) {
      if (m1.getCols() == m2.getRows()) {
        Matrix product = Matrix::multiplyMatrices(m1, m2);
        std::cout << "\nProduct of A and B:" << std::endl;
        product.print();
      } else {
        std::cout << "Cannot multiply matrices - dimensions incompatible"
                  << std::endl;
      }
    } else if (opChoice == 3) {
      std::cout << "Exiting program." << std::endl;
      break;
    } else {
      std::cout << "Invalid choice. Please enter 1, 2 or 3." << std::endl;
    }
  }
}

void matrixOperations() {
  int rows1;
  int cols1;
  int rows2;
  int cols2;
  bool validDimensions = false;

  while (!validDimensions) {
    std::cout << "Enter dimensions for first matrix (rows columns): ";

    if (!(std::cin >> rows1 >> cols1)) {
      std::cout << "Invalid input. Please enter two numbers.\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }

    std::cout << "Enter dimensions for second matrix (rows columns): ";

    if (!(std::cin >> rows2 >> cols2)) {
      std::cout << "Invalid input. Please enter two numbers.\n";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }

    if (rows1 <= 0 || cols1 <= 0 || rows2 <= 0 || cols2 <= 0) {
      std::cout
          << "Error: Matrix dimensions must be positive. Please try again.\n";
    } else {
      validDimensions = true;
    }
  }

  Matrix m1(rows1, cols1);
  Matrix m2(rows2, cols2);

  fillMatrices(m1, m2);
  performMatrixOperations(m1, m2);
}

int main() {
  matrixOperations();
  return 0;
}