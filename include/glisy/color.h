#ifndef GLISY_COLOR_H
#define GLISY_COLOR_H

#include <stdlib.h>

typedef struct glisy_color glisy_color;
struct glisy_color {
  char *name;
  char *string;
  double r, g, b, a;
  uint32_t value;
};

void
glisy_color_init(glisy_color *color, const char *name, uint32_t value);

const char *
glisy_color_to_string(const glisy_color color);

const char *
glisy_color_to_name(const glisy_color color);
#endif
