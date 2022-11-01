all:
	g++ -Wall -Wextra -fsanitize=address ./main.cpp ./src/network.cpp -o test.out