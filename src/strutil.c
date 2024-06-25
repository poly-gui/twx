#include "strutil.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

uint32_t strhash(const char *str) {
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

char *substr(const char *str, size_t start, size_t end) {
  if (str == NULL || start < 0 || end <= start || end > strlen(str)) {
    return NULL;
  }

  const size_t substr_len = end - start;
  // + 1 for the null char at the end
  char *sub = (char *)malloc((substr_len + 1) * sizeof(char));
  if (sub == NULL) {
    return NULL;
  }

  strncpy(sub, str + start, substr_len);
  sub[substr_len] = '\0';

  return sub;
}

bool str_starts_with(const char *str, const char *prefix) {
  if (strncmp(str, prefix, strlen(prefix)) == 0)
    return true;
  return false;
}
