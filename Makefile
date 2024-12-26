CXX = clang
CXXFLAGS = -std=c++20 -Wall -Wextra -Wpedantic

all: clean build run

build: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	rm -f a.exe

run:
	./a.exe