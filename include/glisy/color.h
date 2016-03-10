#ifndef GLISY_COLOR_H
#define GLISY_COLOR_H

#include <stdlib.h>

typedef struct GlisyColor GlisyColor;
struct GlisyColor {
  char *name;
  char *string;
  double r, g, b, a;
  uint32_t value;
};

void
glisyColorInit(GlisyColor *color, const char *name, uint32_t value);

const char *
glisyColorToString(const GlisyColor color);

const char *
glisyColorToName(const GlisyColor color);
#endif
