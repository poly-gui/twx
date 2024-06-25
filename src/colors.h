#ifndef TWX__COLORS_H
#define TWX__COLORS_H

#include "twx/twx.h"
#include <stdint.h>

bool get_tw_color(const char *color_name, const int color_num, TwxARGB *color);

bool parse_color_string(const char *color_str, TwxARGB *color);

void parse_bg(const char *class_name, struct TwxStyle *style);

#endif
