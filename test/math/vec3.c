#include <assert.h>
#include <glisy/math/vec3.h>

#include "../test.h"

int
main (void) {
  // init
  vec3 a = vec3(1, 1, 1);
  assert(1 == a.x);
  assert(1 == a.y);
  assert(1 == a.z);

  // clone
  vec3 b = vec3_clone(a);
  assert(b.x == a.x);
  assert(b.y == a.y);
  assert(b.z == a.z);

  // subtract
  vec3 c = vec3_subtract(a, b);
  assert(0 == c.x);
  assert(0 == c.y);
  assert(0 == c.z);

  // multiply
  vec3 d = vec3_multiply(vec3(2, 2, 2), vec3(2, 2, 2));
  assert(4 == d.x);
  assert(4 == d.y);
  assert(4 == d.z);

  // divide
  vec3 e = vec3_divide(vec3(4, 4, 4), vec3(2, 2, 2));
  assert(2 == e.x);
  assert(2 == e.y);
  assert(2 == e.z);

  // copy
  vec3 f;
  vec3_copy(f, a);
  assert(f.y == a.y);
  assert(f.x == a.x);

  // set
  vec3 g = vec3_set(vec3(0, 1, 2), 2, 4, 6);
  assert(2 == g.x);
  assert(4 == g.y);
  assert(6 == g.z);

  vec3 h;
  vec3_set(h, 2, 4, 6);
  assert(2 == h.x);
  assert(4 == h.y);
  assert(6 == h.z);

  // add
  vec3 sum = vec3_add(vec3(1, 1, 1), vec3(2, 2, 2));
  assert(3 == sum.x);
  assert(3 == sum.y);
  assert(3 == sum.z);

  // max
  vec3 max = vec3_max(vec3(2, 4, 6), vec3(4, 2, 0));
  assert(4 == max.x);
  assert(4 == max.y);
  assert(6 == max.z);

  // min
  vec3 min = vec3_min(vec3(2, 4, 6), vec3(4, 2, 0));
  assert(2 == min.x);
  assert(2 == min.y);
  assert(0 == min.z);

  // scale
  vec3 scaled = vec3_scale(vec3(2, 2, 2), 2);
  assert(4 == scaled.x);
  assert(4 == scaled.y);
  assert(4 == scaled.z);

  // distance
  float distance = vec3_distance(vec3(1, 1, 1), vec3(5, 5, 5));
  float expected = 6.92820;
  assert(fcmp(expected, distance));

  // distance squared
  float distance2 = vec3_distance_squared(vec3(1, 1, 1), vec3(2, 2, 2));
  float expected2 = 3.0;
  assert(fcmp(expected2, distance2));

  // length
  float length = vec3_length(vec3(2, 2, 2));
  float expected3 = 3.464101;
  assert(fcmp(length, expected3));

  // length squared
  float lengthsq = vec3_length_squared(vec3(2, 2, 2));
  float expected4 = 12;
  assert(lengthsq == expected4);

  // negate
  vec3 negated = vec3_negate(a);
  assert(-a.x == negated.x);
  assert(-a.y == negated.y);
  assert(-a.z == negated.z);

  // inverse
  vec3 inverse = vec3_inverse(vec3(4, 2, 1));
  assert(0.25 == inverse.x);
  assert(0.5 == inverse.y);
  assert(1 == inverse.z);

  // normalize
  vec3 normalized = vec3_normalize(vec3(10, 20, 30));
  vec3 expected5 = vec3(0.26726124191242434, 0.5345224838248487, 0.8017837257372731);
  assert(fcmp(normalized.x, expected5.x));
  assert(fcmp(normalized.y, expected5.y));

  // dot product
  assert(fcmp(44.0f, vec3_dot(vec3(2, 4, 6), vec3(1, 3, 5))));

  // cross product
  vec3 cross = vec3_cross(vec3(2, 4, 6), vec3(1, 3, 5));
  assert(2 == cross.x);
  assert(-4 == cross.y);
  assert(2 == cross.z);

  // lerp
  vec3 interpolated = vec3_lerp(vec3(2, 4, 6), vec3(3, 5, 7), 0.45);
  assert(fcmp(2.45, interpolated.x));
  assert(fcmp(4.45, interpolated.y));
  assert(fcmp(6.45, interpolated.z));

  // random
  vec3 random = vec3_random(5);
  assert(random.x != 0);
  assert(random.y != 0);
  assert(random.z != 0);

  // @TODO(werle) - hermite
  // @TODO(werle) - bezier
  // @TODO(werle) - transform
  // @TODO(werle) - transformMat4
  // @TODO(werle) - transformQuat
  // @TODO(werle) - rotateX
  // @TODO(werle) - rotateY
  // @TODO(werle) - rotateZ
  // @TODO(werle) - angle

  return 0;
}
