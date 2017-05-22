CXX=g++
CXX_FLAGS=-std=c++14 -O3 -march=native -mtune=native

all: test-polygon-bisect

test-polygon-bisect: main.o polygon_bisect.o generate_polygon.o
	$(CXX) $(CXX_FLAGS) -o test-polygon-bisect main.o polygon_bisect.o generate_polygon.o

main.o: main.cpp polygon_bisect.hpp
	$(CXX) $(CXX_FLAGS) -c main.cpp

polygon_bisect.o: polygon_bisect.cpp polygon_bisect.hpp
	$(CXX) $(CXX_FLAGS) -c polygon_bisect.cpp

generate_polygon.o: generate_polygon.cpp generate_polygon.hpp
	$(CXX) $(CXX_FLAGS) -c generate_polygon.cpp

@PHONY: clean
clean:
	rm *.o
