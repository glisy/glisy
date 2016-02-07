#ifndef GLISY_MAT4_H
#define GLISY_MAT4_H

#include <glisy/math.h>

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
 * mat4 initializers.
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

#define mat4_copy(a, b) (mat4) ({                                                 \
  mat4 *tmp = &a;                                                                 \
  (tmp->m11 = b.m11), (tmp->m12 = b.m12), (tmp->m13 = b.m13), (tmp->m14 = b.m14); \
  (tmp->m21 = b.m21), (tmp->m22 = b.m22), (tmp->m23 = b.m23), (tmp->m24 = b.m24); \
  (tmp->m31 = b.m31), (tmp->m32 = b.m32), (tmp->m33 = b.m33), (tmp->m34 = b.m34); \
  (tmp->m41 = b.m41), (tmp->m42 = b.m42), (tmp->m43 = b.m43), (tmp->m44 = b.m44); \
  (*tmp);                                                                         \
})

/**
 * Sets an identity for mat4 a.
 */

#define mat4_identity(a) (mat4) ({                                \
  mat4 *tmp = &a;                                                 \
  (tmp->m11 = 1), (tmp->m12 = 0), (tmp->m13 = 0), (tmp->m14 = 0); \
  (tmp->m21 = 0), (tmp->m22 = 1), (tmp->m23 = 0), (tmp->m24 = 0); \
  (tmp->m31 = 0), (tmp->m32 = 0), (tmp->m33 = 1), (tmp->m34 = 0); \
  (tmp->m41 = 0), (tmp->m42 = 0), (tmp->m43 = 0), (tmp->m44 = 1); \
  (*tmp);                                                         \
})

/**
 * Transposes mat4 a.
 */

#define mat4_transpose(a) (mat4) ({ \
  mat4(a.m11, a.m21, a.m31, a.m41,  \
       a.m12, a.m22, a.m32, a.m42,  \
       a.m13, a.m23, a.m33, a.m43,  \
       a.m14, a.m24, a.m34, a.m44); \
})

/**
 * Calculates and returns inverse for mat4 a.
 */

#define mat4_invert(a) (mat4) ({                                     \
  mat4 b = mat4(0,0,0,0,                                             \
                0,0,0,0,                                             \
                0,0,0,0,                                             \
                0,0,0,0);                                            \
                                                                     \
  float a00 = a.m11, a01 = a.m12, a02 = a.m13, a03 = a.m14;          \
  float a10 = a.m21, a11 = a.m22, a12 = a.m23, a13 = a.m24;          \
  float a20 = a.m31, a21 = a.m32, a22 = a.m33, a23 = a.m34;          \
  float a30 = a.m41, a31 = a.m42, a32 = a.m43, a33 = a.m44;          \
                                                                     \
  float b00 = a00 * a11 - a01 * a10;                                 \
  float b01 = a00 * a12 - a02 * a10;                                 \
  float b02 = a00 * a13 - a03 * a10;                                 \
  float b03 = a01 * a12 - a02 * a11;                                 \
  float b04 = a01 * a13 - a03 * a11;                                 \
  float b05 = a02 * a13 - a03 * a12;                                 \
  float b06 = a20 * a31 - a21 * a30;                                 \
  float b07 = a20 * a32 - a22 * a30;                                 \
  float b08 = a20 * a33 - a23 * a30;                                 \
  float b09 = a21 * a32 - a22 * a31;                                 \
  float b10 = a21 * a33 - a23 * a31;                                 \
  float b11 = a22 * a33 - a23 * a32;                                 \
                                                                     \
  float det = b00 * b11 - b01 * b10                                  \
            + b02 * b09 + b03 * b08                                  \
            - b04 * b07 + b05 * b06;                                 \
                                                                     \
  if (det) {                                                         \
    det = 1.0 / det;                                                 \
                                                                     \
    b.m11 = (a11 * b11 - a12 * b10 + a13 * b09) * det;               \
    b.m12 = (a02 * b10 - a01 * b11 - a03 * b09) * det;               \
    b.m13 = (a31 * b05 - a32 * b04 + a33 * b03) * det;               \
    b.m14 = (a22 * b04 - a21 * b05 - a23 * b03) * det;               \
                                                                     \
    b.m21 = (a12 * b08 - a10 * b11 - a13 * b07) * det;               \
    b.m22 = (a00 * b11 - a02 * b08 + a03 * b07) * det;               \
    b.m23 = (a32 * b02 - a30 * b05 - a33 * b01) * det;               \
    b.m24 = (a20 * b05 - a22 * b02 + a23 * b01) * det;               \
                                                                     \
    b.m31 = (a10 * b10 - a11 * b08 + a13 * b06) * det;               \
    b.m32 = (a01 * b08 - a00 * b10 - a03 * b06) * det;               \
    b.m33 = (a30 * b04 - a31 * b02 + a33 * b00) * det;               \
    b.m34 = (a21 * b02 - a20 * b04 - a23 * b00) * det;               \
                                                                     \
    b.m41 = (a11 * b07 - a10 * b09 - a12 * b06) * det;               \
    b.m42 = (a00 * b09 - a01 * b07 + a02 * b06) * det;               \
    b.m43 = (a31 * b01 - a30 * b03 - a32 * b00) * det;               \
    b.m44 = (a20 * b03 - a21 * b01 + a22 * b00) * det;               \
  }                                                                  \
  (b);                                                               \
})

