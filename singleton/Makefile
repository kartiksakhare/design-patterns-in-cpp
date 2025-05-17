.PHONY: run build clean superclean

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = singleton
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
