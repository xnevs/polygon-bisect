CXX=g++
CXX_FLAGS=-std=c++14 -O3 -march=native -mtune=native

all: test-polygon-bisect

test-polygon-bisect: main.o polygon_bisect.o
	$(CXX) $(CXX_FLAGS) -o test-polygon-bisect main.o polygon_bisect.o

main.o: main.cpp polygon_bisect.hpp
	$(CXX) $(CXX_FLAGS) -c main.cpp

polygon_bisect.o: polygon_bisect.cpp polygon_bisect.hpp
	$(CXX) $(CXX_FLAGS) -c polygon_bisect.cpp

@PHONY: clean
clean:
	rm *.o