/**
 * Calculates adjugate of mat4 a.
 */

#define mat4_adjoint(a) (mat4) ({                                    \
  mat4 b = mat4(0,0,0,0,                                             \
                0,0,0,0,                                             \
                0,0,0,0,                                             \
                0,0,0,0);                                            \
                                                                     \
  float a00 = a.m11, a01 = a.m12, a02 = a.m13, a03 = a.m14;          \
  float a10 = a.m21, a11 = a.m22, a12 = a.m23, a13 = a.m24;          \
  float a20 = a.m31, a21 = a.m32, a22 = a.m33, a23 = a.m34;          \
  float a30 = a.m41, a31 = a.m42, a32 = a.m43, a33 = a.m44;          \
                                                                     \
  b.m11 =   (a11 * (a22 * a33 - a23 * a32)                           \
           - a21 * (a12 * a33 - a13 * a32)                           \
           + a31 * (a12 * a23 - a13 * a22));                         \
                                                                     \
  b.m12 = - (a01 * (a22 * a33 - a23 * a32)                           \
           - a21 * (a02 * a33 - a03 * a32)                           \
           + a31 * (a02 * a23 - a03 * a22));                         \
                                                                     \
  b.m13 =   (a01 * (a12 * a33 - a13 * a32)                           \
           - a11 * (a02 * a33 - a03 * a32)                           \
           + a31 * (a02 * a13 - a03 * a12));                         \
                                                                     \
  b.m14 = - (a01 * (a12 * a23 - a13 * a22)                           \
           - a11 * (a02 * a23 - a03 * a22)                           \
           + a21 * (a02 * a13 - a03 * a12));                         \
                                                                     \
  b.m21 = - (a10 * (a22 * a33 - a23 * a32)                           \
           - a20 * (a12 * a33 - a13 * a32)                           \
           + a30 * (a12 * a23 - a13 * a22));                         \
                                                                     \
  b.m22 =  (a00 * (a22 * a33 - a23 * a32)                            \
          - a20 * (a02 * a33 - a03 * a32)                            \
          + a30 * (a02 * a23 - a03 * a22));                          \
                                                                     \
  b.m23 = - (a00 * (a12 * a33 - a13 * a32)                           \
           - a10 * (a02 * a33 - a03 * a32)                           \
           + a30 * (a02 * a13 - a03 * a12));                         \
                                                                     \
  b.m24 =  (a00 * (a12 * a23 - a13 * a22)                            \
          - a10 * (a02 * a23 - a03 * a22)                            \
          + a20 * (a02 * a13 - a03 * a12));                          \
                                                                     \
  b.m31 =  (a10 * (a21 * a33 - a23 * a31)                            \
          - a20 * (a11 * a33 - a13 * a31)                            \
          + a30 * (a11 * a23 - a13 * a21));                          \
                                                                     \
  b.m32 = - (a00 * (a21 * a33 - a23 * a31)                           \
           - a20 * (a01 * a33 - a03 * a31)                           \
           + a30 * (a01 * a23 - a03 * a21));                         \
                                                                     \
  b.m33 =  (a00 * (a11 * a33 - a13 * a31)                            \
          - a10 * (a01 * a33 - a03 * a31)                            \
          + a30 * (a01 * a13 - a03 * a11));                          \
                                                                     \
  b.m34 = - (a00 * (a11 * a23 - a13 * a21)                           \
           - a10 * (a01 * a23 - a03 * a21)                           \
           + a20 * (a01 * a13 - a03 * a11));                         \
                                                                     \
  b.m41 = - (a10 * (a21 * a32 - a22 * a31)                           \
           - a20 * (a11 * a32 - a12 * a31)                           \
           + a30 * (a11 * a22 - a12 * a21));                         \
                                                                     \
  b.m42 =  (a00 * (a21 * a32 - a22 * a31)                            \
          - a20 * (a01 * a32 - a02 * a31)                            \
          + a30 * (a01 * a22 - a02 * a21));                          \
                                                                     \
  b.m43 = - (a00 * (a11 * a32 - a12 * a31)                           \
           - a10 * (a01 * a32 - a02 * a31)                           \
           + a30 * (a01 * a12 - a02 * a11));                         \
                                                                     \
  b.m44 =  (a00 * (a11 * a22 - a12 * a21)                            \
          - a10 * (a01 * a22 - a02 * a21)                            \
          + a20 * (a01 * a12 - a02 * a11));                          \
                                                                     \
  (b);                                                               \
})

