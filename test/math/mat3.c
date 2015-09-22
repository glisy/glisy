#include <assert.h>
#include <glisy/math/vec2.h>
#include <glisy/math/mat3.h>
#include <glisy/math/quat.h>

#include "../test.h"

static inline void
mat3_assert_equals (mat3 a, mat3 b) {
  assert(fcmp(a.m11, b.m11));
  assert(fcmp(a.m12, b.m12));
  assert(fcmp(a.m21, b.m21));
  assert(fcmp(a.m22, b.m22));
  assert(fcmp(a.m31, b.m31));
  assert(fcmp(a.m32, b.m32));
}

int
main (void) {
  // identity explicit
  mat3 mat = mat3(1,0,0,
                  0,1,0,
                  0,0,1);
  assert(fcmp(1, mat.m11));
  assert(fcmp(0, mat.m12));
  assert(fcmp(0, mat.m21));
  assert(fcmp(1, mat.m22));

  // identity implicit
  mat3 identity = mat3_create();
  mat3_assert_equals(identity, mat);

  // clone
  mat3 cloned = mat3_clone(mat);
  mat3_assert_equals(cloned, mat);

  // copy
  mat3_assert_equals(mat3_copy(mat3_create(), mat), mat);

  // identity
  mat3_assert_equals(mat3(1,0,0,
                          0,1,0,
                          0,0,1),
                     mat3_identity(mat3(0,0,0,
                                        0,0,0,
                                        0,0,0)));

  // transpose
  mat3_assert_equals(mat3_transpose(mat3(1,2,3,
                                         4,5,6,
                                         7,8,9)),
                     mat3(1,4,7,
                          2,5,8,
                          3,6,9));

  // inverse
  mat3_assert_equals(mat3_invert(mat3(1,1,0,
                                      0,1,1,
                                      1,0,1)),
                     mat3(0.5,-0.5,0.5,
                          0.5,0.5,-0.5,
                          -0.5,0.5,0.5));

  // adjugate
  mat3_assert_equals(mat3_adjoint(mat3(1,1,0,
                                       0,1,1,
                                       0,0,1)),
                     mat3(1, -1, 1,
                          0, 1, -1,
                          0, 0, 1));

  // determinant
  assert(fcmp(1, mat3_determinant(mat3(1,0,0,
                                       0,1,0,
                                       0,0,1))));

  // multiply
  mat3_assert_equals(mat3_multiply(mat3(1,0,0,
                                        0,1,0,
                                        0,0,1), mat3(2,4,6,
                                                     1,3,5,
                                                     7,8,9)),
                     mat3(2,4,6,
                          1,3,5,
                          7,8,9));

  // translate
  mat3_assert_equals(mat3_translate(mat3(1,0,0,
                                         0,1,0,
                                         0,0,1), vec2(M_PI, M_PI/2)),
                     mat3(1,0,0,
                          0,1,0,
                          3.14159,1.57079,0));

  // rotate
  mat3_assert_equals(mat3_rotate(mat3(1,0,0,
                                      0,1,0,
                                      0,0,1), 2/M_PI),
                     mat3(0.80411,0.59448,0,
                          -0.59448,0.80411,0,
                          0,0,1));

  // scale
  mat3_assert_equals(mat3_scale(mat3(1,0,0,
                                     0,1,0,
                                     0,0,1), vec2(2/M_PI, M_PI/2)),
                     mat3(0.63662,0,0,
                          0,1.5708,0,
                          0,0,1));

  // from translation
  mat3_assert_equals(mat3_from_translation(vec2(M_PI/2, M_PI)),
                     mat3(1,0,0,
                          0,1,0,
                          1.5708,3.14159,1));

  // from rotation
  mat3_assert_equals(mat3_from_rotation(M_PI), mat3(-1, 0, 0,
                                                    0, -1, 0,
                                                    0, 0, 1));

  // from scale
  mat3_assert_equals(mat3_from_scale(vec2(M_PI, 1)), mat3(M_PI, 0, 0,
                                                   0, 1, 0,
                                                   0, 0, 1));

  // from quat
  mat3_assert_equals(mat3_from_quat(quat(2/M_PI, 0, 0, 1)), mat3(1,0,0,
                                                                 0,0.18943,1.27329,
                                                                 0,-1.27329,0.18943));

  // Frobenius norm
  assert(fcmp(1.73205, mat3_frob(mat3(1,0,0,
                                      0,1,0,
                                      0,0,1))));
  return 0;
}
