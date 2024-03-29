#include "network.h"
#include "SparseMatrix.hpp"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <unordered_map>
#include <utility>

std::random_device globalRndDev;
std::mt19937 globalRNG(globalRndDev());

network::network(uint16_t initialCapital, uint16_t rows, uint16_t cols) : adjacencyMatrix_(rows * cols, rows * cols) {
  rows_ = rows;
  cols_ = cols;
  initCap_ = initialCapital;
  players_.resize(rows_ * cols_, initialCapital);
}

uint16_t network::getRows() const { return rows_; }
uint16_t network::getCols() const { return cols_; }

std::vector<uint16_t> const &network::players() { return players_; }
std::vector<uint16_t> const &network::getPoors() {
  poors_.clear();
  for (int i{}; i < rows_ * cols_; ++i) {
    if (isPoor(players_[i])) {
      poors_.push_back(i);
    }
  }
  return poors_;
}

uint16_t network::couples(uint16_t first) {
  auto dist = std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ - 1);  // second player is chosen randomly
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

  for (int i{}; i < rows_ * cols_ - 1; ++i) {
    for (int j{i + 1}; j < rows_ * cols_; ++j) {
      if (dis(globalRNG) < prob) {
        adjacencyMatrix_.insert_or_assign(i, j, true);
      }
    }
  }
  adjacencyMatrix_ += (++adjacencyMatrix_);  // symmetrize the matrix
  nLinks_ = adjacencyMatrix_.getDegreeVector();
}

void network::importMatrix(std::string const &filename) {
  std::ifstream input;
  input.open(filename);
  input >> adjacencyMatrix_;
  nLinks_ = adjacencyMatrix_.getDegreeVector();
  for (auto const &p : nLinks_) {
    std::cout << p.second << std::endl;
  }
}

bool network::exists(int i, int j) { return adjacencyMatrix_.contains(i, j); }

bool network::isPoor(uint16_t money) { return money < initCap_ * 15e-2; }

void network::printMatrix() {
  for (int i{}; i < rows_ * cols_; ++i) {
    for (int j{}; j < rows_ * cols_; ++j) {
      std::cout << this->exists(i, j) << "  ";
    }
    std::cout << '\n';
  }
}

void network::evolveUniform() {
  uint16_t first = std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ - 1)(globalRNG);
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
  uint16_t first = std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ - 1)(globalRNG);
  uint16_t other = couples(first);
  float prob = ((nLinks_(first)) + 1.) / (nLinks_(first) + nLinks_(other) + 2.);
  if (std::bernoulli_distribution(prob)(globalRNG) && players_[other] > 0) {
    ++players_[first];
    --players_[other];
  } else if (players_[first] > 0) {
    --players_[first];
    ++players_[other];
  }
}

void network::evolvePrefAttNoTax() {
  uint16_t first = std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ - 1)(globalRNG);
  uint16_t other = couples(first);
  uint16_t poor, rich;
  if (players_[first] >= players_[other]) {
    poor = other;
    rich = first;
  } else {
    poor = first;
    rich = other;
  }
  float prob = (float)(players_[poor] + 1) / (players_[poor] + players_[rich] + 1);
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
  SparseMatrix<bool> row = adjacencyMatrix_.getRow(first);
  if (row.size() == 0) {
    return;
  }
  uint16_t second = row.getRndElement().first;

  std::uniform_int_distribution<std::mt19937::result_type> coin(0, 1);
  if (coin(globalRNG) && players_[second] > 0) {
    ++players_[first];
    --players_[second];
  } else if (players_[first] > 0) {
    --players_[first];
    ++players_[second];
  }
}

