#include "./src/network.hpp"
#include <iostream>

int main() {
  network net(10, 10, 10);
  for (uint8_t i = 0; i < 169; ++i) {
    net.evolve();
  }
  int sum = 0;
  for (auto i : net.getPlayers()) {
    sum += i;
  }
  net.print();
  std::cout << sum;
}