/**
 * Calculates determinant of mat4 a.
 */

#define mat4_determinant(a) (float) ({                               \
  float a00 = a.m11, a01 = a.m12, a02 = a.m13, a03 = a.m14;          \
  float a10 = a.m21, a11 = a.m22, a12 = a.m23, a13 = a.m24;          \
  float a20 = a.m31, a21 = a.m32, a22 = a.m33, a23 = a.m34;          \
  float a30 = a.m41, a31 = a.m42, a32 = a.m43, a33 = a.m44;          \
                                                                     \
  float b00 = a00 * a11 - a01 * a10;                                 \
  float b01 = a00 * a12 - a02 * a10;                                 \
  float b02 = a00 * a13 - a03 * a10;                                 \
  float b03 = a01 * a12 - a02 * a11;                                 \
  float b04 = a01 * a13 - a03 * a11;                                 \
  float b05 = a02 * a13 - a03 * a12;                                 \
  float b06 = a20 * a31 - a21 * a30;                                 \
  float b07 = a20 * a32 - a22 * a30;                                 \
  float b08 = a20 * a33 - a23 * a30;                                 \
  float b09 = a21 * a32 - a22 * a31;                                 \
  float b10 = a21 * a33 - a23 * a31;                                 \
  float b11 = a22 * a33 - a23 * a32;                                 \
                                                                     \
  float det = b00 * b11                                              \
            - b01 * b10                                              \
            + b02 * b09                                              \
            + b03 * b08                                              \
            - b04 * b07                                              \
            + b05 * b06;                                             \
  (det);                                                             \
})

/**
 * Add mat4 a and mat4 b.
 */

#define mat4_add(a, b) ((mat4) {                                     \
  a.m11 + b.m11, a.m12 + b.m12, a.m13 + b.m13, a.m14 + b.m14,        \
  a.m21 + b.m21, b.m22 + b.m22, a.m23 + b.m23, a.m24 + b.m24,        \
  a.m31 + b.m31, b.m32 + b.m32, a.m33 + b.m33, a.m34 + b.m34,        \
  a.m41 + b.m41, b.m42 + b.m42, a.m43 + b.m43, a.m44 + b.m44         \
})

/**
 * Subtract mat4 b from mat4 a.
 */

#define mat4_subtract(a, b) ((mat4) {                                \
  a.m11 - b.m11, a.m12 - b.m12, a.m13 - b.m13, a.m14 - b.m14,        \
  a.m21 - b.m21, b.m22 - b.m22, a.m23 - b.m23, a.m24 - b.m24,        \
  a.m31 - b.m31, b.m32 - b.m32, a.m33 - b.m33, a.m34 - b.m34,        \
  a.m41 - b.m41, b.m42 - b.m42, a.m43 - b.m43, a.m44 - b.m44         \
})

