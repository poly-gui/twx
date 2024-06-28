#include "modifiers.h"
#include "modifier_table.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

uint64_t extract_and_strip_modifiers(char **class_name) {
  if (class_name == NULL) {
    return 0;
  }

  const char *delim = ":";

  char *modifier_str = strsep(class_name, delim);
  uint64_t modifiers = 0;

  if (class_name == NULL) {
    return 0;
  }

  while (modifier_str != NULL && *class_name != NULL) {
    const struct twx_modifier *modifier =
        find_modifier_code(modifier_str, strlen(modifier_str));
    if (modifier == NULL) {
      continue;
    }

    modifiers |= modifier->code;
    modifier_str = strsep(class_name, delim);
  }

  *class_name = modifier_str;

  return modifiers;
}
