#ifndef SparseMatrix_hpp
#define SparseMatrix_hpp

#include <map>
#include <stdexcept>

class SparseMatrix {
    std::map<int, double> _matrix;
    int _rows, _cols;

    public:
    SparseMatrix(int, int);
    SparseMatrix(const SparseMatrix&);

    void insert(int , int , double );
    void erase(int , int );
    void clear();

    double& operator() (int i, int j) {
        if(i >= _rows || j >= _cols) {
            throw std::out_of_range("Index out of range");
        }
        return this->_matrix[i*_cols + j];
    }
};


#endif