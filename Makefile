all:
	clang-format -i ./main.cpp
	clang-format -i ./src/*.cpp
	clear
	g++ -Wall -Wextra -fsanitize=address ./main.cpp ./src/network.cpp -o test.out