#include "interval.h"
#include "utility.h"

Interval::Interval(double min, double max)
  : min(min), max(max) {}
  
double Interval::size() const {
  return max - min;
}

bool Interval::contains(double x) const {
  return min <= x && x <= max;
}

bool Interval::surrounds(double x) const {
  return min < x && x < max;
}

const Interval Interval::empty(+infinity, -infinity);
const Interval Interval::real_numbers(-infinity, +infinity);
const Interval Interval::positive_real_numbers(0, +infinity);