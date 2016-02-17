#ifndef GLISY_EULER_H
#define GLISY_EULER_H

#include "vec3.h"

/**
 * euler type
 */

typedef vec3 euler;

/**
 * euler initializer.
 */

#define euler(x, y, z) (euler) {x, y, z}
#define euler_create() euler(0, 0, 0)

/**
 * Clones and returns euler.
 */

#define euler_clone(e) ((euler) {e.x, e.y, e.z})
#endif
