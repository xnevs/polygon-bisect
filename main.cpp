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
    
    polygon_t polygon = generate_polygon(atoi(argv[1]));

    auto num_rep = max(static_cast<std::size_t>(5),4000000/polygon.size());
    vector<double> results(num_rep);

    chrono::time_point<chrono::steady_clock> start, end;
    start = chrono::steady_clock::now();
    for(int i=0; i<num_rep; ++i) {
        double x, la, a;
        results[i] = polygon_bisect(polygon);
        //a = left_area(polygon, numeric_limits<double>::infinity());
        //la = left_area(polygon, x);
        //cout << la << " " << a << endl;
    }
    end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start);

    cerr << polygon.size() << " " << num_rep << " " << elapsed.count() << endl;
    
    for(auto x : results) {
        cout << x << endl;
    }
}
