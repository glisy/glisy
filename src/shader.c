#include <string.h>
#include <glisy/gl.h>
#include <glisy/shader.h>

int
glisy_shader_init (glisy_shader this,
                   const char *vertex,
                   const char *fragment) {
  size_t vertex_len = 1 + strlen(vertex) + strlen(GLISY_GLSL_VERTEX_SHADER_HEADER);
  size_t fragment_len = 1 + strlen(fragment) + strlen(GLISY_GLSL_FRAGMENT_SHADER_HEADER);
  char vertex_src[vertex_len];
  char fragment_src[fragment_len];

  memset(vertex_src, 0, sizeof(vertex_src));
  memset(fragment_src, 0, sizeof(fragment_src));

#define compile(type, source, size) {         \
  GLuint shader = glCreateShader(type);       \
  glShaderSource(shader, 1, &source, 0);      \
  glCompileShader(shader);                    \
}

  compile(GL_VERTEX_SHADER, vertex_src, vertex_len);
  //compile(GL_FRAGMENT_SHADER, (const char **) &fragment_src, fragment_len);

#undef compile
#undef CHECK
  return 0;
}
