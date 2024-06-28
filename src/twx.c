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

#define PARSER_FUNC_COUNT 16

typedef void (*ClassParserFunc)(const char *class_name,
                                const char *matched_prefix,
                                struct twx_style *style);

struct ClassParser {
  char *class_prefix;
  ClassParserFunc parse;
};

static const struct ClassParser parsers[PARSER_FUNC_COUNT] = {
    {"bg-", &parse_bg},

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

const char *twx_parse_to_json(char *class_str) {
  if (class_str == NULL) {
    return NULL;
  }

  const char *delim = " ";

  struct twx_style base_style;
  twx_style_initialize(&base_style);

  struct twx_style_with_modifier *modifier_styles = NULL;

  char *class = strsep(&class_str, delim);
  while (class != NULL) {
    const uint64_t modifiers = extract_and_strip_modifiers(&class);
    if (modifiers == TWX_NO_MODIFIER) {
      parse_class(class, &base_style);
    } else {
      struct twx_style_with_modifier *style_with_modifier =
          (struct twx_style_with_modifier *)malloc(
              sizeof(struct twx_style_with_modifier));

      style_with_modifier->modifiers = modifiers;

      twx_style_initialize(&style_with_modifier->style);
      parse_class(class, &style_with_modifier->style);

      HASH_ADD_INT(modifier_styles, modifiers, style_with_modifier);
    }

    class = strsep(&class_str, delim);
  }

  const char *json = styles_to_json(&base_style, modifier_styles);

  return json;
}
