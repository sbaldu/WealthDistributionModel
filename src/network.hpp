#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <cstdint>
#include <vector>

class network {
    private:
    uint8_t _rows, _cols;
	std::vector<uint16_t> _players; // array that contains all the players in the network
public:
	network(uint16_t ,uint16_t ,uint16_t);
	std::vector<uint16_t> const getPlayers();
	std::vector<uint8_t> couples(uint8_t); // the couples are chosen

	void gamble(); // the players gamble
    void print() const noexcept;
};

#endif