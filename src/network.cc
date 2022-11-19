#include "network.h"
#include "SparseMatrix.hpp"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

std::random_device globalRndDev;
std::mt19937 globalRNG(globalRndDev());

network::network(uint16_t initialCapital, uint16_t rows, uint16_t cols)
    : adjacencyMatrix_(rows, cols) {
  rows_ = rows;
  cols_ = cols;
  std::vector<uint16_t> vec(rows_ * cols_);
  for (auto &i : vec) {
    i = initialCapital;
  }
  players_ = vec;
}

std::vector<uint16_t> const network::getPlayers() { return players_; }
Matrix const network::getAdjacency() { return adjacencyMatrix_; }

std::vector<uint16_t> const network::playersMoney() {
  std::vector<uint16_t> money;
  for (auto const &p : players_) {
    money.push_back(p);
  }
  return money;
}
/* std::vector<uint16_t> const */
/* network::playersMoney(std::vector<uint16_t> const &vec) { */
/*   std::vector<uint16_t> money; */
/*   for (auto const &p : vec) { */
/*     money.push_back(p); */
/*   } */
/*   return money; */
/* } */

uint16_t network::couples(uint16_t first) {
  auto dist = std::uniform_int_distribution<uint16_t>(
      0, rows_ * cols_ - 1); // second player is chosen randomly
  uint16_t second = 0;
  uint16_t rnd = dist(globalRNG);
  if (rnd != first) {
    second = rnd;
  }
  return second;
}

void network::createLinks() {
  float prob = 4. / (cols_ * rows_);
  float r = (float)(std::rand()) / (float)(RAND_MAX);
  /* std::uniform_int_distribution<std::mt19937::result_type> link(0, 1); */
  for (int i = 0; i < rows_ * cols_ - 1; ++i) {
    for (int j = i + 1; j < rows_ * cols_; ++j) {
      if (r < prob) {
        adjacencyMatrix_.insert(i, j, true);
      }
    }
  }
}

bool network::exists(int i, int j) {
  if (j >= i) {
    return adjacencyMatrix_.exists(i, j);
  } else {
    return adjacencyMatrix_.exists(j, i);
  }
}

void network::evolveUniform() {
  uint16_t first =
      std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ - 1)(globalRNG);
  std::uniform_int_distribution<std::mt19937::result_type> coin(0, 1);
  uint16_t other = couples(first);
  if (coin(globalRNG) && players_[other] > 0) {
    ++players_[first];
    --players_[other];
  } else if (players_[first] > 0) {
    --players_[first];
    ++players_[other];
  }
}

void network::evolvePrefAtt() {
  uint16_t first =
      std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ - 1)(globalRNG);
  uint16_t other = couples(first);
  float prob = (float)((players_[first])) / (players_[first] + players_[other]);
  if (std::bernoulli_distribution(prob)(globalRNG) && players_[other] > 0) {
    ++players_[first];
    --players_[other];
  } else if (players_[first] > 0) {
    --players_[first];
    ++players_[other];
  }
}

void network::flatTax(uint8_t percentage) {
  for (auto &i : players_) {
    int tax = i * percentage / 100;
    if (!(i < tax)) {
      i -= tax;
    }
  }
}

void network::print() const noexcept {
  int i = 0;
  for (auto const &player : players_) {
    std::cout << player << '\t';
    ++i;
    if (i % cols_ == 0) {
      std::cout << '\n';
      i = 0;
    }
  }
}

void network::fprintHist() const noexcept {
  double maxValue = *std::max_element(
      players_.begin(), players_.end(),
      [](uint16_t const &a, uint16_t const &b) { return a < b; });
  uint8_t nBins = maxValue + 1;
  // double dBin = maxValue / nBins;
  auto playerSum = std::accumulate(
      players_.begin(), players_.end(), 0,
      [](int currentSum, uint16_t const &a) { return currentSum + a; });
  int n;
  std::ofstream fOut;
  fOut.open("histogram.dat");
  for (int i = 0; i < nBins + 1; ++i) {
    n = std::count_if(players_.begin(), players_.end(),
                      [i, nBins, maxValue](uint16_t const &player) {
                        return player / maxValue >= i * (1. / nBins) &&
                               player / maxValue < (i + 1) * (1. / nBins);
                      });
    std::cout << n << '\n';
    fOut << std::setprecision(3) << i * (1. / nBins) << '\t'
         << static_cast<double>(n) / playerSum << '\n';
  }
  fOut.close();
}

void network::fprintHist(uint8_t nBins) const noexcept {
  double maxValue = *std::max_element(
      players_.begin(), players_.end(),
      [](uint16_t const &a, uint16_t const &b) { return a < b; });
  // double dBin = maxValue / nBins;
  auto playerSum = std::accumulate(
      players_.begin(), players_.end(), 0,
      [](int currentSum, uint16_t const &a) { return currentSum + a; });
  int n;
  std::ofstream fOut;
  fOut.open("histogram.dat");
  for (int i = 0; i < nBins + 1; ++i) {
    n = std::count_if(players_.begin(), players_.end(),
                      [i, nBins, maxValue](uint16_t const &player) {
                        return player / maxValue >= i * (1. / nBins) &&
                               player / maxValue < (i + 1) * (1. / nBins);
                      });
    std::cout << n << '\n';
    fOut << std::setprecision(3) << i * (1. / nBins) << '\t'
         << static_cast<double>(n) / playerSum << '\n';
  }
  fOut.close();
}
