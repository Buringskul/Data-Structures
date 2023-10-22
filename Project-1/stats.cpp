#include "stats.h"  // needed for assert()
#include <assert.h> // header file for the class
#include <cmath>
using namespace main_savitch_2C; // defining the namespace

statistician::statistician() {
  total = 0;
  count = 0;
  tinyest = INFINITY;
  largest = -INFINITY;
}

void statistician::next(double r) {
  total += r;
  if (r < tinyest) {
    tinyest = r;
  }
  if (r > largest) {
    largest = r;
  }
  count++;
}

double statistician::mean() const {
  assert(count > 0);
  return (total / count);
}

int statistician::length() const { return count; }

void statistician::reset() {
  total = 0;
  count = 0;
  tinyest = INFINITY;
  largest = -INFINITY;
}

double statistician::minimum() const { return tinyest; }

double statistician::maximum() const { return largest; }

double statistician::sum() const { return total; }

statistician main_savitch_2C::operator+(const statistician &s,
                                        const statistician &t) {
  statistician u;
  u.count = s.count + t.count;
  u.total = s.total + t.total;

  if (s.tinyest < t.tinyest) {
    u.tinyest = s.tinyest;
  } else {
    u.tinyest = t.tinyest;
  }

  if (s.largest > t.largest) {
    u.largest = s.largest;
  } else {
    u.largest = t.largest;
  }
  return u;
}

statistician main_savitch_2C::operator*(double scale, const statistician &s) {
  statistician s1;

  s1.total = scale * s.total;
  s1.count = s.count;

  if (scale > 0) {
    s1.tinyest = scale * s.tinyest;
    s1.largest = scale * s.largest;
  } else {
    s1.tinyest = scale * s.largest;
    s1.largest = scale * s.tinyest;
  }
  return s1;
}

bool main_savitch_2C::operator==(const statistician &s1,
                                 const statistician &s2) {
  if (s1.length() == 0 && s2.length() == 0) {
    return true;
  }
  if (s1.length() == s2.length() && s1.minimum() == s2.minimum() &&
      s1.maximum() == s2.maximum() && s1.mean() == s2.mean() &&
      s1.sum() == s2.sum()) {
    return true;
  } 
  else {
    return false;
  }
}