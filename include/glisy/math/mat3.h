#ifndef GLISY_MAT3_H
#define GLISY_MAT3_H

/**
 * mat3 struct type.
 */

typedef struct mat3 mat3;
struct mat3 {
  float m11; float m12; float m13;
  float m21; float m22; float m23;
  float m31; float m32; float m33;
};

/**
 * mat3 initializer.
 */

#define mat3_create() mat3(1,0,0, \
                           0,1,0, \
                           0,0,1)
#define mat3(m11, m12, m13, \
             m21, m22, m23, \
             m31, m32, m33) ((mat3) {m11, m12, m13, \
                                     m21, m22, m23, \
                                     m31, m32, m33})

/**
 * Clones and returns mat3 a.
 */

#define mat3_clone(a) ((mat3) {a.m11, a.m12, a.m13, \
                               a.m21, a.m22, a.m23, \
                               a.m31, a.m32, a.m33})

/**
 * Copies mat3 b into mat3 a.
 */

#define mat3_copy(a, b) (mat3) ({                               \
  mat3 *tmp = &a;                                               \
  (tmp->m11 = b.m11), (tmp->m12 = b.m12), (tmp->m13 = b.m13);   \
  (tmp->m21 = b.m21), (tmp->m22 = b.m22), (tmp->m23 = b.m23);   \
  (tmp->m31 = b.m31), (tmp->m32 = b.m32), (tmp->m33 = b.m33);   \
  (*tmp);                                                       \
})

/**
 * Sets an identity for mat3 a.
 */

#define mat3_identity(a) (mat3) ({                    \
  mat3 *tmp = &a;                                     \
  (tmp->m11 = 1), (tmp->m12 = 0), (tmp->m13 = 0);     \
  (tmp->m21 = 0), (tmp->m22 = 1), (tmp->m23 = 0);     \
  (tmp->m31 = 0), (tmp->m32 = 0), (tmp->m33 = 1);     \
  (*tmp);                                             \
})

/**
 * Transposes mat3 a.
 */

#define mat3_transpose(a) (mat3) ({    \
  mat3(a.m11, a.m21, a.m31,            \
       a.m12, a.m22, a.m32,            \
       a.m13, a.m23, a.m33);           \
})

/**
 * Calculates and sets inverse for
 * mat3 a.
 */

#define mat3_invert(a) (mat3) ({                 \
  mat3 b = mat3(0,0,0,0,0,0,0,0,0);              \
  float a11 = a.m11, a12 = a.m12, a13 = a.m13;   \
  float a21 = a.m21, a22 = a.m22, a23 = a.m23;   \
  float a31 = a.m31, a32 = a.m32, a33 = a.m33;   \
  float b11 = a33 * a22 - a23 * a32;             \
  float b21 = -a33 * a21 + a23 * a31;            \
  float b31 = a32 * a21 - a22 * a31;             \
  float det = a11 * b11 + a12 * b21 + a13 * b31; \
  if (det) {                                     \
    det = 1.0 / det;                             \
    (b.m11 = det * b11);                         \
    (b.m12 = det * (-a33 * a12 + a13 * a32));    \
    (b.m13 = det * (a23 * a12 - a13 * a22));     \
    (b.m21 = det * b21);                         \
    (b.m22 = det * (a33 * a11 - a13 * a31));     \
    (b.m23 = det * (-a23 * a11 + a13 * a21));    \
    (b.m31 = det * b31);                         \
    (b.m32 = det * (-a32 * a11 + a12 * a31));    \
    (b.m33 = det * (a22 * a11 - a12 * a21));     \
  }                                              \
  (b);                                           \
})

/**
 * Calculates adjugate of mat3 a.
 */

#define mat3_adjoint(a) (mat3) ({                \
  mat3 b;                                        \
  float a11 = a.m11, a12 = a.m12, a13 = a.m13;   \
  float a21 = a.m21, a22 = a.m22, a23 = a.m23;   \
  float a31 = a.m31, a32 = a.m32, a33 = a.m33;   \
  b.m11 = (a22 * a33 - a23 * a32);               \
  b.m12 = (a13 * a32 - a12 * a33);               \
  b.m13 = (a12 * a23 - a13 * a22);               \
  b.m21 = (a23 * a31 - a21 * a33);               \
  b.m22 = (a11 * a33 - a13 * a31);               \
  b.m23 = (a13 * a21 - a11 * a23);               \
  b.m31 = (a21 * a32 - a22 * a31);               \
  b.m32 = (a12 * a31 - a11 * a32);               \
  b.m33 = (a11 * a22 - a12 * a21);               \
  (b);                                           \
})

/**
 * Calculates determinant of mat3 a.
 */

