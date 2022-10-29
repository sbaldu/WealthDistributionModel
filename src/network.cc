#include <cstdint>
#include <iostream>
#include <sys/types.h>
#include <vector>

class network{
private:
	std::vector<uint16_t> players_; // array that contains all the players in the network
public:
	network(uint16_t initialCapital = 10, uint16_t rows = 10, uint16_t cols = 10) {
		std::vector<uint16_t> vec(rows*cols,initialCapital);
		players_ = vec;
	}
	std::vector<uint16_t> const getPlayers() {
		return players_;
	}
	std::vector<uint8_t> couples() { // the couples are chosen
		;
	} 	
	void gamble() { // the players gamble
		;	
	}
};

int main() {}
