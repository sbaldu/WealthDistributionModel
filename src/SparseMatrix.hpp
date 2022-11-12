#ifndef SparseMatrix_hpp
#define SparseMatrix_hpp

#include <map>
#include <stdexcept>
#include <iostream>

template <typename T> 
class SparseMatrix {
  std::map<int, T> _matrix;
  int _rows, _cols;

public:
  SparseMatrix(int rows, int cols) {
    this->_rows = rows;
    this->_cols = cols;
  };
  SparseMatrix(SparseMatrix const& other) {
    this->_rows = other._rows;
    this->_cols = other._cols;
    this->_matrix = other._matrix;
  };

  void insert(int i, int j, T value) {
    if (i >= _rows || j >= _cols) {
      throw std::out_of_range("Index out of range");
    }
    _matrix.insert(std::make_pair(i * _cols + j, value));
  };
  void insert(int i, T value) {
    if(i >= _rows*_cols) {
      throw std::out_of_range("Index out of range");
    }
    _matrix.insert(std::make_pair(i, value));
  };
  void erase(int i, int j) { _matrix.erase(i * _cols + j); };
  void clear() { _matrix.clear(); };
  void print() {
    for (int i = 0; i < _rows; ++i) {
      for (int j = 0; j < _cols; ++j) {
        std::cout << _matrix[i * _cols + j] << '\t';
      }
      std::cout << '\n';
    }
  };

  T &operator()(int i, int j) {
    if (i >= _rows || j >= _cols) {
      throw std::out_of_range("Index out of range");
    }
    return this->_matrix[i * _cols + j];
  }
};

#endif
