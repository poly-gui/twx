#ifndef TWX__SPACE_H
#define TWX__SPACE_H

#include "styledef.h"
#include <stdbool.h>

bool is_valid_space_value(double value);

bool parse_space_value(const char *space_value_str, double *space);

void parse_padding(const char *class_name, const char *matched_prefix,
                   struct twx_style *style);

void parse_margin(const char *class_name, const char *matched_prefix,
                  struct twx_style *style);

void parse_width(const char *class_name, const char *matched_prefix,
                 struct twx_style *style);

void parse_height(const char *class_name, const char *matched_prefix,
                  struct twx_style *style);

#endif
