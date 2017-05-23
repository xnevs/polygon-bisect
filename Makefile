CXX=g++
CXX_FLAGS=-std=c++14 -O2 -march=native -mtune=native

all: example test-polygon-bisect

example: main.o polygon_bisect.o generate_polygon.o
	$(CXX) $(CXX_FLAGS) -o example main.o polygon_bisect.o generate_polygon.o

test-polygon-bisect: test-polygon-bisect.o polygon_bisect.o generate_polygon.o
	$(CXX) $(CXX_FLAGS) -o test-polygon-bisect test-polygon-bisect.o polygon_bisect.o generate_polygon.o

main.o: src/main.cpp src/polygon_bisect.hpp src/generate_polygon.hpp
	$(CXX) $(CXX_FLAGS) -c src/main.cpp

test-polygon-bisect.o: src/test-polygon-bisect.cpp src/polygon_bisect.hpp
	$(CXX) $(CXX_FLAGS) -c src/test-polygon-bisect.cpp

polygon_bisect.o: src/polygon_bisect.cpp src/polygon_bisect.hpp
	$(CXX) $(CXX_FLAGS) -c src/polygon_bisect.cpp

generate_polygon.o: src/generate_polygon.cpp src/generate_polygon.hpp
	$(CXX) $(CXX_FLAGS) -c src/generate_polygon.cpp

@PHONY: clean
clean:
	rm *.o
