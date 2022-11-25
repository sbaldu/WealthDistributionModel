#ifndef SparseMatrix_hpp
#define SparseMatrix_hpp

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

template <typename T> class SparseMatrix {
  std::unordered_map<int, T> ad_matrix = {};
  int net_rows = 0, net_cols = 0;
  static T constexpr defaultReturn = 0;

public:
  SparseMatrix() = default;
  SparseMatrix(int rows, int cols) {
    rows < 0 || cols < 0
        ? throw std::invalid_argument("SparseMatrix: rows and cols must be > 0")
        : net_rows = rows,
          net_cols = cols;
  };
  SparseMatrix(const char *fName) {
    std::ifstream file(fName);
    if (!file.is_open())
      throw std::invalid_argument("SparseMatrix: file not found");
    file >> net_rows >> net_cols;
    int pos;
    T value;
    while (file >> pos >> value) {
      if (pos < 0 || pos > (net_rows * net_cols) - 1)
        throw std::invalid_argument("SparseMatrix: index out of bounds");
      ad_matrix.insert({pos, value});
      std::cout << __LINE__ << '\t' << pos << '\t' << value << '\n';
    }

    file.close();
  }
  SparseMatrix(SparseMatrix const &other) {
    this->net_rows = other.net_rows;
    this->net_cols = other.net_cols;
    this->ad_matrix = other.ad_matrix;
  };

  std::unordered_map<int, T> const& getMatrix() { return ad_matrix; }

  void insert(int i, int j, T value) {
    if (i >= net_rows * net_cols || j >= net_rows * net_cols || i < 0 || j < 0) { // actually they should be contained in the triangule of the matrix
      throw std::out_of_range("Index out of range");
    }
    ad_matrix.emplace(std::make_pair(i * net_cols * net_rows + j, value));
  };
  void insert(int i, T value) {
    if (i >= net_rows * net_cols * net_rows * net_cols || i < 0) { // again, it should be contained in the upper triangule
      throw std::out_of_range("Index out of range");
    }
    ad_matrix.emplace(std::make_pair(i, value));
  };
  void insert_or_assign(int i, int j, T value) {
    if (i >= net_rows || j >= net_cols || i < 0 || j < 0) {
      throw std::out_of_range("Index out of range");
    }
    ad_matrix.insert_or_assign(i * net_cols + j, value);
  };
  void erase(int i, int j) {
    ad_matrix.find(i * net_cols + j) != ad_matrix.end()
        ? ad_matrix.erase(i * net_cols + j)
        : throw std::out_of_range("Index out of range");
  };
  void clear() noexcept { ad_matrix.clear(); };
  bool exists(int i, int j) const noexcept {
    return ad_matrix.count(i * net_cols * net_rows + j);
  };

  std::unordered_map<int, T> getRow(int index) const {
    if (index >= net_rows || index < 0) {
      throw std::out_of_range("Index out of range");
    }
    std::unordered_map<int, T> row;
    for (auto &it : ad_matrix) {
      if (it.first / net_cols == index) {
        row.emplace(std::make_pair(it.first % net_cols, it.second));
      }
    }
    return row;
  }
  std::unordered_map<int, T> getCol(int index) const {
    if (index >= net_cols || index < 0) {
      throw std::out_of_range("Index out of range");
    }
    std::unordered_map<int, T> col;
    for (auto &it : ad_matrix) {
      if (it.first % net_cols == index) {
        col.emplace(std::make_pair(it.first / net_cols, it.second));
      }
    }
    return col;
  }
  int getRowDim() const noexcept { return this->net_rows; };
  int getColDim() const noexcept { return this->net_cols; };
  int size() const noexcept { return this->net_rows * this->net_cols; };

  void print() const noexcept {
    for (int i = 0; i < net_rows; ++i) {
      for (int j = 0; j < net_cols; ++j) {
        auto const &it = ad_matrix.find(i * net_cols + j);
        it != ad_matrix.end() ? std::cout << it->second : std::cout << 0;
        std::cout << '\t';
      }
      std::cout << '\n';
    }
  }
  void save(const char *fName) const {
    std::ofstream file(fName);
    file << net_rows * net_cols << '\t' << net_rows * net_cols << '\n';
    for (auto const &it : ad_matrix) {
      file << it.first << '\t' << it.second << '\n';
    }
    file.close();
  }
  void saveAsMatrix(const char *fName) const {
    std::ofstream file(fName);
    for (int i = 0; i < net_rows; ++i) {
      for (int j = 0; j < net_cols; ++j) {
        auto const &it = ad_matrix.find(i * net_cols + j);
        it != ad_matrix.end() ? file << it->second : file << 0;
        file << '\t';
      }
      file << '\n';
    }
    file.close();
  }

  T const &operator()(int i, int j) {
    if (i >= net_rows || j >= net_cols || i < 0 || j < 0) {
      throw std::out_of_range("Index out of range");
    }
    auto const &it = ad_matrix.find(i * net_cols + j);
    return it != ad_matrix.end() ? it->second : defaultReturn;
  }
  SparseMatrix &operator=(const SparseMatrix &other) {
    this->net_rows = other.net_rows;
    this->net_cols = other.net_cols;
    this->ad_matrix = other.ad_matrix;
    return *this;
  }
};

#endif
