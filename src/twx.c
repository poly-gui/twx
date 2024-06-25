#include "colors.h"
#include "space.h"
#include "strutil.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include <time.h>
#include <twx/twx.h>

typedef void (*ClassParserFunc)(const char *class_name, struct TwxStyle *style);

struct ClassParserEntry {
  char *class_prefix;
  ClassParserFunc parse;
};

static const struct ClassParserEntry parser_funcs[9] = {
    {"bg-", &parse_bg},

    {"p-", &parse_p},   {"pt-", &parse_pt},
    {"pb-", &parse_pb}, {"pr-", &parse_pr},

    {"m-", &parse_m},   {"mt-", &parse_mt},
    {"mb-", &parse_mb}, {"mr-", &parse_mr},
};

void parse_class(char *class, struct TwxStyle *style) {
  for (size_t i = 0; i < 9; ++i) {
    if (str_starts_with(class, parser_funcs[i].class_prefix)) {
      parser_funcs[i].parse(class, style);
      return;
    }
  }
}

bool twx_parse(char *class_str, struct TwxStyle *style) {
  if (class_str == NULL || style == NULL) {
    return false;
  }

  const char *delim = " ";

  char *class = strsep(&class_str, delim);
  while (class != NULL) {
    parse_class(class, style);
    class = strsep(&class_str, delim);
  }

  return true;
}
