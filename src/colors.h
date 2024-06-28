#ifndef TWX__COLORS_H
#define TWX__COLORS_H

#include "styledef.h"
#include <stdint.h>

bool get_tw_color(const char *color_name, const int color_num, twx_argb *color);

bool parse_color_string(const char *color_str, twx_argb *color);

void parse_bg(const char *class_name, const char *matched_prefix,
              struct twx_style *style);

#endif
