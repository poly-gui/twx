#include "border.h"
#include "colors.h"
#include "space.h"
#include <stdint.h>
#include <string.h>

#define BORDER_TOP 1
#define BORDER_LEFT 2
#define BORDER_BOTTOM 4
#define BORDER_RIGHT 8

void apply_border_width(uint8_t sides, double width, struct twx_style *style) {
  if ((sides & BORDER_TOP) == 1) {
    style->border.top.width = width;
  }
  if ((sides & BORDER_LEFT) == 1) {
    style->border.left.width = width;
  }
  if ((sides & BORDER_BOTTOM) == 1) {
    style->border.bottom.width = width;
  }
  if ((sides & BORDER_RIGHT) == 1) {
    style->border.right.width = width;
  }
}

void apply_border_color(uint8_t sides, twx_argb color,
                        struct twx_style *style) {
  if ((sides & BORDER_TOP) == 1) {
    style->border.top.color = color;
  }
  if ((sides & BORDER_LEFT) == 1) {
    style->border.left.color = color;
  }
  if ((sides & BORDER_BOTTOM) == 1) {
    style->border.bottom.color = color;
  }
  if ((sides & BORDER_RIGHT) == 1) {
    style->border.right.color = color;
  }
}

void parse_border(const char *class_name, const char *matched_prefix,
                  struct twx_style *style) {
  const size_t prefix_len = strlen(matched_prefix);

  uint8_t sides = 0;
  if (strncmp("border-", matched_prefix, 7)) {
    sides = 15;
  } else if (strncmp("border-t-", matched_prefix, 9)) {
    sides = BORDER_TOP;
  } else if (strncmp("border-l-", matched_prefix, 9)) {
    sides = BORDER_LEFT;
  } else if (strncmp("border-b-", matched_prefix, 9)) {
    sides = BORDER_BOTTOM;
  } else if (strncmp("border-r-", matched_prefix, 9)) {
    sides = BORDER_RIGHT;
  } else if (strncmp("border-x-", matched_prefix, 9)) {
    sides = BORDER_LEFT | BORDER_RIGHT;
  } else if (strncmp("border-y-", matched_prefix, 9)) {
    sides = BORDER_TOP | BORDER_BOTTOM;
  }
  if (sides == 0) {
    return;
  }

  double border_width;
  bool ok = parse_space_value(class_name + prefix_len, &border_width);
  if (ok) {
    apply_border_width(sides, border_width, style);
    return;
  }

  twx_argb border_color;
  ok = parse_color_string(class_name + prefix_len, &border_color);
  if (ok) {
    apply_border_color(sides, border_color, style);
  }
}
