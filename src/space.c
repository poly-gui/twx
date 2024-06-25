#include "space.h"

static const double space_values[34] = {
    0.0,  0.5,  1.0,  1.5,  2.0,  2.5,  3.0,  3.5,  4.0,  5.0,  6.0,  7.0,
    8.0,  9.0,  10.0, 11.0, 12.0, 14.0, 16.0, 20.0, 24.0, 28.0, 32.0, 36.0,
    40.0, 44.0, 48.0, 52.0, 56.0, 60.0, 64.0, 72.0, 80.0, 96.0};

bool is_valid_space_value(double value) {
  for (int i = 0; i < 34; ++i) {
    if (value == space_values[i]) {
      return true;
    }
  }
  return false;
}
