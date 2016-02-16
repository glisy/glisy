#ifndef GLISY_BUFFER_H
#define GLISY_BUFFER_H

#include <stdio.h>
#include <glisy/gl.h>

/**
 * Glisy Buffer struct type.
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
 * Glisy Buffer initializer.
 * This function initializes a glisy_buffer struct. The buffer's handle is set
 * to 0 and the target is set to the value of the target param. If the
 * target param is 0, the buffer will point to the global GL_ARRAY_BUFFER
 * memory location. If the buffer param is NULL or undefined the function fails.
 *
 * @param buffer * - pointer to a glisy_buffer struct.
 * @param target   - unsigned int referencing the buffer's target.
 */

void
glisy_buffer_init(glisy_buffer *buffer, GLuint target);

/**
 * Glisy Buffer bind.
 * This function uses glGenBuffers() to tell OpenGL to allocate space for this
 * buffer and glBindBuffer() to bind the buffer's handle to its target. If the
 * buffer param is NULL or undefined the function fails.
 *
 * @param buffer * - pointer to a glisy_buffer struct.
 */

void
glisy_buffer_bind(glisy_buffer *buffer);

/**
 * Glisy Buffer unbind.
 * This function uses glBindBuffer() to reset the buffer's target to 0. If the
 * buffer param is NULL or undefined the function fails.
 *
 * @param buffer * - pointer to a glisy_buffer struct.
 */

void
glisy_buffer_unbind(glisy_buffer *buffer);

/**
 * Glisy Buffer dispose.
 * This function uses glDeleteBuffers() to deallocate the buffer's memory and
 * resets its handle to 0. If the buffer param is NULL or undefined the function
 * fails.
 *
 * @param buffer * - pointer to a glisy_buffer struct.
 */

void
glisy_buffer_dispose(glisy_buffer *buffer);

/**
 * Glisy Buffer update.
 * This function uses glBufferData() to create the buffer's data in memory. If
 * the buffer param is NULL or undefined the function fails.
 *
 * @param buffer * - pointer to a glisy_buffer struct.
 * @param usage    - unsigned int referencing the buffer's usage.
 */

void
glisy_buffer_update(glisy_buffer *buffer, GLuint usage);

/**
 * Glisy Buffer source.
 * This function prepares the buffer's data so it is ready to be created by
 * glisy_buffer_update(). If the buffer or data params are NULL or undefined the
 * function fails.
 *
 * @param buffer * - pointer to a glisy_buffer struct.
 * @param size     - the size of the data stored in the buffer.
 * @param data   * - the actual buffer data to be rendered.
 */

void
glisy_buffer_source(glisy_buffer *buffer, GLsizei size, GLvoid *data);

#endif
