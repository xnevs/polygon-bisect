CXX=g++
CXX_FLAGS=-std=c++14 -O3 -march=native -mtune=native

all: test-polygon-bisect

test-polygon-bisect: main.o polygon_bisect.o generate_polygon.o
	$(CXX) $(CXX_FLAGS) -o test-polygon-bisect main.o polygon_bisect.o generate_polygon.o

main.o: src/main.cpp src/polygon_bisect.hpp
	$(CXX) $(CXX_FLAGS) -c src/main.cpp

polygon_bisect.o: src/polygon_bisect.cpp src/polygon_bisect.hpp
	$(CXX) $(CXX_FLAGS) -c src/polygon_bisect.cpp

generate_polygon.o: src/generate_polygon.cpp src/generate_polygon.hpp
	$(CXX) $(CXX_FLAGS) -c src/generate_polygon.cpp

@PHONY: clean
clean:
	rm *.o
