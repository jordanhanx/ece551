#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> *[numRows]) {
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(numColumns);
    }
  }
  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = new std::vector<T> *[numRows];
    for (int i = 0; i < numRows; i++) {
      rows[i] = new std::vector<T>(*rhs.rows[i]);
    }
  }
  ~Matrix() {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      std::vector<T> ** temp_rows = new std::vector<T> *[rhs.numRows];
      for (int i = 0; i < rhs.numRows; i++) {
        temp_rows[i] = new std::vector<T>(*rhs.rows[i]);
      }
      for (int j = 0; j < numRows; j++) {
        delete rows[j];
      }
      delete[] rows;
      rows = temp_rows;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
    }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert((index >= 0) && (index < numRows));
    return *rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert((index >= 0) && (index < numRows));
    return *rows[index];
  }
  bool operator==(const Matrix & rhs) const {
    if ((numRows != rhs.numRows) || (numColumns != rhs.numColumns)) {
      return false;
    }
    for (int i = 0; i < numRows; i++) {
      if (*rows[i] != *rhs.rows[i]) {
        return false;
      }
    }
    return true;
  }
  Matrix operator+(const Matrix & rhs) const {
    assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
    Matrix sum(numRows, numColumns);
    for (int r = 0; r < numRows; r++) {
      for (int c = 0; c < numColumns; c++) {
        (*sum.rows[r])[c] = (*rows[r])[c] + (*rhs.rows[r])[c];
      }
    }
    return sum;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  s << "[ ";
  for (int r = 0; r < rhs.getRows(); r++) {
    s << rhs[r];
    if (r != rhs.getRows() - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  s << "{";
  for (typename std::vector<T>::const_iterator it = rhs.begin(); it < rhs.end(); ++it) {
    if (it != rhs.begin()) {
      s << ", ";
    }
    s << *it;
  }
  s << "}";
  return s;
}
#endif
