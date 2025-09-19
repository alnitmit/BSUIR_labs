#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
  int rows;
  int cols;
  double **data;

  void freeMemory();
  void allocateAndCopyData(const Matrix &other);

public:
  Matrix(int rows, int cols);
  Matrix(const Matrix &other);
  Matrix &operator=(const Matrix &other);
  ~Matrix();

  int getRows() const;
  int getCols() const;
  void setValue(int row, int col, double value) const;
  double getValue(int row, int col) const;
  void print() const;
  void fillFromInput() const;
  void readAndSetElement(int i, int j) const;

  Matrix add(const Matrix &other) const;
  Matrix multiply(const Matrix &other) const;

  static Matrix addMatrices(const Matrix &a, const Matrix &b);
  static Matrix multiplyMatrices(const Matrix &a, const Matrix &b);
};

#endif