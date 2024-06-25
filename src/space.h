#ifndef TWX__SPACE_H
#define TWX__SPACE_H

#include "twx/twx.h"
#include <stdbool.h>

bool is_valid_space_value(double value);

bool parse_space_value(const char *space_value_str, double *space);

void parse_p(const char *class_name, struct TwxStyle *style);
void parse_pt(const char *class_name, struct TwxStyle *style);
void parse_pb(const char *class_name, struct TwxStyle *style);
void parse_pl(const char *class_name, struct TwxStyle *style);
void parse_pr(const char *class_name, struct TwxStyle *style);

void parse_m(const char *class_name, struct TwxStyle *style);
void parse_mt(const char *class_name, struct TwxStyle *style);
void parse_mb(const char *class_name, struct TwxStyle *style);
void parse_ml(const char *class_name, struct TwxStyle *style);
void parse_mr(const char *class_name, struct TwxStyle *style);

#endif
