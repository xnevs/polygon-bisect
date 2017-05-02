#include <vector>
#include <utility>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <cmath>


using polygon_t = std::vector<std::pair<double,double>>;

std::pair<double,double> split_area(const polygon_t & polygon, double split_x) {
    auto n = polygon.size();

    double left_area = 0.0;
    double right_area = 0.0;

    for(polygon_t::size_type i=0; i<n; ++i) {
        auto x0 = polygon[i].first - split_x;
        auto y0 = polygon[i].second;
        auto x1 = polygon[(i+1)%n].first - split_x;
        auto y1 = polygon[(i+1)%n].second;

        if(x0 <= 0 && x1 <= 0) {
            left_area  += 0.5 * (x1 - x0) * (y1 + y0);
        } else if(x0 >= 0 && x1 >= 0) {
            right_area += 0.5 * (x1 - x0) * (y1 + y0);
        } else if(x0 < 0) {
            auto ax0 = std::abs(x0);
            auto ax1 = std::abs(x1);
            auto dx = ax0 + ax1;
            left_area  += 0.5 * (-x0) * (ax1/dx * y0 + ax0/dx * y1 + y0);
            right_area += 0.5 * ( x1) * (y1 + ax1/dx * y0 + ax0/dx * y1);
        } else if (x0 > 0) {
            auto ax0 = std::abs(x0);
            auto ax1 = std::abs(x1);
            auto dx = ax0 + ax1;
            left_area  += 0.5 * ( x1) * (y1 + ax1/dx * y0 + ax0/dx * y1);
            right_area += 0.5 * (-x0) * (ax1/dx * y0 + ax0/dx * y1 + y0);
        }
    }

    return {left_area, right_area};
}

double bisecting_line(const polygon_t & polygon) {
    auto n = polygon.size();
    std::vector<polygon_t::size_type> idxs(n);
    std::iota(begin(idxs),end(idxs),0);
    std::sort(begin(idxs),end(idxs), [&polygon](int a, int b) {
        return polygon[a] < polygon[b];
    });

    // bisection
    polygon_t::size_type left  = 0;
    polygon_t::size_type right = n-1;
    while(right - left > 1) {
        polygon_t::size_type mid = (left + right) / 2;
        auto split_x = polygon[idxs[mid]].first;
        double left_area, right_area;
        std::tie(left_area,right_area) = split_area(polygon,split_x);
        if(left_area < right_area) {
            left = mid;
        } else {
            right = mid;
        }
    }
    auto lx = polygon[idxs[left]].first;
    auto rx = polygon[idxs[right]].first;

    double lla, lra, rla, rra; // TODO: can use results from the while loop
    std::tie(lla,lra) = split_area(polygon,lx);
    std::tie(rla,rra) = split_area(polygon,rx);
    double area = lla + lra;

    // compute final line
    std::vector<double> left_intersections;
    for(polygon_t::size_type i=1; i<=n; ++i) {
        auto x1 = polygon[i-1].first - lx;
        auto y1 = polygon[i-1].second;
        auto x2 = polygon[i%n].first - lx;
        auto y2 = polygon[i%n].second;
        if( x1 * x2 <= 0 && (x1 < 0 || x2 < 0) ) {
            auto ax1 = std::abs(x1);
            auto ax2 = std::abs(x2);
            auto y = (ax2 * y1 + ax1 * y2) / (ax1 + ax2);
            left_intersections.push_back(y);
        }
    }
    std::sort(begin(left_intersections),end(left_intersections));

    std::vector<double> right_intersections;
    for(polygon_t::size_type i=1; i<=n; ++i) {
        auto x1 = polygon[i-1].first - rx;
        auto y1 = polygon[i-1].second;
        auto x2 = polygon[i%n].first - rx;
        auto y2 = polygon[i%n].second;
        if( x1 * x2 <= 0 && (x1 < 0 || x2 < 0) ) {
            auto ax1 = std::abs(x1);
            auto ax2 = std::abs(x2);
            auto y = (ax2 * y1 + ax1 * y2) / (ax1 + ax2);
            right_intersections.push_back(y);
        }
    }
    std::sort(begin(right_intersections),end(right_intersections));

    double left_height = 0.0;
    for(std::size_t i=0; i<left_intersections.size(); i+=2) {
        left_height += left_intersections[i+1] - left_intersections[i];
    }
    double right_height = 0.0;
    for(std::size_t i=0; i<right_intersections.size(); i+=2) {
        right_height += right_intersections[i+1] - right_intersections[i];
    }

    // solve the quadratic equation
    auto dx = rx - lx;
    auto a = (right_height - left_height) / (2 * dx);
    auto b = left_height / dx;
    auto c = lla - area/2;
    if(a == 0) {
        return -c / left_height;
    }
    auto D = b*b - 4*a*c;
    auto x1 = (-b + sqrt(D)) / (2*a);
    auto x2 = (-b - sqrt(D)) / (2*a);
    if(0 <= x1 && x1 <= dx) {
        return lx+x1;
    } else {
        return lx+x2;
    }
}

#include <iostream>
using namespace std;

int main() {
    polygon_t polygon{{0,7},{7,8},{8,0},{3,1},{6,2},{2,3},{5,4},{1,5},{4,6}};

    auto x = bisecting_line(polygon);
    cout << x << endl;
    auto areas = split_area(polygon, x);
    cout << areas.first << " " << areas.second << endl;
}
