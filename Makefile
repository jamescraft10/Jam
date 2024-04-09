all:
	g++ -o ./build/jam.out ./src/jam.cpp ./src/lexer.cpp -Iinclude/
	build/jam.out $(INPUT) $(OUTPUT)

build:
	g++ -o ./build/jam.out ./src/jam.cpp ./src/lexer.cpp -Iinclude/ -O3