#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <cstdint>
#include <vector>

struct Player {
	uint16_t capital;
	uint8_t nLink;

	Player();
	Player(uint16_t, uint8_t);
	Player(const Player& p) : capital(p.capital), nLink(p.nLink) {}

	Player& operator++() {
		++capital;
		return *this;
	}
	Player& operator--() {
		--capital;
		return *this;
	}
	Player& operator=(Player const& other) {
		capital = other.capital;
		nLink = other.nLink;
		return *this;
	}
	Player& operator+(Player const& other) {
		capital += other.capital;
		return *this;
	}
	Player& operator-(Player const& other) {
		capital -= other.capital;
		return *this;
	}
};

class network {
    uint16_t _rows, _cols;
	std::vector<Player> _players; // array that contains all the players in the network
public:
	network(uint16_t ,uint16_t ,uint16_t);
	std::vector<Player> const getPlayers();
	uint16_t couples(uint16_t); // the couples are chosen
	
	void evolveUniform(); // the couples play
	void evolvePrefAtach(); // the couples play
    void print() const noexcept;
	void fprintHist() const noexcept;
	void fprintHist(uint8_t) const noexcept;
};

#endif