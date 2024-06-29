#ifndef TWX__TO_JSON_H
#define TWX__TO_JSON_H

#include "styledef.h"

char *styles_to_json(const struct twx_style *base_style,
                     struct twx_style_with_modifier *modifier_styles);

#endif
