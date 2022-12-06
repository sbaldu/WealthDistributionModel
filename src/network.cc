#include "network.h"
#include "SparseMatrix.hpp"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <utility>

std::random_device globalRndDev;
std::mt19937 globalRNG(globalRndDev());

network::network(uint16_t initialCapital, uint16_t rows, uint16_t cols)
    : adjacencyMatrix_(rows * cols, rows * cols) {
  rows_ = rows;
  cols_ = cols;
  initCap_ = initialCapital;
  std::vector<uint16_t> vec(rows_ * cols_);
  for (auto &i : vec) {
    i = initialCapital;
  }
  players_ = vec;
}

uint16_t const network::getRows() { return rows_; }
uint16_t const network::getCols() { return cols_; }

std::vector<uint16_t> const &network::getPlayers() { return players_; }
std::vector<uint16_t> const &network::getPoors() {
  poors_.clear();
  for (int i = 0; i < rows_ * cols_; ++i) {
    if (isPoor(players_[i])) {
      poors_.push_back(i);
    }
  }
  return poors_;
}

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

void network::createLinks(uint8_t avgLinks) {
  float prob = (float)(avgLinks) / (cols_ * rows_);
  std::uniform_real_distribution<float> dis(0, 1);

  for (int i = 0; i < rows_ * cols_ - 1; ++i) {
    for (int j = i + 1; j < rows_ * cols_; ++j) {
      if (dis(globalRNG) < prob) {
        adjacencyMatrix_.insert(i, j, true);
        adjacencyMatrix_.insert(rows_ * cols_ - j, i, true);
      }
    }
  }
  nLinks_ = adjacencyMatrix_.getDegreeVector();
}

void network::importMatrix(const char *filename) {
  adjacencyMatrix_ = Matrix(filename);
  std::cout << __LINE__ << std::endl;
  nLinks_ = adjacencyMatrix_.getDegreeVector();
  for (auto const &p : nLinks_) {
    std::cout << p << std::endl;
  }
}

bool network::exists(int i, int j) { return adjacencyMatrix_.exists(i, j); }

bool network::isPoor(uint16_t money) { return money < initCap_ * 15e-2; }

void network::printMatrix() {
  for (int i = 0; i < rows_ * cols_; ++i) {
    for (int j = 0; j < rows_ * cols_; ++j) {
      std::cout << this->exists(i, j) << "  ";
    }
    std::cout << '\n';
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

// void network::evolvePrefAtt() {
//   uint16_t first =
//       std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ -
//       1)(globalRNG);
//   uint16_t other = couples(first);
//   float prob = (float)((players_[first])) / (players_[first] +
//   players_[other]); if (std::bernoulli_distribution(prob)(globalRNG) &&
//   players_[other] > 0) {
//     ++players_[first];
//     --players_[other];
//   } else if (players_[first] > 0) {
//     --players_[first];
//     ++players_[other];
//   }
// }
void network::evolvePrefAtt() {
  uint16_t first =
      std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ - 1)(globalRNG);
  uint16_t other = couples(first);
  float prob = ((nLinks_[first]) + 1.) / (nLinks_[first] + nLinks_[other] + 2.);
  if (std::bernoulli_distribution(prob)(globalRNG) && players_[other] > 0) {
    ++players_[first];
    --players_[other];
  } else if (players_[first] > 0) {
    --players_[first];
    ++players_[other];
  }
}

void network::evolvePrefAttNoTax() {
  uint16_t first =
      std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ - 1)(globalRNG);
  uint16_t other = couples(first);
  uint16_t poor, rich;
  if (players_[first] >= players_[other]) {
    poor = other;
    rich = first;
  } else {
    poor = first;
    rich = other;
  }
  float prob =
      (float)(players_[poor] + 1) / (players_[poor] + players_[rich] + 1);
  if (std::bernoulli_distribution(prob)(globalRNG) && players_[rich] > 0) {
    ++players_[poor];
    --players_[rich];
  } else if (players_[poor] > 0) {
    --players_[poor];
    ++players_[rich];
  }
}

