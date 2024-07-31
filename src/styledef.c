#include "styledef.h"

void twx_style_initialize(struct twx_style *style) {
  style->width.is_set = false;
  style->width.is_set = false;

  style->background_color = TWX_VALUE_NOT_SET;

  style->padding.top = TWX_VALUE_NOT_SET;
  style->padding.left = TWX_VALUE_NOT_SET;
  style->padding.bottom = TWX_VALUE_NOT_SET;
  style->padding.right = TWX_VALUE_NOT_SET;
  style->padding.horizontal = TWX_VALUE_NOT_SET;
  style->padding.vertical = TWX_VALUE_NOT_SET;

  style->margin.top = TWX_VALUE_NOT_SET;
  style->margin.left = TWX_VALUE_NOT_SET;
  style->margin.bottom = TWX_VALUE_NOT_SET;
  style->margin.right = TWX_VALUE_NOT_SET;
  style->margin.horizontal = TWX_VALUE_NOT_SET;
  style->margin.vertical = TWX_VALUE_NOT_SET;

  style->border.top.width = TWX_VALUE_NOT_SET;
  style->border.left.width = TWX_VALUE_NOT_SET;
  style->border.bottom.width = TWX_VALUE_NOT_SET;
  style->border.right.width = TWX_VALUE_NOT_SET;
  style->border.top.color = TWX_VALUE_NOT_SET;
  style->border.left.color = TWX_VALUE_NOT_SET;
  style->border.bottom.color = TWX_VALUE_NOT_SET;
  style->border.right.color = TWX_VALUE_NOT_SET;
}

int compare_twx_style_with_modifier(void *a, void *b) {
  return ((struct twx_style_with_modifier *)a)->modifier_set.modifier_count -
         ((struct twx_style_with_modifier *)b)->modifier_set.modifier_count;
}

enum twx_dimension_variant twx_dimension_variant_from_str(const char *str) {
  if (strncmp("full", str, 4) == 0) {
    return TWX_DIMENSION_FULL;
  }

  if (strncmp("auto", str, 4) == 0) {
    return TWX_DIMENSION_AUTO;
  }

  return -1;
}

const char *twx_dimension_variant_to_str(enum twx_dimension_variant variant) {
  switch (variant) {
  case TWX_DIMENSION_AUTO:
    return "auto";

  case TWX_DIMENSION_FULL:
    return "full";

  default:
    return NULL;
  }
}