/**
 * Multiply mat4 a and mat4 b.
 */

#define mat4_multiply(a, b) ((mat4) mat4(                            \
  (a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13 + a.m41 * b.m14),   \
  (a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13 + a.m42 * b.m14),   \
  (a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13 + a.m43 * b.m14),   \
                                                                     \
  (a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23 + a.m41 * b.m24),   \
  (a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23 + a.m42 * b.m24),   \
  (a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23 + a.m43 * b.m24),   \
                                                                     \
  (a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33 + a.m41 * b.m34),   \
  (a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33 + a.m42 * b.m34),   \
  (a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33 + a.m43 * b.m34),   \
                                                                     \
  (a.m11 * b.m41 + a.m21 * b.m42 + a.m31 * b.m43 + a.m41 * b.m44),   \
  (a.m12 * b.m41 + a.m22 * b.m42 + a.m32 * b.m43 + a.m42 * b.m44),   \
  (a.m13 * b.m41 + a.m23 * b.m42 + a.m33 * b.m43 + a.m43 * b.m44),   \
))

/**
 * Rotates mat4 a by angle rad.
 */

#define mat4_rotate(a, rad, vec) ((mat4) {                           \
  float x = vec.x, y = vec.y, z = vec.z;                             \
  float d = sqrt(x*x + y*y + z*z);                                   \
  float c = cosf(a), s = sinf(a), t = 1 - c;                         \
                                                                     \
  x /= d; y /= d; z /= d;                                            \
                                                                     \
  a.m11 = x * x * t + c;                                             \
  a.m12 = x * y * t - z * s;                                         \
  a.m13 = x * z * t + y * s;                                         \
  a.m14 = 0;                                                         \
                                                                     \
  a.m21 = y * x * t + z * s;                                         \
  a.m22 = y * y * t + c;                                             \
  a.m23 = y * z * t - x * s;                                         \
  a.m24 = 0;                                                         \
                                                                     \
  a.m31 = z * x * t - y * s;                                         \
  a.m32 = z * y * t + x * s;                                         \
  a.m33 = z * z * t + c;                                             \
  a.m34 = 0;                                                         \
                                                                     \
  a.m41 = 0;                                                         \
  a.m42 = 0;                                                         \
  a.m43 = 0;                                                         \
  a.m44 = 1;                                                         \
                                                                     \
  (a);                                                               \
})

/**
 * Scales mat4 a by vec3 b.
 */

#define mat4_scale(a, b) ((mat4) {                                   \
  (a.m11 * b.x), (a.m12 * b.x), (a.m13 * b.x), (a.m14 * b.x),        \
  (a.m21 * b.y), (a.m22 * b.y), (a.m23 * b.y), (a.m24 * b.y),        \
  (a.m31 * b.z), (a.m32 * b.z), (a.m33 * b.z), (a.m34 * b.z),        \
  a.m41, a.m42, a.m43, a.m44                                         \
})

/**
 * Translate mat4 a by vec2 b.
 */

#define mat4_translate(a, b) ((mat4) mat4(                           \
  a.m11, a.m12, a.m13, a.m14,                                        \
  a.m21, a.m22, a.m23, a.m24,                                        \
  (b.x * a.m11 + b.y * a.m21 + b.z * a.m31 + a.m41),                 \
  (b.x * a.m12 + b.y * a.m22 + b.z * a.m32 + a.m42),                 \
  (b.x * a.m13 + b.y * a.m23 + b.z * a.m33 + a.m43),                 \
  (b.x * a.m14 + b.y * a.m24 + b.z * a.m34 + a.m44)                  \
))

/**
 * Generates a frustum matrix from top, left, bottom, right,
 * near, and far bounds.
 */

