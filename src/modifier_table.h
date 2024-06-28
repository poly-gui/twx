#ifndef TWX__MODIFIER_TABLE_H
#define TWX__MODIFIER_TABLE_H

#include "modifiers.h"

static unsigned int hash_modifier_str(register const char *str,
                                      register unsigned int len);

const struct twx_modifier *find_modifier_code(register const char *str,
                                              register unsigned int len);

#endif
