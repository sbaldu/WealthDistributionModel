#include "network.hpp"
#include <iostream>
#include <random>

network::network(uint16_t initialCapital, uint16_t rows, uint16_t cols) {
    _rows = rows;
    _cols = cols;
    std::vector<uint16_t> vec(_rows*_cols,initialCapital);
    _players = vec;
}

std::vector<uint16_t> const network::getPlayers() {
    return _players;
}

std::vector<uint8_t> network::couples(uint8_t n) {
    // rnd numbers init
    std::random_device rnd_dev;
    std::mt19937 rng(rnd_dev());
    std::uniform_real_distribution<uint8_t> dist(0., 1.);
    uint8_t initLenght = _rows*_cols - 1;
    std::vector<uint8_t> temp(n);
    std::vector<uint8_t> couples(n);

    for(int i = 0; i < n; ++i) {

    }

}

void network::print() const noexcept {
    int i = 0;
    for(auto const& player : _players) {
        std::cout << player << '\t';
        ++i;
        if(i%_cols == 0) {
            std::cout << '\n';
            i = 0;
        }
    }
}