void network::evolvebyLink() {
  auto random_iterator = adjacencyMatrix_.begin();
  std::advance(random_iterator,
               std::uniform_int_distribution<uint16_t>(0, adjacencyMatrix_.getNonZeroElements() - 1)(globalRNG));
  auto link = *random_iterator;
  uint16_t first = link.first / (cols_ * rows_);
  uint16_t second = link.first % (cols_ * rows_);
  if (first == second) {
    return;
  }
  std::uniform_int_distribution<std::mt19937::result_type> coin(0, 1);
  if (coin(globalRNG) && players_[second] > 0) {
    ++players_[first];
    --players_[second];
  } else if (players_[first] > 0) {
    --players_[first];
    ++players_[second];
  }
}

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

float network::checkPoor(uint16_t poorPlayer) {
  SparseMatrix<bool> neighbors = adjacencyMatrix_.getRow(poorPlayer);
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

std::pair<float, float> network::calcProb(std::vector<uint16_t> const &poors) {
  // calculate all the possible couples of poors
  int linked_and_poor{};
  int pairs_of_poors{};
  for (int i{}; i < (int)(poors.size()) - 1; ++i) {
    for (int j{i + 1}; j < (int)(poors.size()) - 1; ++j) {
      ++pairs_of_poors;
      if (adjacencyMatrix_.contains(i, j)) {
        ++linked_and_poor;
      }
    }
  }
  // calculate the probability that the two poors in a couple are linked
  float prob_linked_and_poor = (float)(linked_and_poor) / pairs_of_poors;

  // calculate all the possible couples of agents
  int linked{};
  int pairs_of_agents{};
  for (int i{}; i < (int)(players_.size()) - 1; ++i) {
    for (int j{i + 1}; j < (int)(players_.size()) - 1; ++j) {
      ++pairs_of_agents;
      if (adjacencyMatrix_.contains(i, j)) {
        ++linked;
      }
    }
  }
  // calculate the probability that two agents at random are linked
  std::cout << "Pairs of agents linked = " << linked << std::endl;
  std::cout << "Pairs of agents = " << pairs_of_agents << std::endl;
  float prob_linked = (float)(linked) / pairs_of_agents;

  return {prob_linked_and_poor, prob_linked};
}

void network::print() const {
  int i{};
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
  double maxValue =
      *std::max_element(players_.begin(), players_.end(), [](uint16_t const &a, uint16_t const &b) { return a < b; });
  uint8_t nBins = maxValue + 1;
  auto playerSum = std::accumulate(
      players_.begin(), players_.end(), 0, [](int currentSum, uint16_t const &a) { return currentSum + a; });
  int n;
  std::ofstream fOut;
  fOut.open("histogram.dat");
  for (int i{}; i < nBins + 1; ++i) {
    n = std::count_if(players_.begin(), players_.end(), [i, nBins, maxValue](uint16_t const &player) {
      return player / maxValue >= i * (1. / nBins) && player / maxValue < (i + 1) * (1. / nBins);
    });
    std::cout << n << '\n';
    fOut << std::setprecision(3) << i * (1. / nBins) << '\t' << static_cast<double>(n) / playerSum << '\n';
  }
  fOut.close();
}

void network::fprintHist(uint8_t nBins) const noexcept {
  double maxValue =
      *std::max_element(players_.begin(), players_.end(), [](uint16_t const &a, uint16_t const &b) { return a < b; });
  // double dBin = maxValue / nBins;
  auto playerSum = std::accumulate(
      players_.begin(), players_.end(), 0, [](int currentSum, uint16_t const &a) { return currentSum + a; });
  int n;
  std::ofstream fOut;
  fOut.open("histogram.dat");
  for (int i{}; i < nBins + 1; ++i) {
    n = std::count_if(players_.begin(), players_.end(), [i, nBins, maxValue](uint16_t const &player) {
      return player / maxValue >= i * (1. / nBins) && player / maxValue < (i + 1) * (1. / nBins);
    });
    std::cout << n << '\n';
    fOut << std::setprecision(3) << i * (1. / nBins) << '\t' << static_cast<double>(n) / playerSum << '\n';
  }
  fOut.close();
}

void network::saveMatrix(std::string const &path) const {
  std::ofstream output;
  output.open(path);
  output << adjacencyMatrix_;
}
