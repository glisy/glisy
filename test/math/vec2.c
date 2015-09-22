#include <assert.h>
#include <glisy/math/vec2.h>
#include <glisy/math/vec3.h>
#include <glisy/math/mat2.h>
#include <glisy/math/mat3.h>

#include "../test.h"

int
main (void) {
  // init
  vec2 a = vec2(1, 1);
  assert(1 == a.x);
  assert(1 == a.y);

  // clone
  vec2 b = vec2_clone(a);
  assert(b.x == a.x);
  assert(b.y == a.y);

  // subtract
  vec2 c = vec2_subtract(a, b);
  assert(0 == c.x);
  assert(0 == c.y);

  // multiply
  vec2 d = vec2_multiply(vec2(2, 2), vec2(2, 2));
  assert(4 == d.x);
  assert(4 == d.y);

  // divide
  vec2 e = vec2_divide(vec2(4, 4), vec2(2, 2));
  assert(2 == e.x);
  assert(2 == e.y);

  // copy
  vec2 f;
  vec2_copy(f, a);
  assert(f.y == a.y);
  assert(f.x == a.x);

  // set
  vec2 g = vec2_set(vec2(0, 1), 2, 4);
  assert(2 == g.x);
  assert(4 == g.y);
  vec2 h;
  vec2_set(h, 2, 4);
  assert(2 == h.x);
  assert(4 == h.y);

  // add
  vec2 sum = vec2_add(vec2(1, 1), vec2(2, 2));
  assert(3 == sum.x);
  assert(3 == sum.y);

  // max
  vec2 max = vec2_max(vec2(2, 4), vec2(4, 2));
  assert(4 == max.x);
  assert(4 == max.y);

  // min
  vec2 min = vec2_min(vec2(2, 4), vec2(4, 2));
  assert(2 == min.x);
  assert(2 == min.y);

  // scale
  vec2 scaled = vec2_scale(vec2(2, 2), 2);
  assert(4 == scaled.x);
  assert(4 == scaled.y);

  // distance
  float distance = vec2_distance(vec2(1, 1), vec2(5, 5));
  float expected = 5.656854;
  assert(expected == distance);

  // distance squared
  float distance2 = vec2_distance_squared(vec2(1, 1), vec2(2, 2));
  float expected2 = 2.0;
  assert(expected2 == distance2);

  // length
  float length = vec2_length(vec2(2, 2));
  float expected3 = 2.828427;
  assert(length == expected3);

  // length squared
  float lengthsq = vec2_length_squared(vec2(2, 2));
  float expected4 = 8;
  assert(lengthsq == expected4);

  // negate
  vec2 negated = vec2_negate(a);
  assert(-a.x == negated.x);
  assert(-a.y == negated.y);

  // inverse
  vec2 inverse = vec2_inverse(vec2(4, 2));
  assert(0.25 == inverse.x);
  assert(0.5 == inverse.y);

  // normalize
  vec2 normalized = vec2_normalize(vec2(10, 20));
  vec2 expected5 = vec2(0.447214, 0.894427);
  assert(fcmp(normalized.x, expected5.x));
  assert(fcmp(normalized.y, expected5.y));

  // dot product
  assert(14.0f == vec2_dot(vec2(2, 4), vec2(1, 3)));

  // cross product
  vec3 cross = vec2_cross(vec2(2, 4), vec2(1, 3));
  assert(0 == cross.x);
  assert(0 == cross.y);
  assert(2 == cross.z);

  // lerp
  vec2 interpolated = vec2_lerp(vec2(2, 4), vec2(3, 5), 0.45);
  assert(fcmp(4.45, interpolated.y));
  assert(fcmp(2.45, interpolated.x));

  // random
  vec2 random = vec2_random(5);
  assert(random.x != 0);
  assert(random.y != 0);

  // mat2 transform
  mat2 mat2id = mat2_create(); // identity
  vec2 vec2mat2 = vec2_transform_mat2(vec2(5, 5), mat2id);
  // vec2 left intact when transform applied from identity matrix
  assert(fcmp(5.0 , vec2mat2.x));
  assert(fcmp(5.0 , vec2mat2.y));
  mat2 mat2a = mat2(1, 1, 1, 1);
  vec2 vec2mat2a = vec2_transform_mat2(vec2(5, 5), mat2a);
  assert(fcmp(10.0 , vec2mat2a.x));
  assert(fcmp(10.0 , vec2mat2a.y));

  vec2 vec2mat3 = vec2_transform_mat2(vec2(M_PI, 1), mat3(-1,0,0,
                                                           0,1,0,
                                                           0,0,-1));

  assert(fcmp(-M_PI, vec2mat3.x));
  assert(fcmp(1, vec2mat3.y));

  // @TODO(werle) - mat4 transform

  // string
  const char *str = vec2_string(vec2(2.34567, 4.5678));
  assert(0 == strcmp("vec2(2.34567, 4.5678)", str));
  return 0;
}
