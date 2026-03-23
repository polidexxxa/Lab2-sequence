CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

all: main tests demos

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

tests: Tests.cpp
	$(CXX) $(CXXFLAGS) -o tests Tests.cpp

demos: demos.cpp
	$(CXX) $(CXXFLAGS) -o demos demos.cpp

run: main
	./main

test: tests
	./tests

demo: demos
	./demos

clean:
	rm -f main tests demos

rebuild: clean all

.PHONY: all run test demo clean rebuild