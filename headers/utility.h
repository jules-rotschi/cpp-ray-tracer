#ifndef UTILITY_H
#define UTILITY_H

#include <limits>
#include <numbers>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = std::numbers::pi;

namespace utility {
  double random();
  double random(double min, double max);
}


#endif