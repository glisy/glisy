#ifndef GLISY_EULER_H
#define GLISY_EULER_H

#include <glisy/vec3.h>

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif
#endif