#define mat4_frustum(top, left, bottom, right, near, far) (mat4) ({  \
  float rl = 1 / (right - left);                                     \
  float tb = 1 / (top - bottom);                                     \
  float nf = 1 / (near - far);                                       \
  mat4 mat;                                                          \
                                                                     \
  a.m11 = rl * (2 * near);                                           \
  a.m12 = 0;                                                         \
  a.m13 = 0;                                                         \
  a.m14 = 0;                                                         \
                                                                     \
  a.m21 = 0;                                                         \
  a.m22 = tb * (2 * near);                                           \
  a.m23 = 0;                                                         \
  a.m24 = 0;                                                         \
                                                                     \
  a.m31 = rl * (right + left);                                       \
  a.m32 = rl * (top + bottom);                                       \
  a.m33 = nf * (far + near);                                         \
  a.m34 = -1;                                                        \
                                                                     \
  a.m41 = 0;                                                         \
  a.m42 = 0;                                                         \
  a.m43 = nf * (2 * far * near)                                      \
  a.m44 = 0;                                                         \
                                                                     \
  (a);                                                               \
})

/**
 * Generates a perspective matrix from fov, aspect, near, and
 * far bounds.
 */

#define mat4_perspective(fov, aspect, near, far) (mat4) ({           \
  float f = 1.0 / tand(fov / 2);                                     \
  float nf = 1 / (near - far);                                       \
  mat4 mat;                                                          \
                                                                     \
  a.m11 = f / aspect;                                                \
  a.m12 = 0;                                                         \
  a.m13 = 0;                                                         \
  a.m14 = 0;                                                         \
                                                                     \
  a.m21 = 0;                                                         \
  a.m22 = f;                                                         \
  a.m23 = 0;                                                         \
  a.m24 = 0;                                                         \
                                                                     \
  a.m31 = 0;                                                         \
  a.m32 = 0;                                                         \
  a.m33 = nf * (far + near);                                         \
  a.m34 = -1;                                                        \
                                                                     \
  a.m41 = 0;                                                         \
  a.m42 = 0;                                                         \
  a.m43 = nf * (2 * far * near);                                     \
  a.m44 = 0;                                                         \
                                                                     \
  (a);                                                               \
})

/**
 * Generates a orthogonal matrix from top, left, bottom, right,
 * near, and far bounds.
 */

#define mat4_ortho(top, left, bottom, right, near, far) (mat4) ({    \
  float lr = 1 / (left - right);                                     \
  float bt = 1 / (bottom - top);                                     \
  float nf = 1 / (near - far);                                       \
  mat4 mat;                                                          \
                                                                     \
  a.m11 = -2 * lr;                                                   \
  a.m12 = 0;                                                         \
  a.m13 = 0;                                                         \
  a.m14 = 0;                                                         \
                                                                     \
  a.m21 = 0;                                                         \
  a.m22 = -2 * bt;                                                   \
  a.m23 = 0;                                                         \
  a.m24 = 0;                                                         \
                                                                     \
  a.m31 = 0;                                                         \
  a.m32 = 0;                                                         \
  a.m33 = 2 * nf;                                                    \
  a.m34 = 0;                                                         \
                                                                     \
  a.m41 = lr * (left + right);                                       \
  a.m42 = bt * (top + bottom);                                       \
  a.m43 = nf * (far + near);                                         \
  a.m44 = 1;                                                         \
                                                                     \
  (a);                                                               \
})

/**
 * Generates a lookAt matrix from an eye, focal, and up vec3.
 */

