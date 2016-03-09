#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glisy/gl.h>
#include <glisy/shader.h>

GLboolean
glisy_shader_init(glisy_shader *shader, GLuint type, const char *source) {
  GLint isCompiled = 0;

  if (shader == NULL) return GL_FALSE;

  shader->id = glCreateShader(type);
  if (shader->id == 0) return GL_FALSE;

  shader->type = type;
  shader->source = strdup(source);

  glShaderSource(shader->id, 1, &source, 0);
  glCompileShader(shader->id);

  glGetShaderiv(shader->id, GL_COMPILE_STATUS, &isCompiled);

  if (!isCompiled) {
    GLint infoLen = 0;

    glGetShaderiv(shader->id, GL_INFO_LOG_LENGTH, &infoLen);

    if (infoLen > 1) {
       char *infoLog = malloc(sizeof (char) * infoLen);

       glGetShaderInfoLog(shader->id, infoLen, NULL, infoLog);
       printf("Error compiling shader:\n%s\n", infoLog);

       free(infoLog);
    }

    glDeleteShader(shader->id);
    return GL_FALSE;
  }

  return GL_TRUE;
}
