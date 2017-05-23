# polygon-bisect

A program that, given a polygon, calculates a vertical line, such that the area of the polygon to the left of the line is equal to the area of the polygon to the right of the line.

## Usage

The function `polygon_bisect` defined in `src/polygon_bisect.cpp` accepts a polygon (given as a `vector` of vertices) and returns a single value x0, that defines the bisecting line x = x0.

An example can be found in the file `src/main.cpp`.

## Building

To build the example run `make` in the root folder.

A C++ compiler wth C++14 support is required. If you wish to use a compiler other than `g++`, change the `CXX` variable in the `Makefile`.

The result of building are the `./example` and the `./test-polygon-bisect` binaries.
