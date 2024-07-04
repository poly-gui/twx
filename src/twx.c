#include "border.h"
#include "colors.h"
#include "modifiers.h"
#include "space.h"
#include "strutil.h"
#include "styledef.h"
#include "to_json.h"
#include "uthash.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <twx/twx.h>

#define PARSER_FUNC_COUNT 18

typedef void (*ClassParserFunc)(const char *class_name,
                                const char *matched_prefix,
                                struct twx_style *style);

struct ClassParser {
  char *class_prefix;
  ClassParserFunc parse;
};

static const struct ClassParser parsers[PARSER_FUNC_COUNT] = {
    {"bg-", &parse_bg},

    {"w-", &parse_width},         {"h-", &parse_height},

    {"p-", &parse_padding},       {"pt-", &parse_padding},
    {"pb-", &parse_padding},      {"pr-", &parse_padding},

    {"m-", &parse_margin},        {"mt-", &parse_margin},
    {"mb-", &parse_margin},       {"mr-", &parse_margin},

    {"border-", &parse_border},   {"border-t-", &parse_border},
    {"border-b-", &parse_border}, {"border-l-", &parse_border},
    {"border-r-", &parse_border}, {"border-x-", &parse_border},
    {"border-y-", &parse_border},
};

void parse_class(char *class, struct twx_style *style) {
  for (size_t i = 0; i < PARSER_FUNC_COUNT; ++i) {
    const char *prefix = parsers[i].class_prefix;
    if (str_starts_with(class, prefix)) {
      parsers[i].parse(class, prefix, style);
      return;
    }
  }
}

char *twx_parse_to_json(const char *class_str) {
  if (class_str == NULL) {
    return NULL;
  }

  const size_t class_str_len = strlen(class_str);
  char *class_str_cpy = (char *)malloc((class_str_len + 1) * sizeof(char));
  if (class_str_cpy == NULL) {
    return NULL;
  }
  strcpy(class_str_cpy, class_str);

  const char *delim = " ";

  struct twx_style base_style;
  twx_style_initialize(&base_style);

  struct twx_style_with_modifier *modifier_styles = NULL;

  char *class = strsep(&class_str_cpy, delim);
  while (class != NULL) {
    const struct twx_modifier_set modifier_set =
        extract_and_strip_modifiers(&class);

    if (modifier_set.modifier_count == 0) {
      parse_class(class, &base_style);
    } else {
      struct twx_style_with_modifier *style_with_modifier;

      // find if there is an existing style object for this combination of
      // variants if not, create one
      HASH_FIND_INT(modifier_styles, &modifier_set.modifiers,
                    style_with_modifier);
      if (style_with_modifier == NULL) {
        style_with_modifier = (struct twx_style_with_modifier *)malloc(
            sizeof(struct twx_style_with_modifier));
        if (style_with_modifier == NULL) {
          return NULL;
        }

        HASH_ADD_INT(modifier_styles, modifier_set.modifiers,
                     style_with_modifier);
      }

      style_with_modifier->modifier_set = modifier_set;

      twx_style_initialize(&style_with_modifier->style);
      parse_class(class, &style_with_modifier->style);
    }

    class = strsep(&class_str_cpy, delim);
  }

  HASH_SORT(modifier_styles, compare_twx_style_with_modifier);

  char *json = styles_to_json(&base_style, modifier_styles);

  free(class_str_cpy);

  return json;
}
