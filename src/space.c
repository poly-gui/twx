#include "space.h"
#include "styledef.h"
#include <ctype.h>
#include <stdio.h>
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
  if ((end - space_value_str) != len) {
    return false;
  }

  if (!is_valid_space_value(value)) {
    return false;
  }

  *space = value;

  return true;
}

void parse_padding(const char *class_name, const char *matched_prefix,
                   struct twx_style *style) {
  double padding;
  const bool ok =
      parse_space_value(class_name + strlen(matched_prefix), &padding);
  if (!ok) {
    return;
  }

  if (strncmp("p-", matched_prefix, 2) == 0) {
    style->padding.top = padding;
    style->padding.bottom = padding;
    style->padding.left = padding;
    style->padding.right = padding;
  } else if (strncmp("pt-", matched_prefix, 3) == 0) {
    style->padding.top = padding;
  } else if (strncmp("pb-", matched_prefix, 3) == 0) {
    style->padding.bottom = padding;
  } else if (strncmp("pl-", matched_prefix, 3) == 0) {
    style->padding.left = padding;
  } else if (strncmp("pr-", matched_prefix, 3) == 0) {
    style->padding.right = padding;
  } else if (strncmp("px-", matched_prefix, 3) == 0) {
    style->padding.left = padding;
    style->padding.right = padding;
    style->padding.horizontal = padding;
  } else if (strncmp("py-", matched_prefix, 3) == 0) {
    style->padding.top = padding;
    style->padding.bottom = padding;
    style->padding.vertical = padding;
  }
}

void parse_margin(const char *class_name, const char *matched_prefix,
                  struct twx_style *style) {
  double margin;
  const bool ok =
      parse_space_value(class_name + strlen(matched_prefix), &margin);
  if (!ok) {
    return;
  }

  if (strncmp("m-", matched_prefix, 2) == 0) {
    style->margin.top = margin;
    style->margin.bottom = margin;
    style->margin.left = margin;
    style->margin.right = margin;
  } else if (strncmp("mt-", matched_prefix, 3) == 0) {
    style->margin.top = margin;
  } else if (strncmp("mb-", matched_prefix, 3) == 0) {
    style->margin.bottom = margin;
  } else if (strncmp("ml-", matched_prefix, 3) == 0) {
    style->margin.left = margin;
  } else if (strncmp("mr-", matched_prefix, 3) == 0) {
    style->margin.right = margin;
  } else if (strncmp("mx-", matched_prefix, 3) == 0) {
    style->margin.left = margin;
    style->margin.right = margin;
    style->margin.horizontal = margin;
  } else if (strncmp("my-", matched_prefix, 3) == 0) {
    style->margin.top = margin;
    style->margin.bottom = margin;
    style->margin.vertical = margin;
  }
}

void parse_width(const char *class_name, const char *matched_prefix,
                 struct twx_style *style) {
  const char *token = class_name + strlen(matched_prefix);

  double width;
  const bool ok = parse_space_value(token, &width);
  if (ok) {
    style->width.is_set = true;
    style->width.is_fixed = true;
    style->width.value.fixed_value = width;
    return;
  }

  enum twx_dimension_variant variant = twx_dimension_variant_from_str(token);
  if (variant >= 0) {
    style->width.is_set = true;
    style->width.is_fixed = false;
    style->width.value.variant = variant;
  }
}

void parse_height(const char *class_name, const char *matched_prefix,
                  struct twx_style *style) {
  const char *token = class_name + strlen(matched_prefix);

  double height;
  const bool ok = parse_space_value(token, &height);
  if (ok) {
    style->height.is_set = true;
    style->height.is_fixed = true;
    style->height.value.fixed_value = height;
    return;
  }

  enum twx_dimension_variant variant = twx_dimension_variant_from_str(token);
  if (variant >= 0) {
    style->height.is_set = true;
    style->height.is_fixed = false;
    style->height.value.variant = variant;
  }
}
