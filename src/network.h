#ifndef NETWORK_H
#define NETWORK_H

#include "SparseMatrix.hpp"
#include <cstdint>
#include <map>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <utility>
#include <vector>

class network {
  uint16_t rows_, cols_, cass_ = 0, initCap_;
  std::vector<uint16_t> players_, poors_;  // array that contains all the players in the network
  SparseMatrix<bool> adjacencyMatrix_;
  SparseMatrix<int> nLinks_;

public:
  network(uint16_t, uint16_t, uint16_t);
  uint16_t getRows() const;
  uint16_t getCols() const;
  std::vector<uint16_t> const& players();
  std::vector<uint16_t> const& getPoors();
  uint16_t couples(uint16_t);

  void createLinks(uint8_t);
  void importMatrix(std::string const&);
  bool exists(int, int);
  bool isPoor(uint16_t);
  void printMatrix();
  void evolveUniform();
  void evolvePrefAtt();
  void evolvePrefAttNoTax();
  void evolveFixed();
  void evolvebyLink();
  void flatTax(uint8_t);
  float checkPoor(uint16_t);
  std::pair<float, float> calcProb(std::vector<uint16_t> const&);
  void print() const;
  void fprintHist() const noexcept;
  void fprintHist(uint8_t) const noexcept;
  void saveMatrix(std::string const&) const;
};

#endif
