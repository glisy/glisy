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

typedef struct glisy_uniform glisy_uniform;
struct glisy_uniform {
  const char *name;
  void *buffer;
  GLuint dimension;
  GLint location;
  GLsizei size;
  GLuint type;
};

void
glisy_uniform_init(glisy_uniform *uniform,
                   const char *name,
                   GLuint type,
                   GLuint dimension);

void
glisy_uniform_bind(glisy_uniform *uniform, glisy_program *program);

void
glisy_uniform_set(glisy_uniform *uniform, void *data, GLsizei size);

#endif
