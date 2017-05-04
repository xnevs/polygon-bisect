#include <iostream>
#include <limits>

#include "polygon_bisect.hpp"

// declare for testing purposes
double left_area(const polygon_t & polygon, double split_x);

using namespace std;

int main() {
    polygon_t polygon{{0,7},{7,8},{8,0},{3,1},{6,2},{2,3},{5,4},{1,5},{4,6}};

    double x, la, a;

    x = polygon_bisect(polygon);
    cout << x << endl;
    a = left_area(polygon, numeric_limits<double>::infinity());
    la = left_area(polygon, x);
    cout << la << " " << a << endl;

    polygon_t p1{{0,1},{1,1},{1,0},{0,0}};
    x = polygon_bisect(p1);
    cout << x << endl;
    a = left_area(p1, numeric_limits<double>::infinity());
    la = left_area(p1, x);
    cout << la << " " << a << endl;
}
