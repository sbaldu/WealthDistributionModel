#ifndef newModel_h
#define newModel_h

#include <cstdint>
#include <sys/types.h>
#include <map>
#include <unordered_map>
#include <vector>

class newModel {
	uint16_t rows_, cols_;
	std::vector<float> players_; // array that contains all the players in the network
	std::vector<float> lambda_;
public:
	newModel(float, uint16_t ,uint16_t);
	uint16_t const getRows();
	uint16_t const getCols();
	std::vector<float> const& getPlayers();
	std::vector<float> const& getLambdas();
	std::vector<float> const playersMoney();
	uint16_t couples(uint16_t); // the couples are chosen
	
	void evolveUniform();
	void evolveSavings();
};

#endif
