#include "network.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

std::random_device globalRndDev;
std::mt19937 globalRNG(globalRndDev());

Player::Player() : capital(0), nLink(0){};
Player::Player(uint16_t c, uint8_t n) : capital(c), nLink(n){};

network::network(uint16_t initialCapital, uint16_t rows, uint16_t cols) {
  _rows = rows;
  _cols = cols;
  std::vector<Player> vec(_rows * _cols);
  for (auto &i : vec) {
    i.capital = initialCapital;
    i.nLink = 1;
  }
  _players = vec;
}

std::vector<Player> const network::getPlayers() { return _players; }

std::vector<Player> const network::filterByLinks(uint8_t n) {
  std::vector<Player> vec;
  for (auto &i : _players) {
    if (i.nLink == n) {
      vec.push_back(i);
    }
  }
  return vec;
}

std::vector<uint16_t> const network::playersMoney() {
  std::vector<uint16_t> money;
  for (auto const &p : _players) {
    money.push_back(p.capital);
  }
  return money;
}

std::vector<uint16_t> const
network::playersMoney(std::vector<Player> const &vec) {
  std::vector<uint16_t> money;
  for (auto const &p : vec) {
    money.push_back(p.capital);
  }
  return money;
}

std::vector<uint16_t> network::couples(uint16_t first, uint8_t n) {
  auto dist = std::uniform_int_distribution<uint16_t>(
      0, _rows * _cols - 1); // second player is chosen randomly
  std::vector<uint16_t> couples;
  while (couples.size() < n) {
    uint16_t rnd = dist(globalRNG);
    if (rnd != first ||
        (couples.size() > 0 &&
         !(*std::find_if(couples.begin(), couples.end(),
                         [rnd](uint16_t const &i) { return i == rnd; })))) {
      couples.push_back(rnd);
    }
  }
  return couples;
}

void network::createBusinessMen(uint8_t nLink, uint8_t total) {
  auto dist = std::uniform_int_distribution<uint16_t>(0, _rows * _cols - 1);
  while (total > 0) {
    uint16_t rnd = dist(globalRNG);
    if (_players[rnd].nLink == 1) {
      _players[rnd].capital *= nLink;
      _players[rnd].nLink = nLink;
      --total;
    }
  }
}

void network::distributeBusinessMen(uint8_t mean) {
  auto dist = std::poisson_distribution<uint8_t>(mean);
  int value;
  for (auto &player : _players) {
    value = dist(globalRNG);
    if (value > 1) {
      player.capital *= value;
      player.nLink = value;
    }
  }
}

void network::evolveUniform() {
  uint16_t first =
      std::uniform_int_distribution<uint16_t>(0, _rows * _cols - 1)(globalRNG);
  std::uniform_int_distribution<std::mt19937::result_type> coin(0, 1);

  for (auto const &other : couples(first, _players[first].nLink)) {
    if (coin(globalRNG) && _players[other].capital > 0) {
      ++_players[first];
      --_players[other];
    } else if (_players[first].capital > 0) {
      --_players[first];
      ++_players[other];
    }
  }
}

void network::evolvePrefAtt() {
  uint16_t first =
      std::uniform_int_distribution<uint16_t>(0, _rows * _cols - 1)(globalRNG);
  double prob;

  for (auto const &other : couples(first, _players[first].nLink)) {
    prob = (double)(_players[first].capital) /
           (_players[first].capital + _players[other].capital);
    if (std::bernoulli_distribution(prob)(globalRNG) &&
        _players[other].capital > 0) {
      ++_players[first];
      --_players[other];
    } else if (_players[first].capital > 0) {
      --_players[first];
      ++_players[other];
    }
  }
}

void network::flatTax(uint16_t percentage) {
  for (auto &i : _players) {
    int tax = i.capital * percentage / 100;
    if (!(i.capital < tax)) {
      i.capital -= tax;
    }
  }
}

void network::print() const noexcept {
  int i = 0;
  for (auto const &player : _players) {
    std::cout << player.capital << '\t';
    ++i;
    if (i % _cols == 0) {
      std::cout << '\n';
      i = 0;
    }
  }
}

void network::fprintHist() const noexcept {
  double maxValue = (*std::max_element(_players.begin(), _players.end(),
                                       [](Player const &a, Player const &b) {
                                         return a.capital < b.capital;
                                       }))
                        .capital;
  uint8_t nBins = maxValue + 1;
  // double dBin = maxValue / nBins;
  auto playerSum = std::accumulate(
      _players.begin(), _players.end(), 0,
      [](int currentSum, Player const &a) { return currentSum + a.capital; });
  int n;
  std::ofstream fOut;
  fOut.open("histogram.dat");
  for (int i = 0; i < nBins + 1; ++i) {
    n = std::count_if(_players.begin(), _players.end(),
                      [i, nBins, maxValue](Player const &player) {
                        return player.capital / maxValue >= i * (1. / nBins) &&
                               player.capital / maxValue <
                                   (i + 1) * (1. / nBins);
                      });
    std::cout << n << '\n';
    fOut << std::setprecision(3) << i * (1. / nBins) << '\t'
         << static_cast<double>(n) / playerSum << '\n';
  }
  fOut.close();
}

void network::fprintHist(uint8_t nBins) const noexcept {
  double maxValue = (*std::max_element(_players.begin(), _players.end(),
                                       [](Player const &a, Player const &b) {
                                         return a.capital < b.capital;
                                       }))
                        .capital;
  // double dBin = maxValue / nBins;
  auto playerSum = std::accumulate(
      _players.begin(), _players.end(), 0,
      [](int currentSum, Player const &a) { return currentSum + a.capital; });
  int n;
  std::ofstream fOut;
  fOut.open("histogram.dat");
  for (int i = 0; i < nBins + 1; ++i) {
    n = std::count_if(_players.begin(), _players.end(),
                      [i, nBins, maxValue](Player const &player) {
                        return player.capital / maxValue >= i * (1. / nBins) &&
                               player.capital / maxValue <
                                   (i + 1) * (1. / nBins);
                      });
    std::cout << n << '\n';
    fOut << std::setprecision(3) << i * (1. / nBins) << '\t'
         << static_cast<double>(n) / playerSum << '\n';
  }
  fOut.close();
}
