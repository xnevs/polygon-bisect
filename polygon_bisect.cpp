#include "polygon_bisect.hpp"

#include <vector>
#include <utility>
#include <tuple>
#include <numeric>
#include <algorithm>
#include <cmath>

double left_area(const polygon_t & polygon, double split_x) {
    auto n = polygon.size();
    double area = 0.0;
    for(polygon_t::size_type i=0; i<n; ++i) {
        auto x0 = polygon[i].first;
        auto y0 = polygon[i].second;
        auto x1 = polygon[(i+1)%n].first;
        auto y1 = polygon[(i+1)%n].second;
        if(x0 <= split_x && x1 <= split_x) {
            area  += 0.5 * (x1 - x0) * (y1 + y0);
        } else if(x0 < split_x || x1 < split_x){
            auto ax0 = std::abs(x0 - split_x);
            auto ax1 = std::abs(x1 - split_x);
            auto dx = ax0 + ax1;
            if(x0 < split_x) {
                area += 0.5 * (split_x-x0) * (ax1/dx * y0 + ax0/dx * y1 + y0);
            } else {
                area += 0.5 * (x1-split_x) * (y1 + ax1/dx * y0 + ax0/dx * y1);
            }
        }
    }
    return area;
}

double polygon_height_at_x(const polygon_t & polygon, double x, bool lean_left) {
    auto n = polygon.size();
    std::vector<double> intersections;
    for(polygon_t::size_type i=1; i<=n; ++i) {
        auto x1 = polygon[i-1].first - x;
        auto y1 = polygon[i-1].second;
        auto x2 = polygon[i%n].first - x;
        auto y2 = polygon[i%n].second;
        if( x1 * x2 <= 0
             && (   ( lean_left && (x1 < 0 || x2 < 0))
                 || (!lean_left && (x1 > 0 || x2 > 0)))) {
            auto ax1 = std::abs(x1);
            auto ax2 = std::abs(x2);
            auto y = (ax2 * y1 + ax1 * y2) / (ax1 + ax2);
            intersections.push_back(y);
        }
    }
    std::sort(begin(intersections),end(intersections));
    double height = 0.0;
    for(std::size_t i=0; i<intersections.size(); i+=2) {
        height += intersections[i+1] - intersections[i];
    }
    return height;
}

double solve_quad_eqn(double a, double b, double c, double sx, double ex) {
    if(a != 0) {
        auto sqrtD = std::sqrt(b*b - 4*a*c);
        auto x1 = (-b + sqrtD) / (2*a);
        auto x2 = (-b - sqrtD) / (2*a);
        if(sx <= x1 && x1 <= ex) {
            return x1;
        } else {
            return x2;
        }
    } else {
        return -c / b;
    }
}

double polygon_bisect(const polygon_t & polygon) {
    auto n = polygon.size();
    std::vector<polygon_t::size_type> idxs(n);
    std::iota(begin(idxs),end(idxs),0);
    std::sort(begin(idxs),end(idxs), [&polygon](int a, int b) {
        return polygon[a] < polygon[b];
    });
    auto area = left_area(polygon, std::numeric_limits<double>::infinity());
    // bisection
    polygon_t::size_type left  = 0;
    double lla = 0.0;
    polygon_t::size_type right = n-1;
    while(right - left > 1) {
        polygon_t::size_type mid = left + (right - left) / 2;
        auto split_x = polygon[idxs[mid]].first;
        auto mla = left_area(polygon,split_x);
        if(mla < area/2) {
            left = mid;
            lla = mla;
        } else {
            right = mid;
        }
    }
    auto lx = polygon[idxs[left]].first;
    auto rx = polygon[idxs[right]].first;
    // compute final line
    double left_height  = polygon_height_at_x(polygon, lx, false);
    double right_height = polygon_height_at_x(polygon, rx, true);
    auto dx = rx - lx;
    auto a = (right_height - left_height) / (2 * dx);
    auto b = left_height;
    auto c = lla - area/2;
    return lx + solve_quad_eqn(a,b,c,0,dx);
}
