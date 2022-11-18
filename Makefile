all:
	clang-format -i ./src/*.cc
	clear
	./src/compile.sh
cpp:
	clang-format -i ./src/*.cc
	clear
