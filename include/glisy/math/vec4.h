#ifndef GLISY_VEC4_H
#define GLISY_VEC4_H

#include <time.h>
#include <math.h>
#include <stdlib.h>

/**
 * vec4 struct type.
 */

typedef struct vec4 vec4;
struct vec4 { float x; float y; float z; float w; };

/**
 * vec4 initializer.
 */

#define vec4(x, y, z, w) (vec4) {x, y, z, w}
#define vec4_create() vec4(0, 0, 0, 0)

#endif
