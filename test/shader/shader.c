#include <assert.h>
#include <glisy/glisy.h>

const char *vertexSource =
  ""
;

const char *fragmentSource =
  ""
;

int
main (void) {
  glisy_shader vertex;
  glisy_shader fragment;
  //assert(glisy_shader_init(&vertex, GL_VERTEX_SHADER, vertexSource));
  //assert(glisy_shader_init(&fragment, GL_FRAGMENT_SHADER, fragmentSource));
  return 0;
}
