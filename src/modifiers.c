#include "modifiers.h"
#include "modifier_table.h"
#include <stdint.h>
#include <string.h>
#include <strings.h>

uint64_t extract_modifiers(char *class_name) {
  const char *delim = ":";

  char *modifier_str = strsep(&class_name, delim);
  uint64_t modifiers = 0;

  while (modifier_str != NULL) {
    const struct twx_modifier *modifier =
        find_modifier_code(modifier_str, strlen(modifier_str));
    if (modifier == NULL) {
      continue;
    }

    modifiers |= modifier->code;
  }

  return modifiers;
}
