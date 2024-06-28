#include "styledef.h"

void twx_style_initialize(struct twx_style *style) {
  style->background_color = TWX_VALUE_NOT_SET;

  style->padding.top = TWX_VALUE_NOT_SET;
  style->padding.left = TWX_VALUE_NOT_SET;
  style->padding.bottom = TWX_VALUE_NOT_SET;
  style->padding.right = TWX_VALUE_NOT_SET;

  style->margin.top = TWX_VALUE_NOT_SET;
  style->margin.left = TWX_VALUE_NOT_SET;
  style->margin.bottom = TWX_VALUE_NOT_SET;
  style->margin.right = TWX_VALUE_NOT_SET;

  style->border.left.width = TWX_VALUE_NOT_SET;
  style->border.bottom.width = TWX_VALUE_NOT_SET;
  style->border.left.width = TWX_VALUE_NOT_SET;
  style->border.right.width = TWX_VALUE_NOT_SET;
}
