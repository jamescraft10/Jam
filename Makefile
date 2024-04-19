all:
	g++ -o ./build/jam.out ./src/jam.cpp ./src/lexer.cpp -Iinclude/
	build/jam.out $(INPUT) $(OUTPUT)

build:
	g++ -o ./build/jam.out ./src/jam.cpp ./src/lexer.cpp -Iinclude/ -O3

debug:
	g++ -o ./build/jam.out ./src/jam.cpp ./src/lexer.cpp -Iinclude/ -g
	gdb --args ./build/jam.out $(INPUT) $(OUTPUT)

time:
	g++ -o ./build/jam.out ./src/jam.cpp ./src/lexer.cpp -Iinclude/
	time build/jam.out $(INPUT) $(OUTPUT)

setup:
	mkdir build
	mkdir ./build/jam