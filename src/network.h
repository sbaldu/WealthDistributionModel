#ifndef NETWORK_H
#define NETWORK_H

#include <cstdint>
#include <sys/types.h>
#include <map>
#include <unordered_map>
#include <vector>
#include "SparseMatrix.hpp"

using Matrix = SparseMatrix<bool>;

class network {
	uint16_t rows_, cols_;
	std::vector<uint16_t> players_; // array that contains all the players in the network
	std::unordered_map<uint16_t,int>	poorMap_;
	Matrix adjacencyMatrix_;
public:
	network(uint16_t ,uint16_t ,uint16_t);
	uint16_t const getRows();
	uint16_t const getCols();
	std::vector<uint16_t> const& getPlayers();
	std::unordered_map<uint16_t,int> const& getPoors();
	std::unordered_map<int, bool> const& getAdjacency();
	std::vector<uint16_t> const playersMoney();
	/* std::vector<uint16_t> const playersMoney(std::vector<uint16_t> const&); */
	uint16_t couples(uint16_t); // the couples are chosen
	
	void createLinks(uint8_t);
	void importMatrix(const char*);
	bool exists(int, int);
	void printMatrix();
	void evolveUniform(); // the couples play
	void evolvePrefAtt();
	void evolvePrefAttNoTax();
	void evolveFixed(int);
	void flatTax(uint8_t);
	float checkPoor(uint16_t);
	void print() const noexcept;
	void fprintHist() const noexcept;
	void fprintHist(uint8_t) const noexcept;
	void saveMatrix(const char*) const;
};

#endif
