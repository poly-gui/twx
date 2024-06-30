#include "to_json.h"
#include "json_object.h"
#include "json_types.h"
#include "styledef.h"
#include "uthash.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define ADD_COLOR_VALUE_IF_SET(json, key, value)                               \
  if (value >= 0) {                                                            \
    char str[10];                                                              \
    twx_argb_to_hex_str(value, str);                                           \
    json_object_object_add(json, key, json_object_new_string(str));            \
  }

#define ADD_KEY_IF_VALUE_SET(json, type, key, value)                           \
  if (value != TWX_VALUE_NOT_SET) {                                            \
    json_object_object_add(json, key, json_object_new_##type(value));          \
  }

void twx_argb_to_hex_str(twx_argb argb, char *str) {
  uint32_t value = argb & 0xFFFFFFFF;
  sprintf(str, "#%X", value);
}

void twx_modifier_to_str(uint64_t modifiers, char *str) {
  sprintf(str, "%llU", modifiers);
}

void twx_style_to_json(const struct twx_style *style, json_object *json) {
  if (style == NULL || json == NULL) {
    return;
  }

  if (style->width.is_set) {
    if (style->width.is_fixed) {
      json_object_object_add(
          json, "width",
          json_object_new_double(style->width.value.fixed_value));
    } else {
      const char *name =
          twx_dimension_variant_to_str(style->width.value.variant);
      if (name != NULL) {
        json_object_object_add(json, "width", json_object_new_string(name));
      }
    }
  }
  if (style->height.is_set) {
    if (style->height.is_fixed) {
      json_object_object_add(
          json, "height",
          json_object_new_double(style->height.value.fixed_value));
    } else {
      const char *name =
          twx_dimension_variant_to_str(style->height.value.variant);
      if (name != NULL) {
        json_object_object_add(json, "height", json_object_new_string(name));
      }
    }
  }

  ADD_COLOR_VALUE_IF_SET(json, "backgroundColor", style->background_color);

  ADD_KEY_IF_VALUE_SET(json, double, "paddingTop", style->padding.top);
  ADD_KEY_IF_VALUE_SET(json, double, "paddingLeft", style->padding.left);
  ADD_KEY_IF_VALUE_SET(json, double, "paddingBottom", style->padding.bottom);
  ADD_KEY_IF_VALUE_SET(json, double, "paddingRight", style->padding.right);

  ADD_KEY_IF_VALUE_SET(json, double, "marginTop", style->margin.top);
  ADD_KEY_IF_VALUE_SET(json, double, "marginLeft", style->margin.left);
  ADD_KEY_IF_VALUE_SET(json, double, "marginBottom", style->margin.bottom);
  ADD_KEY_IF_VALUE_SET(json, double, "marginRight", style->margin.right);

  if (style->border.top.width != TWX_VALUE_NOT_SET) {
    json_object *border_obj = json_object_new_object();
    json_object_object_add(border_obj, "width",
                           json_object_new_double(style->border.top.width));
    ADD_COLOR_VALUE_IF_SET(border_obj, "color", style->border.top.color);
    json_object_object_add(json, "borderTop", border_obj);
  }

  if (style->border.left.width != TWX_VALUE_NOT_SET) {
    json_object *border_obj = json_object_new_object();
    json_object_object_add(border_obj, "width",
                           json_object_new_double(style->border.left.width));
    ADD_COLOR_VALUE_IF_SET(border_obj, "color", style->border.left.color);

    json_object_object_add(json, "borderLeft", border_obj);
  }

  if (style->border.bottom.width != TWX_VALUE_NOT_SET) {
    json_object *border_obj = json_object_new_object();
    json_object_object_add(border_obj, "width",
                           json_object_new_double(style->border.bottom.width));
    ADD_COLOR_VALUE_IF_SET(border_obj, "color", style->border.bottom.color);

    json_object_object_add(json, "borderBottom", border_obj);
  }

  if (style->border.right.width != TWX_VALUE_NOT_SET) {
    json_object *border_obj = json_object_new_object();
    json_object_object_add(border_obj, "width",
                           json_object_new_double(style->border.right.width));
    ADD_COLOR_VALUE_IF_SET(border_obj, "color", style->border.right.color);

    json_object_object_add(json, "borderRight", border_obj);
  }
}

char *styles_to_json(const struct twx_style *base_style,
                     struct twx_style_with_modifier *modifier_styles) {
  if (base_style == NULL) {
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

  if (modifier_styles != NULL) {
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
  }

  // the returned string will be freed by json_object_put later
  // so we need to make a copy here
  const char *json_str =
      json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY);
  const size_t len = strlen(json_str) + 1;
  char *output = (char *)malloc(sizeof(char) * len);
  if (output == NULL) {
    return NULL;
  }
  strncpy(output, json_str, len);

  json_object_put(root);

  return output;
}
