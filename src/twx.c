#include "colors.h"
#include "space.h"
#include "strutil.h"
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include <time.h>
#include <twx/twx.h>

bool parse_color_string(char *color_str, TwxARGB *color) {
  char *hyphen = strchr(color_str, '-');
  if (hyphen == NULL) {
    return NULL;
  }

  const size_t split_i = (size_t)(hyphen - color_str);
  char *color_name = substr(color_str, 0, split_i);
  if (color_name == NULL) {
    return false;
  }

  char *color_num_str = substr(color_str, split_i, strlen(color_str));
  if (color_num_str == NULL) {
    return false;
  }

  int color_num = atoi(color_num_str);
  if (color_num == 0) {
    return 0;
  }

  return get_tw_color(color_name, color_num, color);
}

bool parse_space_value(char *space_value_str, double *space) {
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

void parse_class(char *class, struct TwxStyle *style) {
  if (str_starts_with(class, "bg-")) {
    parse_color_string(class + 3, &style->background_color);
  } else if (str_starts_with(class, "p-")) {
    double padding;
    const bool ok = parse_space_value(class + 2, &padding);
    if (ok) {
      style->padding.top = padding;
      style->padding.bottom = padding;
      style->padding.left = padding;
      style->padding.right = padding;
    }
  } else if (str_starts_with(class, "pt-")) {
    double padding;
    const bool ok = parse_space_value(class + 2, &padding);
    if (ok) {
      style->padding.top = padding;
    }
  } else if (str_starts_with(class, "pb-")) {
    double padding;
    const bool ok = parse_space_value(class + 2, &padding);
    if (ok) {
      style->padding.bottom = padding;
    }
  } else if (str_starts_with(class, "pl-")) {
    double padding;
    const bool ok = parse_space_value(class + 2, &padding);
    if (ok) {
      style->padding.left = padding;
    }
  } else if (str_starts_with(class, "pr-")) {
    double padding;
    const bool ok = parse_space_value(class + 2, &padding);
    if (ok) {
      style->padding.right = padding;
    }
  }
}

bool twx_parse(char *class_str, struct TwxStyle *style) {
  if (class_str == NULL || style == NULL) {
    return false;
  }

  const char *delim = " ";

  char *class = strsep(&class_str, delim);
  while (class != NULL) {
    parse_class(class, style);
    class = strsep(&class_str, delim);
  }

  return true;
}
