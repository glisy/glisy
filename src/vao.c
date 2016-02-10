#include <stdio.h>
#include <stdlib.h>
#include <glisy/gl.h>
#include <glisy/vao.h>
#include <glisy/buffer.h>

#define max(a,b) ({        \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b;       \
})

#define min(a,b) ({        \
  __typeof__ (a) _a = (a); \
  __typeof__ (b) _b = (b); \
  _a <_b ? _a : _b;        \
})

void
glisy_vao_init(glisy_vao *vao) {
  vao->length = 0;
  memset(vao->attributes, 0, sizeof(glisy_vao_attribute) * GLISY_MAX_VAO_ATTRIBS);
}


void
glisy_vao_attribute_bind(glisy_vao_attribute *attribute) {
  GLfloat data[4];
  GLuint dimension = attribute->buffer.dimension;
  GLuint location = attribute->location;
  memcpy(&data, &attribute->buffer.data, sizeof(data));
  switch (dimension) {
  case 4:
    glVertexAttrib4f(location, data[0], data[1], data[2], data[3]);
    break;
  case 3:
    glVertexAttrib3f(location, data[0], data[1], data[2]);
    break;
  case 2:
    glVertexAttrib2f(location, data[0], data[1]);
    break;
  case 1:
    glVertexAttrib1f(location, data[0]);
    break;
  }
}

void
glisy_vao_bind(glisy_vao *vao) {
}

void
glisy_vao_unbind(glisy_vao *vao) {
  glBindVertexArray(0);
}

void
glisy_vao_dispose(glisy_vao *vao) {
  glDeleteVertexArrays(1, &vao->handle);
  vao->handle = 0;
}

GLuint
glisy_vao_push(glisy_vao *vao, glisy_vao_attribute attr) {
  if (vao->length < GLISY_MAX_VAO_ATTRIBS) {
    attr.location = vao->length;
    vao->attributes[vao->length++] = attr;
  }
  return vao->length;
}

GLuint
glisy_vao_set(glisy_vao *vao, GLuint location, glisy_vao_attribute attr) {
  GLuint max = GLISY_MAX_VAO_ATTRIBS;
  if (vao->length < max && location < max) {
    attr.location = location;
    vao->attributes[location] = attr;
  }
  return vao->length;
}

void
glisy_vao_update(glisy_vao *vao) {
  GLuint length = vao->length;
  GLuint vbo[length];

  // initialize VBO and VAO
  glGenBuffers(length, vbo);
  glGenVertexArrays(1, &vao->handle);
  glBindVertexArray(vao->handle);

  for (int i = 0; i < length; ++i) {
    // bind this VBO and setup attribute pointer
    GLuint location = i;
    glisy_vao_attribute *attr = &vao->attributes[i];
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
    glBufferData(GL_ARRAY_BUFFER,
                 attr->buffer.size,
                 attr->buffer.data,
                 attr->buffer.usage);

    glVertexAttribPointer(location,
                          attr->buffer.dimension,
                          GL_FLOAT,
                          GL_FALSE,
                          0, 0);

    glEnableVertexAttribArray(location);
  }
}
