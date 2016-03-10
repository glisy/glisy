#ifndef GLISY_BUFFER_H
#define GLISY_BUFFER_H

#include <stdio.h>
#include <glisy/gl.h>

/**
 * Glisy Buffer struct type.
 */

typedef struct GlisyBuffer GlisyBuffer;
struct GlisyBuffer {
  GLuint target;
  GLuint size;
  GLuint usage;
  GLuint handle;
  GLvoid *data;
};

/**
 * Glisy Buffer initializer.
 * This function initializes a GlisyBuffer struct. The buffer's handle is set
 * to 0 and the target is set to the value of the target param. If the
 * target param is 0, the buffer will point to the global GL_ARRAY_BUFFER
 * memory location. If the buffer param is NULL or undefined the function fails.
 *
 * @param buffer * - pointer to a GlisyBuffer struct.
 * @param target   - unsigned int referencing the buffer's target.
 */

void
glisyBufferInit(GlisyBuffer *buffer, GLuint target);

/**
 * Glisy Buffer bind.
 * This function uses glGenBuffers() to tell OpenGL to allocate space for this
 * buffer and glBindBuffer() to bind the buffer's handle to its target. If the
 * buffer param is NULL or undefined the function fails.
 *
 * @param buffer * - pointer to a GlisyBuffer struct.
 */

void
glisyBufferBind(GlisyBuffer *buffer);

/**
 * Glisy Buffer unbind.
 * This function uses glBindBuffer() to reset the buffer's target to 0. If the
 * buffer param is NULL or undefined the function fails.
 *
 * @param buffer * - pointer to a GlisyBuffer struct.
 */

void
GlisyBuffer_unbind(GlisyBuffer *buffer);

/**
 * Glisy Buffer dispose.
 * This function uses glDeleteBuffers() to deallocate the buffer's memory and
 * resets its handle to 0. If the buffer param is NULL or undefined the function
 * fails.
 *
 * @param buffer * - pointer to a GlisyBuffer struct.
 */

void
glisyBufferDispose(GlisyBuffer *buffer);

/**
 * Glisy Buffer update.
 * This function uses glBufferData() to create the buffer's data in memory. If
 * the buffer param is NULL or undefined the function fails.
 *
 * @param buffer * - pointer to a GlisyBuffer struct.
 * @param usage    - unsigned int referencing the buffer's usage.
 */

void
glisyBufferUpdate(GlisyBuffer *buffer, GLuint usage);

/**
 * Glisy Buffer source.
 * This function prepares the buffer's data so it is ready to be created by
 * GlisyBuffer_update(). If the buffer or data params are NULL or undefined the
 * function fails.
 *
 * @param buffer * - pointer to a GlisyBuffer struct.
 * @param size     - the size of the data stored in the buffer.
 * @param data   * - the actual buffer data to be rendered.
 */

void
glisyBufferSource(GlisyBuffer *buffer, GLsizei size, GLvoid *data);

#endif
