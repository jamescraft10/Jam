CC = g++
SRC_PATH = src
BUILD_PATH = build/
BUILD_FILE_PATH = $(BUILD_PATH)jam
CFLAGS = -Isrc

INPUT = tests/main.ja
OUTPUT = build/main

all: mkdir
	$(CC) src/jam.cpp -o $(BUILD_FILE_PATH) $(CFLAGS)
	$(BUILD_FILE_PATH) $(INPUT) $(OUTPUT)

build: mkdir
	$(CC) src/jam.cpp -o $(BUILD_FILE_PATH) $(CFLAGS) -O3

debug: mkdir
	$(CC) src/jam.cpp -o $(BUILD_FILE_PATH) $(CFLAGS) -g
	gdb --args $(BUILD_FILE_PATH) $(INPUT) $(OUTPUT)

time: mkdir
	$(CC) src/jam.cpp -o $(BUILD_FILE_PATH) $(CFLAGS)
	time $(BUILD_FILE_PATH) $(INPUT) $(OUTPUT)

mkdir:
	if [ -f $(BUILD_PATH) ]; then \
		mkdir build; \
	fi