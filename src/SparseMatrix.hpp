#ifndef SparseMatrix_hpp
#define SparseMatrix_hpp

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <stdexcept>

template <typename T> class SparseMatrix {
  std::unordered_map<int, T> _matrix = {};
  int _rows, _cols;

public:
  SparseMatrix() = default;
  SparseMatrix(int rows, int cols) {
    this->_rows = rows;
    this->_cols = cols;
  };
  SparseMatrix(SparseMatrix const &other) {
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
    if (i >= _rows * _cols) {
      throw std::out_of_range("Index out of range");
    }
    _matrix.insert(std::make_pair(i, value));
  };
  void erase(int i, int j) { _matrix.erase(i * _cols + j); };
  void clear() noexcept { _matrix.clear(); };
  bool exists(int i, int j) const {
    return _matrix.count(i * _cols + j);
  };

  std::unordered_map<int, T> getRow(int index) {
    std::unordered_map<int, T> row;
    for (auto &it : _matrix) {
      if (it.first / _cols == index) {
        row.insert(std::make_pair(it.first % _cols, it.second));
      }
    }
    return row;
  }
  std::unordered_map<int, T> getCol(int index) {
    std::unordered_map<int, T> col;
    for (auto &it : _matrix) {
      if (it.first % _cols == index) {
        col.insert(std::make_pair(it.first / _cols, it.second));
      }
    }
    return col;
  }
  int getRowDim() const noexcept { return this->_rows; };
  int getColDim() const noexcept { return this->_cols; };
  int getDim() const noexcept { return this->_rows * this->_cols; };

  void print() noexcept {
    for (int i = 0; i < _rows; ++i) {
      for (int j = 0; j < _cols; ++j) {
        _matrix.count(i * _cols + j) ? std::cout << _matrix[i * _cols + j] : std::cout << 0;
        std::cout << '\t';
      }
      std::cout << '\n';
    }
  }
  void save(const char *fName) {
    std::ofstream file(fName);
    for (int i = 0; i < _rows; ++i) {
      for (int j = 0; j < _cols; ++j) {
        _matrix.count(i * _cols + j) ? file << _matrix[i * _cols + j] : file << 0;
        file << '\t';
      }
      file << '\n';
    }
    file.close();
  }

  T operator()(int i, int j) {
    if (i >= _rows || j >= _cols) {
      throw std::out_of_range("Index out of range");
    }
    if(_matrix.count(i * _cols + j)) {
        return _matrix.at(i * _cols + j);
    } else {
        return static_cast<T>(0);
    }
  }
  SparseMatrix &operator=(const SparseMatrix &other) {
    this->_rows = other._rows;
    this->_cols = other._cols;
    this->_matrix = other._matrix;
    return *this;
  }
};

#endif