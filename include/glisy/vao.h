#ifndef GLISY_VAO_H
#define GLISY_VAO_H

#include <glisy/gl.h>
#include <glisy/math.h>
#include <glisy/buffer.h>

#define GLISY_MAX_VAO_ATTRIBS 64

/**
 */

typedef struct glisy_vao_attribute glisy_vao_attribute;
struct glisy_vao_attribute {
  GLuint location;
  char *name;

  struct {
    GLfloat data[BUFSIZ];
    GLuint type;
    GLuint size;
    GLuint usage;
    GLuint stride;
    GLuint offset;
    GLuint dimension;
    GLboolean normalized;
  } buffer;
};

/**
 */

typedef struct glisy_vao glisy_vao;
struct glisy_vao {
  GLuint handle;
  GLuint length;
  glisy_vao_attribute attributes[GLISY_MAX_VAO_ATTRIBS];
  GLboolean useElements;
};

/**
 */

void
glisy_vao_init(glisy_vao *vao);

/**
 */

void
glisy_vao_bind(glisy_vao *vao);

/**
 */

void
glisy_vao_unbind(glisy_vao *vao);

/**
 */

void
glisy_vao_dispose(glisy_vao *vao);

/**
 */

void
glisy_vao_update(glisy_vao *vao, glisy_buffer *elements);

GLuint
glisy_vao_push(glisy_vao *vao, glisy_vao_attribute *attr);

GLuint
glisy_vao_pop(glisy_vao *vao);

GLuint
glisy_vao_splice(glisy_vao *vao, GLint start, GLuint count);

GLuint
glisy_vao_set(glisy_vao *vao, GLuint location, glisy_vao_attribute *attr);

GLuint
glisy_vao_remove(glisy_vao *vao, GLuint location);

/**
 */

void
glisy_vao_attribute_bind(glisy_vao_attribute *attribute);

#endif
