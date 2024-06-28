#ifndef TWX__STYLEDEF_H
#define TWX__STYLEDEF_H

#include "modifiers.h"
#include "uthash.h"

#define TWX_VALUE_NOT_SET -1

#include <stdint.h>

typedef int64_t twx_argb;

struct twx_space {
  double top;
  double right;
  double bottom;
  double left;
};

struct TwxBorder {
  double width;
  twx_argb color;
};

struct twx_style {
  struct twx_space padding;
  struct twx_space margin;
  struct {
    struct TwxBorder top;
    struct TwxBorder bottom;
    struct TwxBorder left;
    struct TwxBorder right;
  } border;
  twx_argb background_color;
};

struct twx_style_with_modifier {
  uint64_t modifiers;
  struct twx_style style;
  UT_hash_handle hh;
};

void twx_style_initialize(struct twx_style *style);

#endif
