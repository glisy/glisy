#include <stdio.h>
#include <string.h>
#include <glisy/gl.h>
#include <glisy/buffer.h>

void
glisy_buffer_init(glisy_buffer *buffer, GLuint target) {
  if (!buffer) return;
  if (target == 0) target = GL_ARRAY_BUFFER;
  buffer->handle = 0;
  buffer->target = target;
}

void
glisy_buffer_bind(glisy_buffer *buffer) {
  glGenBuffers(1, &buffer->handle);
  glBindBuffer(buffer->target, buffer->handle);
}

void
glisy_buffer_unbind(glisy_buffer *buffer) {
  glBindBuffer(buffer->target, 0);
}

void
glisy_buffer_dispose(glisy_buffer *buffer) {
  glDeleteBuffers(1, &buffer->handle);
  buffer->handle = 0;
}

void
glisy_buffer_update(glisy_buffer *buffer, GLuint usage) {
  glBufferData(buffer->target,
               buffer->size,
               buffer->data,
               usage);
}

void
glisy_buffer_source(glisy_buffer *buffer, GLsizei size, GLvoid *data) {
  if (!buffer) return;
  buffer->size = size;
  memset(buffer->data, 0, BUFSIZ);
  memcpy(buffer->data, data, size);
}
