#ifndef GLISY_MAT4_H
#define GLISY_MAT4_H

/**
 * mat4 struct type.
 */

typedef struct mat4 mat4;
struct mat4 {
  float m11; float m12; float m13; float m14;
  float m21; float m22; float m23; float m24;
  float m31; float m32; float m33; float m34;
  float m41; float m42; float m43; float m44;
};

/**
 * mat4 initializer.
 */

#define mat4_create() mat4(1,0,0,0, \
                           0,1,0,0, \
                           0,0,1,0, \
                           0,0,0,1)

#define mat4(m11, m12, m13, m14, \
             m21, m22, m23, m24, \
             m31, m32, m33, m34, \
             m41, m42, m43, m44) ((mat4) {m11, m12, m13, m14 \
                                          m21, m22, m23, m24 \
                                          m31, m32, m33, m34 \
                                          m41, m42, m43, m44})

/**
 * Clones and returns mat4 a.
 */

#define mat4_clone(a) ((mat4) {a.m11, a.m12, a.m13, a.m14 \
                               a.m21, a.m22, a.m23, a.m24 \
                               a.m31, a.m32, a.m33, a.m34 \
                               a.m41, a.m42, a.m43, a.m44})

/**
 * Copies mat4 b into mat4 a.
 */

#define mat4_copy(a, b) (mat4) ({                                         \
  mat4 *c = &a;                                                           \
  (c->m11 = b.m11), (c->m12 = b.m12), (c->m13 = b.m13), (c->m14 = b.m14); \
  (c->m21 = b.m21), (c->m22 = b.m22), (c->m23 = b.m23), (c->m24 = b.m24); \
  (c->m31 = b.m31), (c->m32 = b.m32), (c->m33 = b.m33), (c->m34 = b.m34); \
  (c->m41 = b.m41), (c->m42 = b.m42), (c->m43 = b.m43), (c->m44 = b.m44); \
  (*c);                                                                   \
})

/**
 * Sets an identity for mat4 a.
 */

#define mat4_identity(a) (mat4) ({                         \
  mat4 *b = &a;                                            \
  (b->m11 = 1), (b->m12 = 0), (b->m13 = 0), (b->m14 = 0);  \
  (b->m21 = 0), (b->m22 = 1), (b->m23 = 0), (b->m24 = 0);  \
  (b->m31 = 0), (b->m32 = 0), (b->m33 = 1), (b->m34 = 0);  \
  (b->m41 = 0), (b->m42 = 0), (b->m43 = 0), (b->m44 = 1);  \
  (*b);                                                    \
})

/**
 * Transposes mat4 a.
 */

#define mat4_transpose(a) (mat4) ({    \
  mat4(a.m11, a.m21, a.m31, a.m41,     \
       a.m12, a.m22, a.m32, a.m42,     \
       a.m13, a.m23, a.m33, a.m43,     \
       a.m14, a.m24, a.m34, a.m44);    \
})

/**
 * Returns a string representation of mat4 a.
 */

#define mat4_string(a) (const char *) ({                   \
  char str[BUFSIZ];                                        \
  mat4 b;                                                  \
  mat4_copy(b, a);                                         \
  memset(str, 0, BUFSIZ);                                  \
  sprintf(str, "mat4(%f, %f, %f, %f,"                      \
                    "%f, %f, %f, %f,",                     \
                    "%f, %f, %f, %f,",                     \
                    "%f, %f, %f, %f)",                     \
               b.m11, b.m12, b.m13, b.m14,                 \
               b.m21, b.m22, b.m23, b.m24,                 \
               b.m31, b.m32, b.m33, b.m34,                 \
               b.m41, b.m42, b.m43, b.m44);                \
  (strdup(str));                                           \
})

#endif
