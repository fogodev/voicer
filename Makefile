# compiler and libraries
CC=clang++
OPTIONS= -std=c++11 -O2
LIBS= -lwann

# folders of the project
SOURCES=$(wildcard src/*.cpp)
BUILD=./build
TARGET=$(BUILD)/main

all: clean init main

init:
	mkdir $(BUILD)

clean:
	rm -Rf $(BUILD)

main:
	$(CC) $(OPTIONS) $(LIBS) -o $(TARGET) $(SOURCES)

