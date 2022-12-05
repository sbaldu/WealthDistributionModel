#ifndef newModel_h
#define newModel_h

#include <cstdint>
#include <sys/types.h>
#include <map>
#include <unordered_map>
#include <vector>

class newModel {
	int Nplayers_;
	std::vector<double> players_; // array that contains all the players in the network
	std::vector<double> lambda_;
public:
	newModel(double, int);
	std::vector<double> const& getPlayers();
	std::vector<double> const& getLambdas();
	uint16_t couples(uint16_t); // the couples are chosen
	
	void evolveUniform();
	void evolveSavings();
};

#endif
