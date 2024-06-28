#ifndef TWX__MODIFIER_H
#define TWX__MODIFIER_H

#define TWX_NO_MODIFIER 0

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

struct twx_modifier {
  const char *modifier_name;
  enum twx_modifier_code code;
};

/**
 * Extracts all tailwind modifiers in the received class name
 * and returns an integer which is a union of all the numbers representing the
 * modifiers.
 *
 * Array isn't returned here because modifiers may appear in any order in the
 * class name, but twx requires them to be ordered for easier interpretation.
 * Instead, storing the modifiers in an integer sorts them automatically based
 * on their assigned code.
 */
uint64_t extract_modifiers(char *class_name);

#endif
