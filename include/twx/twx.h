#ifndef TWX__TWX_H
#define TWX__TWX_H

#include <stdint.h>

typedef uint32_t TwxARGB;

struct TwxSpace {
  double top;
  double right;
  double bottom;
  double left;
};

struct TwxStyle {
  struct TwxSpace padding;
  struct TwxSpace margin;
  TwxARGB background_color;
};

bool twx_parse(char *class_str, struct TwxStyle *style);

#endif
