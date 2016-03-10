#ifndef GLISY_UNIFORM_H
#define GLISY_UNIFORM_H

#include <glisy/gl.h>
#include <glisy/program.h>

enum {
  GLISY_UNIFORM_VECTOR = 1,
  GLISY_UNIFORM_MATRIX,
  GLISY_UNIFORM_DOUBLE,
  GLISY_UNIFORM_FLOAT,
  GLISY_UNIFORM_BOOL,
  GLISY_UNIFORM_UINT,
  GLISY_UNIFORM_INT,
};

typedef struct GlisyUniform GlisyUniform;
struct GlisyUniform {
  const char *name;
  GLvoid *buffer;
  GLuint dimension;
  GLint location;
  GLsizei size;
  GLuint type;
};

void
glisyUniformInit(GlisyUniform *uniform,
                   const char *name,
                   GLuint type,
                   GLuint dimension);

void
glisyUniformBind(GlisyUniform *uniform, GlisyProgram *program);

void
glisyUniformSet(GlisyUniform *uniform, GLvoid *data, GLsizei size);

#endif
