#include <assert.h>
#include <glisy/math/vec2.h>
#include <glisy/math/mat2.h>

#include "../test.h"

static inline void
mat2_assert_equals (mat2 a, mat2 b) {
  assert(fcmp(a.m11, b.m11));
  assert(fcmp(a.m12, b.m12));
  assert(fcmp(a.m21, b.m21));
  assert(fcmp(a.m22, b.m22));
}

int
main (void) {
  // identity explicit
  mat2 mat = mat2(1,0,0,1);
  assert(fcmp(1, mat.m11));
  assert(fcmp(0, mat.m12));
  assert(fcmp(0, mat.m21));
  assert(fcmp(1, mat.m22));

  // identity implicit
  mat2 identity = mat2_create();
  mat2_assert_equals(identity, mat);

  // clone
  mat2 cloned = mat2_clone(mat);
  mat2_assert_equals(cloned, mat);

  // copy
  mat2_assert_equals(mat2_copy(mat2_create(), mat), mat);

  // identity
  mat2_assert_equals(mat2(1,0,0,1),
                     mat2_identity(mat2(0,0,0,0)));

  // transpose
  mat2_assert_equals(mat2(1,3,2,4),
                     mat2_transpose(mat2(1,2,3,4)));

  // inverse
  mat2_assert_equals(mat2_invert(mat2(1,2,3,4)),
                     mat2(-2,1,1.5,-0.5));

  // adjugate
  mat2_assert_equals(mat2_adjoint(mat2(2,4,6,8)),
                     mat2(8,-4,-6,2));

  // determinant
  assert(fcmp(-2.0, mat2_determinant(mat2(1,2,3,4))));

  // multiply
  mat2_assert_equals(mat2_multiply(mat2(2,4,6,8), mat2(1,2,3,4)),
                     mat2(14,20,30,44));

  // rotate
  mat2_assert_equals(mat2_rotate(mat2(1,1,1,1), M_PI),
                     mat2(-0.99999, -0.99999, -1, -1));

  // scale
  mat2_assert_equals(mat2_scale(mat2(1,0,0,1), vec2(2,4)),
                     mat2(2,0,0,4));

  // from rotation
  mat2_assert_equals(mat2_from_rotation(2.0/M_PI),
                     mat2(0.80410, 0.59448, -0.59448, 0.80410));

  // scaled from vec2
  mat2_assert_equals(mat2_scaled_from_vec2(vec2(4,4)),
                     mat2(4,0,0,4));

  // Frobenius norm
  assert(fcmp(sqrt(2.0), mat2_frob(mat2(1,0,0,1))));
  return 0;
}
