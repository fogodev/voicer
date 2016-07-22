# compiler and libraries
CC=clang++
OPTIONS= -std=c++11 -O2
LIBS= ./libs/libwann.so

# folders of the project
SOURCES=$(wildcard src/*.cpp)
BUILD=./build
TARGET=$(BUILD)/main

all: clean init main genwav

init:
	mkdir $(BUILD)

clean:
	rm -Rf $(BUILD)

main:
	$(CC) $(OPTIONS) -o $(TARGET) $(SOURCES) $(LIBS)

genwav:
	$(CC) $(OPTIONS) -o $(BUILD)/GenWAV src/genWAV.cc
