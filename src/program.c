#include <stdlib.h>
#include <glisy/program.h>

GLboolean
glisy_program_init(glisy_program *program) {
  if (program == NULL) return GL_FALSE;

  program->id = glCreateProgram();
  if (program->id == 0) return GL_FALSE;

  return GL_TRUE;
}

GLboolean
glisy_program_attach_shader(const glisy_program *program, const glisy_shader *shader) {
  if (program == NULL) return GL_FALSE;
  if (shader == NULL) return GL_FALSE;

  // @TODO(jwerle): error handling
  glAttachShader(program->id, shader->id);
  return GL_TRUE;
}

GLboolean
glisy_program_link(glisy_program *program) {
  GLint isLinked = 0;

  if (program == NULL) return GL_FALSE;

  glLinkProgram(program->id);
  glGetProgramiv(program->id, GL_LINK_STATUS, &isLinked);
  if (!isLinked) {
    GLint infoLen = 0;

    glGetProgramiv(program->id, GL_INFO_LOG_LENGTH, &infoLen);

    if (infoLen > 1) {
      char *infoLog = malloc(sizeof (char) * infoLen);

      glGetProgramInfoLog (program->id, infoLen, NULL, infoLog);
      printf("Error linking program:\n%s\n", infoLog);

      free(infoLog);
    }

    glisy_program_delete(program);
    return GL_FALSE;
  }

  return GL_TRUE;
}

GLboolean
glisy_program_delete(glisy_program *program) {
  if (program == NULL) return GL_FALSE;
  if (program->id == 0) return GL_FALSE;
  glDeleteProgram(program->id);
  return GL_TRUE;
}

