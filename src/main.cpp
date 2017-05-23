#include <iostream>
#include <limits>
#include <algorithm>
#include <chrono>
#include <cstdlib>

#include "polygon_bisect.hpp"
#include "generate_polygon.hpp"

// declare for testing purposes
double left_area(const polygon_t & polygon, double split_x);

using namespace std;

int main(int argc, char *argv[]) {
    
    polygon_t polygon = generate_polygon(4);

    double x, la, a;
    x = polygon_bisect(polygon);
    cout << "x = " << x << endl;

    a = left_area(polygon, numeric_limits<double>::infinity());
    cout << "whole area: " << a << endl;
    la = left_area(polygon, x);
    cout << "area left of (x = " << x << "): " << la << endl;
}
