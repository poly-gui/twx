#include "space.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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

bool parse_space_value(const char *space_value_str, double *space) {
  if (space_value_str == NULL || space == NULL) {
    return false;
  }

  const size_t len = strlen(space_value_str);
  for (size_t i = 0; i < len; ++i) {
    if (!isdigit(space_value_str[i])) {
      return false;
    }
  }

  char *end;
  const double value = strtod(space_value_str, &end);
  if ((end - space_value_str + 1) != len) {
    return false;
  }

  if (!is_valid_space_value(value)) {
    return false;
  }

  *space = value;

  return true;
}

void parse_p(const char *class_name, struct TwxStyle *style) {
  double padding;
  const bool ok = parse_space_value(class_name + 2, &padding);
  if (ok) {
    style->padding.top = padding;
    style->padding.bottom = padding;
    style->padding.left = padding;
    style->padding.right = padding;
  }
}

void parse_pt(const char *class_name, struct TwxStyle *style) {
  double padding;
  const bool ok = parse_space_value(class_name + 2, &padding);
  if (ok) {
    style->padding.top = padding;
  }
}

void parse_pb(const char *class_name, struct TwxStyle *style) {
  double padding;
  const bool ok = parse_space_value(class_name + 2, &padding);
  if (ok) {
    style->padding.bottom = padding;
  }
}

void parse_pl(const char *class_name, struct TwxStyle *style) {
  double padding;
  const bool ok = parse_space_value(class_name + 2, &padding);
  if (ok) {
    style->padding.left = padding;
  }
}

void parse_pr(const char *class_name, struct TwxStyle *style) {
  double padding;
  const bool ok = parse_space_value(class_name + 2, &padding);
  if (ok) {
    style->padding.right = padding;
  }
}

void parse_m(const char *class_name, struct TwxStyle *style) {
  double margin;
  const bool ok = parse_space_value(class_name + 2, &margin);
  if (ok) {
    style->margin.top = margin;
    style->margin.bottom = margin;
    style->margin.left = margin;
    style->margin.right = margin;
  }
}

void parse_mt(const char *class_name, struct TwxStyle *style) {
  double margin;
  const bool ok = parse_space_value(class_name + 2, &margin);
  if (ok) {
    style->margin.top = margin;
  }
}

void parse_mb(const char *class_name, struct TwxStyle *style) {
  double margin;
  const bool ok = parse_space_value(class_name + 2, &margin);
  if (ok) {
    style->margin.bottom = margin;
  }
}

void parse_ml(const char *class_name, struct TwxStyle *style) {
  double margin;
  const bool ok = parse_space_value(class_name + 2, &margin);
  if (ok) {
    style->margin.left = margin;
  }
}

void parse_mr(const char *class_name, struct TwxStyle *style) {
  double margin;
  const bool ok = parse_space_value(class_name + 2, &margin);
  if (ok) {
    style->margin.right = margin;
  }
}
