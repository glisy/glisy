#ifndef GLISY_VEC3_H
#define GLISY_VEC3_H

#include <time.h>
#include <math.h>
#include <stdlib.h>

/**
 * vec3 struct type.
 */

typedef struct vec3 vec3;
struct vec3 { float x; float y; float z; };

/**
 * vec3 initializer.
 */

#define vec3(x, y, z) (vec3) {x, y, z}
#define vec3_create() vec3(0, 0, 0)

/**
 * Clones and returns vec3.
 */

#define vec3_clone(vec) ((vec3) {vec.x, vec.y, vec.z})

/**
 * Subtracts vec3 b from vec3 a.
 */

#define vec3_sub vec3_subtract
#define vec3_subtract(a, b) ((vec3) {(a.x - b.x), \
                                     (a.y - b.y), \
                                     (a.z - b.z)})

/**
 * Multiply two vec3.
 */

#define vec3_mul vec3_multiply
#define vec3_multiply(a, b) ((vec3) {(a.x * b.x), \
                                     (a.y * b.y), \
                                     (a.z * b.z)})

/**
 * Divide two vec3 a by vec3 b
 */

#define vec3_div vec3_divide
#define vec3_divide(a, b) ((vec3) {(a.x / b.x), \
                                   (a.y / b.y), \
                                   (a.z / b.z)})

/**
 * Copy vec3 b into vec3 a
 */

#define vec3_copy(a, b) (vec3) ({      \
  vec3 *tmp = &a;                      \
  (tmp->x = b.x);                      \
  (tmp->y = b.y);                      \
  (tmp->z = b.z);                      \
  (*tmp);                              \
})

/**
 * Sets x and y component of vec3.
 */

#define vec3_set(v, a, b, c) (vec3) ({  \
  vec3 *tmp = &v;                      \
  tmp->x = ((float) a);                \
  tmp->y = ((float) b);                \
  tmp->z = ((float) c);                \
  (*tmp);                              \
})

/**
 * Add two vectors together.
 */

#define vec3_add(a, b) ((vec3) {(a.x + b.x), \
                                (a.y + b.y), \
                                (a.z + b.z)})

/**
 * Returns the maximum of two vec3 inputs.
 */

#define vec3_max(a, b) ((vec3) {fmaxf(a.x, b.x), \
                                fmaxf(a.y, b.y), \
                                fmaxf(a.z, b.z)})

/**
 * Returns the minimum of two vec3 inputs.
 */

#define vec3_min(a, b) ((vec3) {fminf(a.x, b.x), \
                                fminf(a.y, b.y), \
                                fminf(a.z, b.z)})

/**
 * Scale a vec3 by a scalar number.
 */

#define vec3_scale(a, s) ((vec3) {(a.x * s), \
                                  (a.y * s), \
                                  (a.z * s)})

/**
 * Calculates the Euclidean distance for a vec3.
 */

#define vec3_distance(a, b) (float) sqrt(pow(b.x - a.x, 2) + \
                                         pow(b.y - a.y, 2) + \
                                         pow(b.z - a.z, 2))

/**
 * Calculates the squared distance for a vec3.
 */

#define vec3_distance_squared(a, b) (float) (powf(b.x - a.x, 2) +    \
                                             powf(b.y - a.y, 2) +    \
                                             powf(b.z - a.z, 2))

/**
 * Calculates the length of a vec3.
 */

#define vec3_length(a) (float) sqrt(powf(a.x, 2) + \
                                    powf(a.y, 2) + \
                                    powf(a.z, 2))

/**
 * Calculates the squard length of a vec3.
 */

#define vec3_length_squared(a) (float) (powf(a.x, 2) + \
                                        powf(a.y, 2) + \
                                        powf(a.z, 2))

/**
 * Returns the negation of a vec3.
 */

#define vec3_negate(a) ((vec3) {-1 * a.x, \
                                -1 * a.y, \
                                -1 * a.z})

/**
 * Calculates the inverse of a vec3.
 */

#define vec3_inverse(a) ((vec3) {(1.0f/a.x), \
                                 (1.0f/a.y), \
                                 (1.0f/a.z)})

/**
 * Returns a normalized vec3.
 */

#define vec3_normalize(a) (vec3) ({                        \
  float len = (a.x * a.x) + (a.y * a.y) + (a.z * a.z);     \
  vec3 vec;                                                \
  if (len > 0) {                                           \
    len = (1/sqrt(len));                                   \
    vec.x = (a.x * len);                                   \
    vec.y = (a.y * len);                                   \
    vec.z = (a.z * len);                                   \
  }                                                        \
  (vec);                                                   \
})

/**
 * Calculates the dot product of vec3 a
 * and vec3 b.
 */

#define vec3_dot(a, b) (float) ((a.x * b.x) + \
                                (a.y * b.y) + \
                                (a.z * b.z))

/**
 * Calculates the cross product of vec3 a
 * and vec3 b.
 */

#define vec3_cross(a, b) ((vec3) {(a.y * b.z - a.z * b.y), \
                                  (a.z * b.x - a.x * b.z), \
                                  (a.x * b.y - a.y * b.x)})
/**
 * Calculates a linear interpolation between
 * vec3 a and vec3 b with interpolation factor t.
 */

#define vec3_lerp(a, b, t) ((vec3) {a.x + t * (b.x - a.x), \
                                    a.y + t * (b.y - a.y), \
                                    a.z + t * (b.z - a.z)})

/**
 * Generates a random vec3 with scale.
 */

#define vec3_random(scale) (vec3) ({             \
  srand((unsigned int) time(NULL));              \
  float rad = 2.0 * M_PI * rand();               \
  float z = (rand() * 2.0) - 1.0;                \
  float zs = sqrt(1.0 - z*z) * scale;            \
  (vec3(cosf(rad)*zs, sinf(rad)*zs, z*scale));   \
})

  // @TODO(werle) - hermite
  // @TODO(werle) - bezier
  // @TODO(werle) - transform
  // @TODO(werle) - transformMat4
  // @TODO(werle) - transformQuat
  // @TODO(werle) - rotateX
  // @TODO(werle) - rotateY
  // @TODO(werle) - rotateZ
  // @TODO(werle) - angle

/**
 * Returns a string representation of vec3 a.
 */

#define vec3_string(a) (const char *) ({              \
  char str[BUFSIZ];                                   \
  memset(str, 0, BUFSIZ);                             \
  sprintf(str, "vec3(%g, %g, %g)", a.x, a.y, a.z);    \
  (strdup(str));                                      \
})
#endif
