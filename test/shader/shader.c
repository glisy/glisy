
#include <glisy/glisy.h>

#define VERTEX ""

#define FRAGMENT ""

int
main (void) {
  glisy_shader shader;
  glisy_shader_init(shader, VERTEX, FRAGMENT);
  return 0;
}
