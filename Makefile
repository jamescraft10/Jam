CC = g++
SRC_PATH = src
BUILD_PATH = build/jam
FILES = jam.cpp lexer.cpp parser.cpp
SOURCES = $(FILES:%.cpp=$(SRC_PATH)/%.cpp)
CFLAGS = -Iinclude

INPUT = tests/main.ja
OUTPUT = build/main

all:
	$(CC) $(SOURCES) -o $(BUILD_PATH) $(CFLAGS)
	$(BUILD_PATH) $(INPUT) $(OUTPUT)

build:
	$(CC) $(SOURCES) -o $(BUILD_PATH) $(CFLAGS) -O3

debug:
	$(CC) $(SOURCES) -o $(BUILD_PATH) $(CFLAGS) -g
	gdb --args $(BUILD_PATH) $(INPUT) $(OUTPUT)

time:
	$(CC) $(SOURCES) -o $(BUILD_PATH) $(CFLAGS)
	time $(BUILD_PATH) $(INPUT) $(OUTPUT)