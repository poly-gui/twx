#ifndef TWX__MODIFIER_H
#define TWX__MODIFIER_H

#define TWX_NO_MODIFIER 0

#include <stdint.h>
#include <twx/twx.h>

struct twx_modifier {
  const char *modifier_name;
  enum twx_modifier_code code;
};

struct twx_modifier_set {
  int modifier_count;
  uint64_t modifiers;
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
struct twx_modifier_set extract_and_strip_modifiers(char **class_name);

#endif
