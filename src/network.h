#ifndef NETWORK_H
#define NETWORK_H

#include <cstdint>
#include <sys/types.h>
#include <vector>
#include "SparseMatrix.hpp"

using Matrix = SparseMatrix<bool>;

class network {
	uint16_t rows_, cols_;
	std::vector<uint16_t> players_; // array that contains all the players in the network
	Matrix adjacencyMatrix_;
public:
	network(uint16_t ,uint16_t ,uint16_t);
	std::vector<uint16_t> const& getPlayers();
	Matrix const& getAdjacency();
	std::vector<uint16_t> const playersMoney();
	/* std::vector<uint16_t> const playersMoney(std::vector<uint16_t> const&); */
	uint16_t couples(uint16_t); // the couples are chosen
	
	void createLinks();
	bool exists(int, int);
	void evolveUniform(); // the couples play
	void evolvePrefAtt();
	void evolvePrefAttNoTax();
	void flatTax(uint8_t);
	void print() const noexcept;
	void fprintHist() const noexcept;
	void fprintHist(uint8_t) const noexcept;
};

#endif
