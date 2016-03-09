#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rgba/rgba.h>
#include <glisy/color.h>

void
glisy_color_init(glisy_color *color, const char *name, uint32_t value) {
  rgba_t rgba;
  uint32_t tmp;
  if (!color) return;

  if (!color->name) {
    color->name = "";
  }

  if (!color->string) {
    color->string = "";
  }

  if (name && value == 0) {
    if ('#' == name[0]) {
      color->string = strdup(name);
    } else if (name == strstr(name, "rgb")) {
      color->string = strdup(name);
    } else {
      color->name = strdup(name);
    }

    short ok = 0;
    tmp = rgba_from_string(name, &ok);
    if (tmp) value = tmp;
  }

  rgba = rgba_new(value);
  color->r = rgba.r;
  color->g = rgba.g;
  color->b = rgba.b;
  color->a = rgba.a;
  color->value = value;
}

const char *
glisy_color_to_name(const glisy_color color) {
  if (strlen(color.name)) return strdup(color.name);
  if (strlen(color.string)) return strdup(color.string);
  rgba_t rgba = (rgba_t) { color.r, color.g, color.b, color.a };
  rgba_to_string(rgba, (char *) color.name, BUFSIZ);
  rgba_to_string(rgba, (char *) color.string, BUFSIZ);
  return strdup(color.name);
}

const char *
glisy_color_to_string(const glisy_color color) {
  if (strlen(color.string)) return strdup(color.string);
  rgba_t rgba = (rgba_t) { color.r, color.g, color.b, color.a };
  rgba_to_string(rgba, (char *) color.string, BUFSIZ);
  return strdup(color.string);
}
