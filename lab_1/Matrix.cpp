#include "Matrix.h"
#include <iostream>
#include <limits>

void Matrix::freeMemory() {
  if (data) {
    for (int i = 0; i < rows; ++i) {
      delete[] data[i];
    }
    delete[] data;
  }
}

void Matrix::allocateAndCopyData(const Matrix &other) {
  data = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    data[i] = new double[cols];
    for (int j = 0; j < cols; ++j) {
      data[i][j] = other.data[i][j];
    }
  }
}

Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
  if (rows <= 0 || cols <= 0) {
    std::cout << "Error: Matrix dimensions must be positive" << std::endl;
    this->rows = 0;
    this->cols = 0;
    data = nullptr;
    return;
  }

  data = new double *[rows];
  for (int i = 0; i < rows; ++i) {
    data[i] = new double[cols]();
  }
}

Matrix::Matrix(const Matrix &other)
    : rows(other.rows), cols(other.cols), data(nullptr) {
  if (rows > 0 && cols > 0) {
    data = new double *[rows];
    for (int i = 0; i < rows; ++i) {
      data[i] = new double[cols];
      for (int j = 0; j < cols; ++j) {
        data[i][j] = other.data[i][j];
      }
    }
  }
}

Matrix &Matrix::operator=(const Matrix &other) {
  if (this == &other) {
    return *this;
  }
  freeMemory();

  rows = other.rows;
  cols = other.cols;

  if (rows > 0 && cols > 0) {
    allocateAndCopyData(other);
  } else {
    data = nullptr;
  }

  return *this;
}

Matrix::~Matrix() { freeMemory(); }

int Matrix::getRows() const { return rows; }

int Matrix::getCols() const { return cols; }

void Matrix::setValue(int row, int col, double value) const {
  if (row < 0 || row >= rows || col < 0 || col >= cols) {
    std::cout << "Error: Matrix indices out of range" << std::endl;
    return;
  }
  data[row][col] = value;
}

double Matrix::getValue(int row, int col) const {
  if (row < 0 || row >= rows || col < 0 || col >= cols) {
    std::cout << "Error: Matrix indices out of range" << std::endl;
    return 0.0;
  }
  return data[row][col];
}

void Matrix::print() const {
  if (!data) {
    std::cout << "Matrix is not initialized" << std::endl;
    return;
  }

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      std::cout << data[i][j] << "\t";
    }
    std::cout << std::endl;
  }
}

void Matrix::fillFromInput() {
  if (!data)
    return;

  std::cout << "Enter " << rows << "x" << cols << " matrix values:" << std::endl;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      readAndSetElement(i, j);
    }
  }
}

void Matrix::readAndSetElement(int i, int j) const {
  double value;
  bool validInput = false;

  while (!validInput) {
    std::cout << "Element [" << i << "][" << j << "]: ";

    if (std::cin >> value) {
      data[i][j] = value;
      validInput = true;
    } else {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid input! Please enter a valid number." << std::endl;
    }
  }
}

Matrix Matrix::add(const Matrix &other) const {
  if (rows != other.rows || cols != other.cols) {
    std::cout << "Error: Matrices dimensions do not match for addition"
              << std::endl;
    return Matrix(0, 0);
  }

  Matrix result(rows, cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      result.data[i][j] = data[i][j] + other.data[i][j];
    }
  }
  return result;
}

Matrix Matrix::multiply(const Matrix &other) const {
  if (cols != other.rows) {
    std::cout << "Error: Matrices dimensions do not match for multiplication"
              << std::endl;
    return Matrix(0, 0);
  }

  Matrix result(rows, other.cols);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < other.cols; ++j) {
      double sum = 0;
      for (int k = 0; k < cols; ++k) {
        sum += data[i][k] * other.data[k][j];
      }
      result.data[i][j] = sum;
    }
  }
  return result;
}

Matrix Matrix::addMatrices(const Matrix &a, const Matrix &b) {
  return a.add(b);
}

Matrix Matrix::multiplyMatrices(const Matrix &a, const Matrix &b) {
  return a.multiply(b);
}