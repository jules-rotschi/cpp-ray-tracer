#include <cstdlib>

#include "utility.h"

double utility::random() {
  return std::rand() / (RAND_MAX + 1.0);
}

double utility::random(double min, double max) {
  return min + (max - min) * random();
}