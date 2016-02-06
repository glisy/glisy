#ifndef GLISY_BUFFER_H
#define GLISY_BUFFER_H

#include <glisy/gl.h>

typedef struct glisy_buffer glisy_buffer;
struct glisy_buffer {
  GLenum target;
  GLuint buffer;
};

glisy_buffer_init (glisy_buffer buffer);

#endif
