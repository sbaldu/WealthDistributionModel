all:
	clang-format -i ./main.cc
	clang-format -i ./src/*.cc
	clear
	./src/compile.sh
	g++ -Wall -Wextra -fsanitize=address ./main.cc ./src/network.cc -o test.out

