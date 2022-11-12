#ifndef SparseMatrix_hpp
#define SparseMatrix_hpp

#include <map>
#include <stdexcept>
#include <iostream>
#include <fstream>

template <typename T> class SparseMatrix {
  std::map<int, T> _matrix;
  int _rows, _cols;

public:
  SparseMatrix(int rows, int cols) {
    this->_rows = rows;
    this->_cols = cols;
  };
  SparseMatrix(const SparseMatrix &other) {
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
  void erase(int i, int j) { _matrix.erase(i * _cols + j); };
  void clear() { _matrix.clear(); };

  std::map<int, T> getRow(int index) {
    std::map<int, T> row;
    for (auto &it : _matrix) {
      if (it.first / _cols == index) {
        row.insert(std::make_pair(it.first % _cols, it.second));
      }
    }
    return row;
  };
  std::map<int, T> getCol(int index) {
    std::map<int, T> col;
    for (auto &it : _matrix) {
      if (it.first % _cols == index) {
        col.insert(std::make_pair(it.first / _cols, it.second));
      }
    }
    return col;
  };

  void print() {
    for (int i = 0; i < _rows; ++i) {
      for (int j = 0; j < _cols; ++j) {
        std::cout << _matrix[i * _cols + j] << '\t';
      }
      std::cout << '\n';
    }
  };
  void save(const char* fName) {
    std::ofstream file(fName);
    for (int i = 0; i < _rows; ++i) {
      for (int j = 0; j < _cols; ++j) {
        file << _matrix[i * _cols + j] << '\t';
      }
      file << '\n';
    }
    file.close();
  };

  T &operator()(int i, int j) {
    if (i >= _rows || j >= _cols) {
      throw std::out_of_range("Index out of range");
    }
    return this->_matrix[i * _cols + j];
  }
};

#endif