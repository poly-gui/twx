#ifndef TWX__TWX_H
#define TWX__TWX_H

#include <stdbool.h>
#include <stdint.h>

enum twx_modifier_code {
  TWX_MODIFIER_DARK = 1,

  // breakpoint modifiers
  TWX_MODIFIER_SM = 2,
  TWX_MODIFIER_MD = 4,
  TWX_MODIFIER_LG = 8,
  TWX_MODIFIER_XL = 16,
  TWX_MODIFIER_XXL = 32,

  // interaction modifiers
  TWX_MODIFIER_HOVER = 64,
};

char *twx_parse_to_json(const char *class_str);

#endif
