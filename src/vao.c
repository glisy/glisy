#include <stdio.h>
#include <stdlib.h>
#include <glisy/gl.h>
#include <glisy/vao.h>
#include <glisy/buffer.h>

void
glisy_vao_init(glisy_vao *vao) {
  vao->length = 0;
  vao->useElements = GL_FALSE;
  memset(vao->attributes, 0, sizeof(glisy_vao_attribute) * GLISY_MAX_VAO_ATTRIBS);
  glGenVertexArrays(1, &vao->handle);
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
  glBindVertexArray(vao->handle);
}

void
glisy_vao_unbind(glisy_vao *vao) {
  glBindVertexArray(0);
}

void
glisy_vao_dispose(glisy_vao *vao) {
  glDeleteVertexArrays(1, &vao->handle);
  vao->handle = 0;
  vao->length = 0;
  vao->useElements = GL_FALSE;
}

GLuint
glisy_vao_push(glisy_vao *vao, glisy_vao_attribute *attr) {
  if (vao->length < GLISY_MAX_VAO_ATTRIBS) {
    attr->location = vao->length;
    vao->attributes[vao->length++] = *attr;
  }
  return vao->length;
}

GLuint
glisy_vao_set(glisy_vao *vao, GLuint location, glisy_vao_attribute *attr) {
  GLuint max = GLISY_MAX_VAO_ATTRIBS;
  if (vao->length < max && location < max) {
    attr->location = location;
    vao->attributes[location] = *attr;
    vao->length = location < vao->length ? vao->length : location;
  }
  return vao->length;
}

void
glisy_vao_update(glisy_vao *vao, glisy_buffer *elements) {
  // number of bound attributes for this VAO
  GLuint length = vao->length;

  // vertex buffer objects of VAO attribute length
  GLuint vbo[length];

  // bind vao
  glisy_vao_bind(vao);

  // init vbo
  glGenBuffers(length, vbo);

  // bind elements if given
  if (elements) {
    glisy_buffer_bind(elements);
    vao->useElements= GL_TRUE;
  } else {
    vao->useElements= GL_FALSE;
  }

  // bind vao attributes
  for (int i = 0; i < length; ++i) {
    GLuint location = i;
    glisy_vao_attribute *attr = &vao->attributes[i];

    // ensure .normalized is true or false
    if (GL_TRUE != attr->buffer.normalized)
      attr->buffer.normalized = GL_FALSE;

    // bind current vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);

    // set vbo data from attribute
    glBufferData(GL_ARRAY_BUFFER,
                 attr->buffer.size,
                 attr->buffer.data,
                 attr->buffer.usage);

    // bind attribute to location
    glVertexAttribPointer(location,
                          attr->buffer.dimension,
                          attr->buffer.type,
                          attr->buffer.normalized,
                          0, 0);

    // enable attribute at location
    glEnableVertexAttribArray(location);
  }
}
