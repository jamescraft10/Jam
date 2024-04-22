all:
	g++ ./src/jam.cpp ./src/lexer.cpp ./src/parser.cpp -o build/jam -Iinclude/
	build/jam $(INPUT) $(OUTPUT)

build:
	g++ ./src/jam.cpp ./src/lexer.cpp ./src/parser.cpp -o build/jam -Iinclude/ -O3

debug:
	g++ ./src/jam.cpp ./src/lexer.cpp ./src/parser.cpp -o build/jam -Iinclude/ -g
	gdb --args ./build/jam $(INPUT) $(OUTPUT)

time:
	g++ ./src/jam.cpp ./src/lexer.cpp ./src/parser.cpp -o build/jam -Iinclude/
	time build/jam $(INPUT) $(OUTPUT)

setup:
	mkdir build
	mkdir ./tests/build