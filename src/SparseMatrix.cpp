#include "SparseMatrix.hpp"
#include <stdexcept>

SparseMatrix::SparseMatrix(int rows, int cols) {
    this->_rows = rows;
    this->_cols = cols;
}
SparseMatrix::SparseMatrix(const SparseMatrix& other) {
    this->_rows = other._rows;
    this->_cols = other._cols;
    this->_matrix = other._matrix;
}

void SparseMatrix::insert(int i, int j, double value) {
    if(i >= _rows || j >= _cols) {
            throw std::out_of_range("Index out of range");
        }
    _matrix.insert(std::make_pair(i*_cols + j, value));
}
void SparseMatrix::erase(int i, int j) {
    _matrix.erase(i*_cols + j);
}
void SparseMatrix::clear() {
    _matrix.clear();
}