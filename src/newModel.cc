#include "newModel.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <utility>

std::random_device globalRndDev;
std::mt19937 globalRNG(globalRndDev());

newModel::newModel(float initialCapital, uint16_t rows, uint16_t cols) {
  rows_ = rows;
  cols_ = cols;
  int Nplayers = rows * cols;

  // Fill the vector containing the players' propensities to save money
  std::vector<float> lambdas;
  for (int i = 0; i < 0.99 * Nplayers; ++i) {
    lambdas.push_back(0);
  }
  for (int i = 0; i < 0.01 * Nplayers; ++i) {
    float lambda_ = std::uniform_real_distribution<float>(0., 1.)(globalRNG);
    lambdas.push_back(lambda_);
  }
  lambda_ = lambdas;
  std::vector<float> vec(rows_ * cols_);
  for (auto &i : vec) {
    i = initialCapital;
  }
  players_ = vec;
}

uint16_t const newModel::getRows() { return rows_; }
uint16_t const newModel::getCols() { return cols_; }

std::vector<float> const &newModel::getPlayers() { return players_; }
std::vector<float> const &newModel::getLambdas() { return lambda_; }

std::vector<float> const newModel::playersMoney() {
  std::vector<float> money;
  for (auto const &p : players_) {
    money.push_back(p);
  }
  return money;
}

uint16_t newModel::couples(uint16_t first) {
  auto dist = std::uniform_int_distribution<uint16_t>(
      0, rows_ * cols_ - 1); // second player is chosen randomly
  uint16_t second = 0;
  uint16_t rnd = dist(globalRNG);
  if (rnd != first) {
    second = rnd;
  }
  return second;
}

void newModel::evolveUniform() {
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

void newModel::evolveSavings() {
  uint16_t first =
      std::uniform_int_distribution<uint16_t>(0, rows_ * cols_ - 1)(globalRNG);
  uint16_t other = couples(first);

  // We introduce the lambda parameter, which indicates the saving propensity
  float lambda_i = lambda_[first];
  float lambda_j = lambda_[other];

  // We introduce the fraction of wealth that is exchanged
  float epsilon = std::uniform_real_distribution<float>(0., 1.)(globalRNG);

  if (players_[first] > 0. && players_[other] > 0.) {
    players_[first] = lambda_i * players_[first] +
                      epsilon * ((1 - lambda_i) * players_[first] +
                                 (1 - lambda_j) * players_[other]);
    players_[other] = lambda_j * players_[other] +
                      (1 - epsilon) * ((1 - lambda_i) * players_[first] +
                                       (1 - lambda_j) * players_[other]);
  }
}
