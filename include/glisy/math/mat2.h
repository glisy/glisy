#ifndef GLISY_MAT2_H
#define GLISY_MAT2_H

/**
 * mat2 struct type.
 */

typedef struct mat2 mat2;
struct mat2 {
  float m11; float m12;
  float m21; float m22;
};

/**
 * mat2 initializer.
 */

#define mat2(m11, m12, m21, m22) ((mat2) {m11, m12, m21, m22})
#define mat2_create() mat2(1, 0, 0, 1)

/**
 * Clones and returns mat2 a.
 */

#define mat2_clone(a) (mat2) {a.m11, a.m12, a.m21, a.m22}

/**
 * Copies mat2 b into mat2 a.
 */

#define mat2_copy(a, b) (mat2) ({      \
  mat2 *tmp = &a;                      \
  (tmp->m11 = b.m11);                  \
  (tmp->m12 = b.m12);                  \
  (tmp->m21 = b.m21);                  \
  (tmp->m22 = b.m22);                  \
  (*tmp);                              \
})

/**
 * Sets an identity for mat2 a.
 */

#define mat2_identity(a) (mat2) ({     \
  mat2 *tmp = &a;                      \
  (tmp->m11 = 1);                      \
  (tmp->m12 = 0);                      \
  (tmp->m21 = 0);                      \
  (tmp->m22 = 1);                      \
  (*tmp);                              \
})

/**
 * Transposes mat2 a.
 */

#define mat2_transpose(a) (mat2) ({    \
  mat2(a.m11, a.m21, a.m12, a.m22);    \
})

/**
 * Calculates and sets inverse for
 * mat2 a.
 */

#define mat2_invert(a) (mat2) ({       \
  mat2 b;                              \
  float det = (                        \
    a.m11 * a.m22 - a.m21 * a.m12      \
  );                                   \
  if (!det) {                          \
    (b.m11 = 0);                       \
    (b.m12 = 0);                       \
    (b.m21 = 0);                       \
    (b.m22 = 0);                       \
  } else {                             \
    det = (1.0/det);                   \
    b.m11 = det * a.m22;               \
    b.m12 = det * -a.m12;              \
    b.m21 = det * -a.m21;              \
    b.m22 = det * a.m11;               \
  }                                    \
  (b);                                 \
})

/**
 * Calculates adjugate of mat2 a.
 */

#define mat2_adjoint(a) (mat2) ({      \
  mat2(a.m22, -a.m12, -a.m21, a.m11);  \
})

/**
 * Calculates determinant of mat2 a.
 */

#define mat2_determinant(a) (float) ({ \
  (a.m11 * a.m22 - a.m21 * a.m12);     \
})

/**
 * Returns the product of mat2 a and mat2 b.
 */

#define mat2_multiply(a, b) ((mat2) { \
  (a.m11 * b.m11 + a.m21 * b.m12),    \
  (a.m12 * b.m11 + a.m22 * b.m12),    \
  (a.m11 * b.m21 + a.m21 * b.m22),    \
  (a.m12 * b.m21 + a.m22 * b.m22)     \
})

/**
 * Rotates mat2 a by angle rad.
 */

#define mat2_rotate(a, rad) ((mat2) ({ \
  float s = sinf(rad);                 \
  float c = cosf(rad);                 \
  mat2(a.m11 * c + a.m21 * s,          \
       a.m12 * c + a.m22 * s,          \
       a.m11 * -s + a.m21 * c,         \
       a.m12 * -s + a.m22 * c);        \
}))

/**
 * Scale mat2 a by vec2 b.
 */

#define mat2_scale(a, b) ((mat2) {     \
  (a.m11 * b.x), (a.m12 * b.x),        \
  (a.m21 * b.y), (a.m22 * b.y)         \
})

/**
 * Creates a mat2 from rotation rad.
 */

#define mat2_from_rotation(rad) ((mat2) {   \
  cosf(rad), sinf(rad),                     \
  -sinf(rad), cosf(rad)                     \
})

/**
 * Creates a scaled mat2 from a vec2 a.
 */

#define mat2_scaled_from_vec2(a) mat2(a.x, 0, 0, a.y)

/**
 * Calculates the Frobenius norm for mat2 a.
 * See: http://mathworld.wolfram.com/FrobeniusNorm.html
 */

#define mat2_frob(a) (float) sqrt(     \
  powf(a.m11, 2.0) +                   \
  powf(a.m12, 2.0) +                   \
  powf(a.m21, 2.0) +                   \
  powf(a.m22, 2.0)                     \
)

/**
 * Returns a string representation of mat2 a.
 */

#define mat2_string(a) (const char *) ({         \
  char str[BUFSIZ];                              \
  memset(str, 0, BUFSIZ);                        \
  sprintf(str, "mat2(%f, %f, %f, %f)",           \
               a.m11, a.m12, a.m21, a.m22);      \
  (strdup(str));                                 \
})
#endif
