.PHONY: run build clean

CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra
TARGET = facade
SRC = main.cpp

build: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)
	rm -rf main.dSYM
# Leaves main.cpp, *.md, and this Makefile untouched
