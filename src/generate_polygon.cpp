#include "generate_polygon.hpp"

#include "polygon_bisect.hpp"

#include <iterator>

polygon_t generate_polygon(int n) {
    polygon_t polygon(4+n*10);
    auto itf = std::begin(polygon);
    auto itb = std::prev(std::end(polygon));
    *(itf++) = {-2,-2};
    *(itf++) = { 0, 0};
    *(itf++) = { 1,-1};
    *(itf++) = { 0,-2};
    for(int i=0; i<n; ++i) {
        double y = -i*4 - 2;
        *(itf++) = {-y,y};
        *(itf++) = {-(y-3),y-3};
        *(itf++) = {y-3+1,y-3};
        *(itf++) = {y-4+1,y-4};
        *(itb--) = {y-1,y-1};
        *(itb--) = {-(y-1)-1,y-1};
        *(itb--) = {-(y-2)-1,y-2};
        *(itb--) = {y-2,y-2};
        *(itb--) = {y-3,y-3};
        *(itb--) = {y-4,y-4};
    }
    return polygon;
}
