#include "./src/network.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>

void printLoadingBar(int const i, int const n) {
  std::cout << "Loading: " << std::setprecision(2) << std::fixed
            << (i * 100. / n) << "%" << '\r';
  std::cout.flush();
}

// uniform parameters
// net(1, 100, 100)
// n = 1e5

int main() {
  network net(1, 100, 100);
  int n = 1e5;
  for (int i = 0; i < n; ++i) {
    printLoadingBar(i, n);
    net.evolveUniform();
    // net.evolvePrefAtach();
  }
  int sum = 0;
  for (auto i : net.getPlayers()) {
    sum += i.capital;
  }
  std::cout << '\n' << '\n';
  // net.print();
  net.fprintHist();
  // std::cout << sum;
}