#define mat4_lookAt(eye, center, up) (mat4) ({                       \
  float x0, x1, x2, y0, y1, y2, z0, z1, z2, len;                     \
  float eyex = eye.x;                                                \
  float eyey = eye.y;                                                \
  float eyez = eye.z;                                                \
  float upx = up.x;                                                  \
  float upy = up.y;                                                  \
  float upz = up.z;                                                  \
  float centerx = center.x;                                          \
  float centery = center.y;                                          \
  float centerz = center.z;                                          \
  mat4 a = mat4_create();                                            \
  if (!(fabs(eyex - centerx) < GLISY_EPSILON &&                      \
      fabs(eyey - centery) < GLISY_EPSILON &&                        \
      fabs(eyez - centerz) < GLISY_EPSILON)) {                       \
    z0 = eyex - centerx;                                             \
    z1 = eyey - centery;                                             \
    z2 = eyez - centerz;                                             \
    len = 1 / sqrt(z0 * z0 + z1 * z1 + z2 * z2);                     \
    z0 *= len;                                                       \
    z1 *= len;                                                       \
    z2 *= len;                                                       \
    x0 = upy * z2 - upz * z1;                                        \
    x1 = upz * z0 - upx * z2;                                        \
    x2 = upx * z1 - upy * z0;                                        \
    len = sqrt(x0 * x0 + x1 * x1 + x2 * x2);                         \
    if (!len) {                                                      \
      x0 = 0;                                                        \
      x1 = 0;                                                        \
      x2 = 0;                                                        \
    } else {                                                         \
      len = 1 / len;                                                 \
      x0 *= len;                                                     \
      x1 *= len;                                                     \
      x2 *= len;                                                     \
    }                                                                \
    y0 = z1 * x2 - z2 * x1;                                          \
    y1 = z2 * x0 - z0 * x2;                                          \
    y2 = z0 * x1 - z1 * x0;                                          \
    len = sqrt(y0 * y0 + y1 * y1 + y2 * y2);                         \
    if (!len) {                                                      \
      y0 = 0;                                                        \
      y1 = 0;                                                        \
      y2 = 0;                                                        \
    } else {                                                         \
      len = 1 / len;                                                 \
      y0 *= len;                                                     \
      y1 *= len;                                                     \
      y2 *= len;                                                     \
    }                                                                \
    a.m11 = x0;                                                      \
    a.m12 = y0;                                                      \
    a.m13 = z0;                                                      \
    a.m14 = 0;                                                       \
    a.m21 = x1;                                                      \
    a.m22 = y1;                                                      \
    a.m23 = z1;                                                      \
    a.m24 = 0;                                                       \
    a.m31 = x2;                                                      \
    a.m32 = y2;                                                      \
    a.m33 = z2;                                                      \
    a.m34 = 0;                                                       \
    a.m41 = -(x0 * eyex + x1 * eyey + x2 * eyez);                    \
    a.m42 = -(y0 * eyex + y1 * eyey + y2 * eyez);                    \
    a.m43 = -(z0 * eyex + z1 * eyey + z2 * eyez);                    \
    a.m44 = 1;                                                       \
  }                                                                  \
  (a);                                                               \
})

/**
 * Calculates Frobenius norm mat4 a.
 */

#define mat4_frob(a) (float) sqrt(                                   \
  powf(a.m11, 2.0) +                                                 \
  powf(a.m12, 2.0) +                                                 \
  powf(a.m13, 2.0) +                                                 \
  powf(a.m14, 2.0) +                                                 \
  powf(a.m21, 2.0) +                                                 \
  powf(a.m22, 2.0) +                                                 \
  powf(a.m23, 2.0) +                                                 \
  powf(a.m24, 2.0) +                                                 \
  powf(a.m31, 2.0) +                                                 \
  powf(a.m32, 2.0) +                                                 \
  powf(a.m33, 2.0) +                                                 \
  powf(a.m34, 2.0) +                                                 \
  powf(a.m41, 2.0) +                                                 \
  powf(a.m42, 2.0) +                                                 \
  powf(a.m43, 2.0) +                                                 \
  powf(a.m44, 2.0)                                                   \
)

/**
 * Returns a string representation of mat4 a.
 */

#define mat4_string(a) (const char *) ({                             \
  char str[BUFSIZ];                                                  \
  mat4 b;                                                            \
  mat4_copy(b, a);                                                   \
  memset(str, 0, BUFSIZ);                                            \
  sprintf(str, "mat4(%f, %f, %f, %f,"                                \
                    "%f, %f, %f, %f,",                               \
                    "%f, %f, %f, %f,",                               \
                    "%f, %f, %f, %f)",                               \
               b.m11, b.m12, b.m13, b.m14,                           \
               b.m21, b.m22, b.m23, b.m24,                           \
               b.m31, b.m32, b.m33, b.m34,                           \
               b.m41, b.m42, b.m43, b.m44);                          \
  (strdup(str));                                                     \
})

#endif
