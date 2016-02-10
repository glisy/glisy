#ifndef GLISY_BUFFER_H
#define GLISY_BUFFER_H

#include <stdio.h>
#include <glisy/gl.h>

/**
 */

typedef struct glisy_buffer glisy_buffer;
struct glisy_buffer {
  GLuint target;
  GLuint size;
  GLuint usage;
  GLuint handle;
  GLfloat data[BUFSIZ];
};

/**
 */

void
glisy_buffer_init(glisy_buffer *buffer, GLuint target);

/**
 */

void
glisy_buffer_bind(glisy_buffer *buffer);

/**
*/

void
glisy_buffer_unbind(glisy_buffer *buffer);

/**
*/

void
glisy_buffer_dispose(glisy_buffer *buffer);

/**
 */

void
glisy_buffer_source(glisy_buffer *buffer, GLsizei size, GLvoid *data);

/**
*/

void
glisy_buffer_update(glisy_buffer *buffer, GLuint usage);

#endif
