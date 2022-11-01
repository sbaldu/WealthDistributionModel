#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <cstdint>
#include <vector>

struct Couple {
	uint8_t first;
	uint8_t second;
};

class network {
    private:
    uint8_t _rows, _cols;
	std::vector<uint16_t> _players; // array that contains all the players in the network
public:
	network(uint16_t ,uint16_t ,uint16_t);
	std::vector<uint16_t> const getPlayers();
	std::vector<Couple> couples(uint8_t); // the couples are chosen
	
	void gamble(Couple); // the players gamble
	void evolve(); // the couples play
    void print() const noexcept;
};

#endif