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
	uint16_t rows_, cols_, cass_ = 0, initCap_;
	std::vector<uint16_t> players_, poors_; // array that contains all the players in the network
	Matrix adjacencyMatrix_;
	std::vector<int> nLinks_;
public:
	network(uint16_t ,uint16_t ,uint16_t);
	uint16_t const getRows();
	uint16_t const getCols();
	std::vector<uint16_t> const& getPlayers();
	std::vector<uint16_t> const& getPoors();
	std::vector<uint16_t> const playersMoney();
	uint16_t couples(uint16_t); // the couples are chosen
	
	void createLinks(uint8_t);
	void importMatrix(const char*);
	bool exists(int, int);
	bool isPoor(uint16_t);
	void printMatrix();
	void evolveUniform(); // the couples play
	void evolvePrefAtt();
	void evolvePrefAttNoTax();
	void evolveFixed();
	void flatTax(uint8_t);
	void evolveSavings();
	float checkPoor(uint16_t);
	std::vector<float> calcProb(std::vector<uint16_t> const&);
	void print() const noexcept;
	void fprintHist() const noexcept;
	void fprintHist(uint8_t) const noexcept;
	void saveMatrix(const char*) const;
};

#endif