#define mat3_determinant(a) (float) ({           \
  a.m11 * (a.m33 * a.m22 - a.m23 * a.m32) +      \
  a.m12 * (-a.m33 * a.m21 + a.m23 * a.m31) +     \
  a.m13 * (a.m32 * a.m21 - a.m22 * a.m31);       \
})

/**
 * Returns the product of mat3 a and mat3 b.
 */

#define mat3_multiply(a, b) ((mat3) mat3(          \
  (a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13), \
  (a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13), \
  (a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13), \
                                                   \
  (a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23), \
  (a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23), \
  (a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23), \
                                                   \
  (a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33), \
  (a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33), \
  (a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33)  \
))

/**
 * Translate mat3 a by vec2 b.
 */

#define mat3_translate(a, b) ((mat3) mat3(       \
  a.m11, a.m12, a.m13,                           \
  a.m21, a.m22, a.m23,                           \
  (b.x * a.m11 + b.y * a.m21 + a.m31),           \
  (b.x * a.m12 + b.y * a.m22 + a.m32),           \
  (b.x * a.m13 + b.y * a.m23 + a.m33)            \
))

/**
 * Rotates mat3 a by angle rad.
 */

#define mat3_rotate(a, rad) ((mat3) ({           \
  float c = cosf(rad);                           \
  float s = sinf(rad);                           \
  mat3((c * a.m11 + s * a.m21),                  \
       (c * a.m12 + s * a.m22),                  \
       (c * a.m13 + s * a.m23),                  \
       (c * a.m21 - s * a.m11),                  \
       (c * a.m22 - s * a.m12),                  \
       (c * a.m23 - s * a.m13),                  \
       a.m31, a.m32, a.m33                       \
    );                                           \
}))

/**
 * Scales mat3 a by vec2 b.
 */

#define mat3_scale(a, b) ((mat3) {               \
  (a.m11 * b.x), (a.m12 * b.x), (a.m13 * b.x),   \
  (a.m21 * b.y), (a.m22 * b.y), (a.m23 * b.y),   \
  a.m31, a.m32, a.m33                            \
})

/**
 * Creates mat3 from translation vec2 a.
 */

#define mat3_from_translation(a) ((mat3) {1, 0, 0,         \
                                          0, 1, 0,         \
                                          a.x, a.y, 1})

/**
 * Creates mat3 from rotation angle rad.
 */

#define mat3_from_rotation(rad) ((mat3) {        \
  cosf(rad), sinf(rad), 0,                       \
  -sinf(rad), cosf(rad), 0,                      \
  0, 0, 1                                        \
})

/**
 * Creates mat3 from scale vec2 a.
 */

#define mat3_from_scale(a) ((mat3) {   \
  a.x, 0, 0,                           \
  0, a.y, 0,                           \
  0, 0, 1                              \
})

/**
 * Creates mat2 from quat a.
 */

#define mat3_from_quat(a) ((mat3) ({             \
  float x = a.x, y = a.y, z = a.z, w = a.w;      \
  float x2 = x + x,                              \
        y2 = y + y,                              \
        z2 = z + z,                              \
        xx = x * x2,                             \
        yx = y * x2,                             \
        yy = y * y2,                             \
        zx = z * x2,                             \
        zy = z * y2,                             \
        zz = z * z2,                             \
        wx = w * x2,                             \
        wy = w * y2,                             \
        wz = w * z2;                             \
  mat3((1 - yy - zz),                            \
       (yx + wz),                                \
       (zx - wy),                                \
       (yx - wz),                                \
       (1 - xx - zz),                            \
       (zy + wx),                                \
       (zx + wy),                                \
       (zy - wx),                                \
       (1 - xx - yy));                           \
}))

/**
 * Calculates Frobenius norm mat3 a.
 */

#define mat3_frob(a) (float) sqrt(     \
  powf(a.m11, 2.0) +                   \
  powf(a.m12, 2.0) +                   \
  powf(a.m13, 2.0) +                   \
  powf(a.m21, 2.0) +                   \
  powf(a.m22, 2.0) +                   \
  powf(a.m23, 2.0) +                   \
  powf(a.m31, 2.0) +                   \
  powf(a.m32, 2.0) +                   \
  powf(a.m33, 2.0)                     \
)

/**
 * Returns a string representation of mat3 a.
 */

#define mat3_string(a) (const char *) ({                   \
  char str[BUFSIZ];                                        \
  mat3 b;                                                  \
  mat3_copy(b, a);                                         \
  memset(str, 0, BUFSIZ);                                  \
  sprintf(str, "mat3(%f, %f, %f, %f, %f, %f, %f, %f, %f)", \
               b.m11, b.m12, b.m13,                        \
               b.m21, b.m22, b.m23,                        \
               b.m31, b.m32, b.m33);                       \
  (strdup(str));                                           \
})
#endif
