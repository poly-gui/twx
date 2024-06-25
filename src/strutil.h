#ifndef TWX__STRUTIL_H
#define TWX__STRUTIL_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t strhash(const char *str);

char *substr(const char *str, size_t start, size_t end);

bool str_starts_with(const char *str, const char *prefix);

#endif
