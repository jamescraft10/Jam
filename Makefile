CC = g++
SRC_PATH = src
BUILD_PATH = build/jam
CFLAGS = -Isrc

INPUT = tests/main.ja
OUTPUT = build/main

all:
	$(CC) src/jam.cpp -o $(BUILD_PATH) $(CFLAGS)
	$(BUILD_PATH) $(INPUT) $(OUTPUT)

build:
	$(CC) src/jam.cpp -o $(BUILD_PATH) $(CFLAGS) -O3

debug:
	$(CC) src/jam.cpp -o $(BUILD_PATH) $(CFLAGS) -g
	gdb --args $(BUILD_PATH) $(INPUT) $(OUTPUT)

time:
	$(CC) src/jam.cpp -o $(BUILD_PATH) $(CFLAGS)
	time $(BUILD_PATH) $(INPUT) $(OUTPUT)