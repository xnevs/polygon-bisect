#ifndef POLYGON_BISECT_HPP
#define POLYGON_BISECT_HPP

#include <vector>
#include <utility>

using polygon_t = std::vector<std::pair<double,double>>;

double polygon_bisect(const polygon_t & polygon);

#endif // POLYGON_BISECT_HPP
