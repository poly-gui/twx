#include "to_json.h"
#include "json_object.h"
#include "json_types.h"
#include "styledef.h"
#include "uthash.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void twx_argb_to_hex_str(twx_argb argb, char *str) {
  uint32_t value = argb & 0xFFFFFFFF;
  sprintf(str, "#%X", value);
}

/**
 * Converts the given set of tailwind modifier codes into a string.
 * For example, given TWX_MODIFIER_DARK | TWX_MODIFIER_SM, this produces:
 * "dark:sm"
 */
void twx_modifier_to_str(uint64_t modifiers, char *str) {
  sprintf(str, "%llU", modifiers);
}

void twx_style_to_json(const struct twx_style *style, json_object *json) {
  if (style == NULL || json == NULL) {
    return;
  }

  char bg_color_str[10];
  twx_argb_to_hex_str(style->background_color, bg_color_str);
  json_object_object_add(json, "backgroundColor",
                         json_object_new_string(bg_color_str));

  json_object_object_add(json, "paddingTop",
                         json_object_new_double(style->padding.top));
  json_object_object_add(json, "paddingLeft",
                         json_object_new_double(style->padding.left));
  json_object_object_add(json, "paddingBottom",
                         json_object_new_double(style->padding.bottom));
  json_object_object_add(json, "paddingRight",
                         json_object_new_double(style->padding.right));

  json_object_object_add(json, "marginTop",
                         json_object_new_double(style->margin.top));
  json_object_object_add(json, "marginLeft",
                         json_object_new_double(style->margin.left));
  json_object_object_add(json, "marginBottom",
                         json_object_new_double(style->margin.bottom));
  json_object_object_add(json, "marginRight",
                         json_object_new_double(style->margin.right));
}

const char *styles_to_json(const struct twx_style *base_style,
                           struct twx_style_with_modifier *modifier_styles) {
  if (base_style == NULL || modifier_styles == NULL) {
    return NULL;
  }

  json_object *root = json_object_new_object();
  if (root == NULL) {
    return NULL;
  }

  json_object *base_style_json = json_object_new_object();
  if (base_style_json == NULL) {
    return NULL;
  }

  twx_style_to_json(base_style, base_style_json);
  json_object_object_add(root, "0", base_style_json);

  struct twx_style_with_modifier *modifier_style, *tmp;
  HASH_ITER(hh, modifier_styles, modifier_style, tmp) {
    json_object *style_json = json_object_new_object();
    if (style_json == NULL) {
      return NULL;
    }

    twx_style_to_json(&modifier_style->style, style_json);

    char modifier_str[32];
    twx_modifier_to_str(modifier_style->modifiers, modifier_str);
    json_object_object_add(root, modifier_str, style_json);

    free(modifier_style);
  }

  // the returned string will be freed by json_object_put later
  // so we need to make a copy here
  const char *json_str = json_object_to_json_string(root);
  const size_t len = strlen(json_str) + 1;
  char *output = (char *)malloc(sizeof(char) * len);
  if (output == NULL) {
    return NULL;
  }
  strncpy(output, json_str, len);

  json_object_put(root);

  return output;
}
