#include <stdio.h>
#include <string.h>
#include <glisy/gl.h>
#include <glisy/buffer.h>

void
glisyBufferInit(GlisyBuffer *buffer, GLuint target) {
  if (!buffer) return;
  if (target == 0) target = GL_ARRAY_BUFFER;
  buffer->handle = 0;
  buffer->target = target;
}

void
glisyBufferBind(GlisyBuffer *buffer) {
  if (!buffer) return;
  glGenBuffers(1, &buffer->handle);
  glBindBuffer(buffer->target, buffer->handle);
}

void
glisyBufferUnbind(GlisyBuffer *buffer) {
  if (!buffer) return;
  glBindBuffer(buffer->target, 0);
}

void
glisyBufferDispose(GlisyBuffer *buffer) {
  if (!buffer) return;
  glDeleteBuffers(1, &buffer->handle);
  buffer->handle = 0;
}

void
glisyBufferUpdate(GlisyBuffer *buffer, GLuint usage) {
  if (!buffer) return;
  glBufferData(buffer->target,
               buffer->size,
               buffer->data,
               usage);
}

void
glisyBufferSource(GlisyBuffer *buffer, GLsizei size, GLvoid *data) {
  if (!buffer) return;
  if (!data) return;
  buffer->size = size;
  buffer->data = data;
}