void network::evolveFixed() {
  std::uniform_int_distribution<uint16_t> rnd(0, rows_ * cols_ - 1);
  uint16_t first = rnd(globalRNG);
  auto row = adjacencyMatrix_.getRow(first);
  if (row.size() == 0) {
    return;
  }
  uint16_t second = adjacencyMatrix_.getRNDRowIndex(first);

  std::uniform_int_distribution<std::mt19937::result_type> coin(0, 1);
  if (coin(globalRNG) && players_[second] > 0) {
    ++players_[first];
    --players_[second];
    // if (players_[second] == 0 && !poorMap_.contains(second)) {
    //   poorMap_.emplace(
    //       std::make_pair(second, 0)); // add the poor to the poor map
    // }
  } else if (players_[first] > 0) {
    --players_[first];
    ++players_[second];
    // if (players_[first] == 0 && !poorMap_.contains(first)) {
    //   poorMap_.emplace(
    //       std::make_pair(first, 0)); // add the poor to the poor map
    // }
  }
  // for (auto &poor : poorMap_) { // check all the poors and if they are still
  //                               // poor, you increase the count
  //   if (players_[poor.first] == 0) {
  //     ++poor.second;
  //   }
  // }
  // for (auto it = poorMap_.begin(); it != poorMap_.end();) {
  //   if (this->checkPoor(it->first) < 0.5) {
  //     it = poorMap_.erase(it);
  //   } else {
  //     ++it;
  //   }
  // }
}

/* void network::flatTax(uint8_t percentage) { */
/*   for (auto &i : players_) { */
/*     int tax = i * percentage / 100; */
/*     if (!(i < tax)) { */
/*       i -= tax; */
/*       cass_ += tax; */
/*     } */
/*   } */
/*   int nPoors = count_if(players_.begin(), players_.end(), isPoor); */
/*   if (cass_ >= nPoors) { */
/*     for (auto &i : players_) { */
/*       if (isPoor(i)) { */
/*         ++i; */
/*         --cass_; */
/*       } */
/*     } */
/*   } */
/* } */

/* void network::flatTax(uint8_t percentage) { */
/*   for (auto &i : players_) { */
/*     int tax = i * percentage / 100; */
/*     if (!(i < percentage / 100)) { */
/*       i -= tax; */
/*       ++cass_; */
/*     } */
/*   } */
/*   if (!(cass_ < players_.size())) { */
/*     for (auto &i : players_) { */
/*       ++i; */
/*       --cass_; */
/*     } */
/*   } */
/* } */

void network::flatTax(uint8_t threshold) {
  for (auto &i : players_) {
    int tax = 1;
    if (!(i < tax)) {
      i -= tax;
      ++cass_;
    }
  }
  if (!(cass_ < players_.size())) {
    for (auto &i : players_) {
      ++i;
      --cass_;
    }
  }
}

void network::evolveSavings() {
  uint16_t first =
      std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ - 1)(globalRNG);
  std::uniform_int_distribution<std::mt19937::result_type> coin(0, 1);
  uint16_t other = couples(first);

  // We introduce the lambda parameter, which indicates the saving propensity
  float lambda_i = std::uniform_real_distribution<float>(0., 1.)(globalRNG);
  float lambda_j = std::uniform_real_distribution<float>(0., 1.)(globalRNG);
  // We introduce the fraction of wealth that is exchanged
  float epsilon = std::uniform_real_distribution<float>(0., 1.)(globalRNG);

  if (coin(globalRNG) && players_[other] > 0) {
    players_[first] = lambda_i * players_[first] +
                      epsilon * ((1 - lambda_i) * players_[first] +
                                 (1 - lambda_j) * players_[other]);
    players_[other] = lambda_j * players_[other] +
                      (1 - epsilon) * ((1 - lambda_i) * players_[first] +
                                       (1 - lambda_j) * players_[other]);
  } else if (players_[first] > 0) {
    players_[other] = lambda_j * players_[other] +
                      epsilon * ((1 - lambda_j) * players_[other] +
                                 (1 - lambda_i) * players_[first]);
    players_[first] = lambda_i * players_[first] +
                      (1 - epsilon) * ((1 - lambda_i) * players_[first] +
                                       (1 - lambda_j) * players_[other]);
  }
}

float network::checkPoor(uint16_t poorPlayer) {
  std::unordered_map<int, bool> neighbors = adjacencyMatrix_.getRow(poorPlayer);
  uint8_t n_neighbors = neighbors.size();
  float poor_neighbors = 0.;

  for (auto &i : neighbors) {
    if (isPoor(players_[i.first])) {
      ++poor_neighbors;
    }
  }
  poor_neighbors /= n_neighbors;
  return poor_neighbors;
}

float network::calcCondProb(std::vector<uint16_t> const &poors) {
  float conditional_probability = 0.;
  float count_favorable = 0.;
  // int count_conditional_total = 0;
  for (auto firstPoor : poors) {
    for (auto secondPoor : adjacencyMatrix_.getRow(firstPoor)) {
      if (isPoor(players_[secondPoor.first])) {
        ++count_favorable;
        break;
      }
    }
    // if (adjacencyMatrix_.getRow(firstPoor).size() != 0) {
    //   count_conditional_total += adjacencyMatrix_.getRow(firstPoor).size();
    // }
  }
  conditional_probability = (count_favorable / 2.) / poors.size();
  return conditional_probability;
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

void network::saveMatrix(const char *path) const {
  adjacencyMatrix_.save(path);
}
