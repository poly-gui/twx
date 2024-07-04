#include "modifiers.h"
#include "modifier_table.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

struct twx_modifier_set extract_and_strip_modifiers(char **class_name) {
  struct twx_modifier_set modifier_set;
  modifier_set.modifier_count = 0;
  modifier_set.modifiers = 0;

  if (class_name == NULL) {
    return modifier_set;
  }

  const char *delim = ":";

  char *modifier_str = strsep(class_name, delim);
  uint64_t modifiers = 0;

  if (class_name == NULL) {
    return modifier_set;
  }

  while (modifier_str != NULL && *class_name != NULL) {
    const struct twx_modifier *modifier =
        find_modifier_code(modifier_str, strlen(modifier_str));
    if (modifier == NULL) {
      continue;
    }

    modifier_set.modifier_count++;
    modifier_set.modifiers |= modifier->code;
    modifier_str = strsep(class_name, delim);
  }

  *class_name = modifier_str;

  return modifier_set;
}
