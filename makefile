CXX := g++
CXXFLAGS := -std=c++2a -Iinclude -Ilib

SOURCE := src/index.cc
TARGET := noble

all:
	$(CXX) -o $(TARGET) $(SOURCE) $(CXXFLAGS)

.PHONY: all
