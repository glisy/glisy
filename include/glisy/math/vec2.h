#ifndef GLISY_VEC2_H
#define GLISY_VEC2_H

#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <glisy/math/vec3.h>
#include <glisy/math/mat2.h>

/**
 * vec2 struct type.
 */

typedef struct vec2 vec2;
struct vec2 {
  float x;
  float y;
};

/**
 * vec2 initializer.
 */

#define vec2(x, y) ((vec2) {x, y})
#define vec2_create() vec2(0, 0)

/**
 * Clones and returns vec2.
 */

#define vec2_clone(vec) ((vec2) {vec.x, vec.y})

/**
 * Subtracts vec2 b from vec2 a.
 */

#define vec2_sub vec2_subtract
#define vec2_subtract(a, b) ((vec2) {(a.x - b.x), \
                                     (a.y - b.y)})

/**
 * Multiply two vec2.
 */

#define vec2_mul vec2_multiply
#define vec2_multiply(a, b) ((vec2) {(a.x * b.x), \
                                     (a.y * b.y)})

/**
 * Divide two vec2 a by vec2 b
 */

#define vec2_div vec2_divide
#define vec2_divide(a, b) ((vec2) {(a.x / b.x), \
                                   (a.y / b.y)})

/**
 * Copy vec2 b into vec2 a
 */

#define vec2_copy(a, b) (vec2) ({      \
  vec2 *tmp = &a;                      \
  (tmp->x = b.x);                      \
  (tmp->y = b.y);                      \
  (*tmp);                              \
})

/**
 * Sets x and y component of vec2.
 */

#define vec2_set(v, a, b) (vec2) ({    \
  vec2 *tmp = &v;                      \
  tmp->x = ((float) a);                \
  tmp->y = ((float) b);                \
  (*tmp);                              \
})

/**
 * Add two vectors together.
 */

#define vec2_add(a, b) ((vec2) {(a.x + b.x), \
                                (a.y + b.y)})

/**
 * Returns the maximum of two vec2 inputs.
 */

#define vec2_max(a, b) ((vec2) {fmaxf(a.x, b.x), \
                                fmaxf(a.y, b.y)})

/**
 * Returns the minimum of two vec2 inputs.
 */

#define vec2_min(a, b) ((vec2) {fminf(a.x, b.x), \
                                fminf(a.y, b.y)})

/**
 * Scale a vec2 by a scalar number.
 */

#define vec2_scale(a, s) ((vec2) {(a.x * s), \
                                  (a.y * s)})

/**
 * Calculates the Euclidean distance for a vec2.
 */

#define vec2_distance(a, b) (float) sqrt(powf(b.x - a.x, 2) +   \
                                         powf(b.y - a.y, 2))

/**
 * Calculates the squared distance for a vec2.
 */

#define vec2_distance_squared(a, b) (float) (powf(b.x - a.x, 2) +    \
                                             powf(b.y - a.y, 2))

/**
 * Calculates the length of a vec2.
 */

#define vec2_length(a) (float) (       \
  sqrt(powf(a.x, 2) + powf(a.y, 2))    \
)

/**
 * Calculates the squard length of a vec2.
 */

#define vec2_length_squared(a) (float) (powf(a.x, 2) + powf(a.y, 2))

/**
 * Returns the negation of a vec2.
 */

#define vec2_negate(a) ((vec2) {-1 * a.x, -1 * a.y})

/**
 * Calculates the inverse of a vec2.
 */

#define vec2_inverse(a) ((vec2) {(1.0f/a.x), (1.0f/a.y)})

/**
 * Returns a normalized vec2.
 */

#define vec2_normalize(a) (vec2) ({              \
  float len = (a.x * a.x) + (a.y * a.y);         \
  vec2 vec = vec2(0, 0);                         \
  if (len > 0) {                                 \
    len = (1/sqrt(len));                         \
    vec.x = (a.x * len);                         \
    vec.y = (a.y * len);                         \
  }                                              \
  (vec);                                         \
})

/**
 * Calculates the dot product of vec2 a
 * and vec2 b.
 */

#define vec2_dot(a, b) (float) ((a.x * b.x) + (a.y * b.y))

/**
 * Calculates the cross product of vec2 a
 * and vec2 b producing a vec3.
 */

#define vec2_cross(a, b) (vec3) ({               \
  vec3(0, 0, (a.x * b.y) - (a.y * b.x));         \
})

/**
 * Calculates a linear interpolation between
 * vec2 a and vec2 b with interpolation factor t.
 */

#define vec2_lerp(a, b, t) ((vec2) {a.x + t * (b.x - a.x), \
                                    a.y + t * (b.y - a.y)})

/**
 * Generates a random vec2 with scale.
 */

#define vec2_random(scale) (vec2) ({             \
  srand((unsigned int) time(NULL));              \
  float rad = 2.0 * M_PI * rand();               \
  (vec2(cosf(rad) * scale, sinf(rad) * scale));    \
})

/**
 * Transform vec2 with mat2.
 */

#define vec2_transform_mat2(a, m) (vec2) ({      \
  float x = m.m11 * a.x + m.m21 * a.y;           \
  float y = m.m12 * a.x + m.m22 * a.y;           \
  (vec2(x, y));                                  \
})

/**
 * Transform vec2 with mat3.
 */

#define vec2_transform_mat3(a, m) (vec2) ({      \
  float x = m.m11 * a.x + m.m21 * a.y + m.m31;   \
  float y = m.m12 * a.x + m.m22 * a.y + m.m32;   \
  (vec2(x, y));                                  \
})

// @TODO(werle) - mat4 transform

/**
 * Returns a string representation of vec2 a.
 */

#define vec2_string(a) (const char *) ({         \
  char str[BUFSIZ];                              \
  memset(str, 0, BUFSIZ);                        \
  sprintf(str, "vec2(%g, %g)", a.x, a.y);        \
  (strdup(str));                                 \
})

#endif
