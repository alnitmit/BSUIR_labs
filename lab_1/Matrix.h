#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

class Matrix {
private:
  int rows;
  int cols;
  double **data;

  void freeMemory() {
    if (data) {
      for (int i = 0; i < rows; ++i) {
        delete[] data[i];
      }
      delete[] data;
    }
  }

  void allocateAndCopyData(const Matrix &other) {
    data = new double *[rows];
    for (int i = 0; i < rows; ++i) {
      data[i] = new double[cols];
      copyRow(other, i);
    }
  }

  void copyRow(const Matrix &other, int rowIndex) const {
    for (int j = 0; j < cols; ++j) {
      data[rowIndex][j] = other.data[rowIndex][j];
    }
  }

public:
  Matrix(int rows, int cols) : rows(rows), cols(cols) {
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

  Matrix(const Matrix &other)
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

  Matrix &operator=(const Matrix &other) {
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

  ~Matrix() {
    if (data) {
      for (int i = 0; i < rows; ++i) {
        delete[] data[i];
      }
      delete[] data;
    }
  }

  int getRows() const { return rows; }
  int getCols() const { return cols; }

  void setValue(int row, int col, double value) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
      std::cout << "Error: Matrix indices out of range" << std::endl;
      return;
    }
    data[row][col] = value;
  }

  double getValue(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
      std::cout << "Error: Matrix indices out of range" << std::endl;
      return 0.0;
    }
    return data[row][col];
  }

  void print() const {
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

  void fillFromInput() const {
    if (!data)
      return;

    std::cout << "Enter " << rows << "x" << cols
              << " matrix values:" << std::endl;
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        std::cout << "Element [" << i << "][" << j << "]: ";
        std::cin >> data[i][j];
      }
    }
  }
};

Matrix addMatrices(const Matrix &a, const Matrix &b);
Matrix multiplyMatrices(const Matrix &a, const Matrix &b);
void matrixOperations();

#endif