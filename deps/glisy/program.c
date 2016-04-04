#include <stdlib.h>
#include <glisy/program.h>

GLboolean
glisyProgramInit(GlisyProgram *program) {
  if (!program) return GL_FALSE;

  program->id = glCreateProgram();
  if (program->id == 0) return GL_FALSE;

  return GL_TRUE;
}

GLboolean
glisyProgramAttachShader(const GlisyProgram *program, const GlisyShader *shader) {
  if (!program) return GL_FALSE;
  if (!shader)  return GL_FALSE;

  // @TODO(jwerle): error handling
  glAttachShader(program->id, shader->id);

  return GL_TRUE;
}

GLboolean
glisyProgramLink(GlisyProgram *program) {
  GLint isLinked = 0;

  if (!program) return GL_FALSE;

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

    glisyProgramDelete(program);
    return GL_FALSE;
  }

  return GL_TRUE;
}

GLboolean
glisyProgramBind(GlisyProgram *program) {
  if (!program) return GL_FALSE;
  if (!program->id) {
    if (!glisyProgramLink(program)) return GL_FALSE;
  }

  glUseProgram(program->id);
  return GL_TRUE;
}

GLboolean
glisyProgramDelete(GlisyProgram *program) {
  if (!program) return GL_FALSE;
  if (program->id == 0) return GL_FALSE;

  glDeleteProgram(program->id);

  return GL_TRUE;
}
