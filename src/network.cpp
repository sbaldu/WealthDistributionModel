#include "network.hpp"
#include <algorithm>
#include <iostream>
#include <random>

network::network(uint16_t initialCapital, uint16_t rows, uint16_t cols) {
  _rows = rows;
  _cols = cols;
  std::vector<uint16_t> vec(_rows * _cols, initialCapital);
  _players = vec;
}

std::vector<uint16_t> const network::getPlayers() { return _players; }

std::vector<Couple> network::couples(uint8_t n) {
  // rnd numbers init
  std::random_device rnd_dev;
  std::mt19937 rng(rnd_dev());

  std::vector<uint8_t> couples(_rows * _cols);
  std::iota(couples.begin(), couples.end(), 1);
  std::shuffle(couples.begin(), couples.end(), rng);

  Couple tempCouple;
  std::vector<Couple> couplesVector(n);
  for (int i = 0; i < n; ++i) {
    tempCouple.first = couples[i] - 1;
    tempCouple.second = couples[i + n] - 1;
    couplesVector[i] = tempCouple;
  }
  return couplesVector;
}

void network::gamble(Couple cop) {
  // rnd numbers init
  std::random_device rnd_dev;
  std::mt19937 rng(rnd_dev());
  std::uniform_int_distribution<std::mt19937::result_type> coin(0, 1);

  uint8_t first = cop.first;
  uint8_t second = cop.second;

  if (_players[first] > 0 && _players[second] > 0) {
    if (coin(rng)) {
      _players[first] += 1;
      _players[second] -= 1;
    } else {
      _players[first] -= 1;
      _players[second] += 1;
    }
  }
}

void network::evolve() {
  std::vector<Couple> couples = this->couples(10);
  for (uint8_t i = 0; i < couples.size(); ++i) {
    gamble(couples[i]);
  }
}

void network::print() const noexcept {
  int i = 0;
  for (auto const &player : _players) {
    std::cout << player << '\t';
    ++i;
    if (i % _cols == 0) {
      std::cout << '\n';
      i = 0;
    }
  }
}