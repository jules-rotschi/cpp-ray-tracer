#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
public:
  double min, max;

  Interval() = delete;
  Interval(double min, double max);

  double size() const;
  bool contains(double x) const;
  bool surrounds(double x) const;

  static const Interval empty, real_numbers, positive_real_numbers;
};

#endif