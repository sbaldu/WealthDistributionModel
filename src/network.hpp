#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <cstdint>
#include <vector>

class network {
    uint16_t _rows, _cols;
	std::vector<uint16_t> _players; // array that contains all the players in the network
public:
	network(uint16_t ,uint16_t ,uint16_t);
	std::vector<uint16_t> const getPlayers();
	uint16_t couples(uint8_t); // the couples are chosen
	
	void evolveUniform(); // the couples play
	void evolvePrefAtach(); // the couples play
    void print() const noexcept;
	void fprintHist(uint8_t) const noexcept;
};

#endif