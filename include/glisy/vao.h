#ifndef GLISY_VAO_H
#define GLISY_VAO_H

#include <glisy/gl.h>
#include <glisy/math.h>
#include <glisy/buffer.h>

#ifndef GLISY_MAX_VAO_ATTRIBS
#define GLISY_MAX_VAO_ATTRIBS 64
#endif

/**
 * Glisy VAO Attribute struct type.
 */

typedef struct glisy_vao_attribute glisy_vao_attribute;
struct glisy_vao_attribute {
  GLuint location;
  const char *name;

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
 * Glisy VAO struct type.
 */

typedef struct glisy_vao glisy_vao;
struct glisy_vao {
  GLuint handle;
  GLuint length;
  glisy_vao_attribute attributes[GLISY_MAX_VAO_ATTRIBS];
  GLboolean useElements;
};

/**
 * This function initializes a glisy_vao struct with default values. Memory is
 * allocated and initialized, and glGenVertexArrays() is called to generate a
 * value for the handle member. The length member defaults to 0 and useElements
 * defaults to false. If the vao param is NULL or undefined the function returns.
 *
 * @param vao * - pointer to a glisy_vao struct.
 */

void
glisy_vao_init(glisy_vao *vao);

/**
 * This function calls glBindVertexArray() to bind the verticies stored in the
 * memory location of the vao handle member. If the vao param is NULL or
 * undefined the function returns.
 *
 * @param vao * - pointer to a glisy_vao struct.
 */

void
glisy_vao_bind(glisy_vao *vao);

/**
 * This function calls glBindVertexArray(0) to clear any bound verticies. If the
 * vao param is NULL or undefined the function returns.
 *
 * @param vao * - pointer to a glisy_vao struct.
 */

void
glisy_vao_unbind(glisy_vao *vao);

/**
 * This function calls glDeleteVertexArrays() to destroy any verticies stored in
 * the memory location of the vao handle member. If the vao param is NULL or
 * undefined the function returns.
 *
 * @param vao * - pointer to a glisy_vao struct.
 */

void
glisy_vao_dispose(glisy_vao *vao);

/**
 * This function resets and reinitializes the vao and all of its attributes. The
 * elements param is optional. If a properly initialized glisy_buffer is passed
 * in, it will be bound and the vao useElements member will be set to true. If
 * elements are not being used, pass NULL to disable. If the vao param is NULL
 * or undefined the function will return.
 *
 * @param vao      * - pointer to a glisy_vao struct.
 * @param elements * - pointer to a glisy_buffer struct.
 */

void
glisy_vao_update(glisy_vao *vao, glisy_buffer *elements);

/**
 * This function pushes attr param onto the vao's internal attributes member
 * list of attributes. If the vao or attr params are NULL or undefined the
 * function returns false, otherwise it returns the new length of the vao.
 *
 * @param vao  * - pointer to a glisy_vao struct.
 * @param attr * - pointer to a glisy_vao_attribute struct.
 */

GLuint
glisy_vao_push(glisy_vao *vao, glisy_vao_attribute *attr);

/**
 * @TODO(jwerle): implement glisy_vao_pop
 *
 * @param vao * - pointer to a glisy_vao struct.
 */

GLuint
glisy_vao_pop(glisy_vao *vao);

/**
 * @TODO(jwerle): implement glisy_vao_splice
 *
 * @param vao * - pointer to a glisy_vao struct.
 * @param start - index at which to start slicing.
 * @param count - length of the slice.
 */

GLuint
glisy_vao_splice(glisy_vao *vao,
                 GLint start,
                 GLuint count);

/**
 * This function places a vao attribute into vao at the index specified by
 * location. If the location exceeds GLISY_MAX_VAO_ATTRIBS or if the vao's
 * length is already at that maximum, nothing will be done. If the vao or attr
 * params are NULL or undefined the function returns false, otherwise it returns
 * the new vao length.
 *
 * @param vao    * - pointer to a glisy_vao struct.
 * @param location - index at which to set the new vao attribute.
 * @param attr   * - pointer to a glisy_vao_attribute struct.
 */

GLuint
glisy_vao_set(glisy_vao *vao,
              GLuint location,
              glisy_vao_attribute *attr);

/**
 * @TODO(jwerle): implement glisy_vao_remove
 *
 * @param vao    * - pointer to a glisy_vao struct.
 * @param location - index of the attr to be removed.
 */

GLuint
glisy_vao_remove(glisy_vao *vao, GLuint location);

/**
 * This function initializes and binds a glisy_vao_attribute struct. If the
 * attribute param is NULL or undefined the function returns.
 *
 * @param attribute * - pointer to a glisy_vao_attribute struct.
 */

void
glisy_vao_attribute_bind(glisy_vao_attribute *attribute);

#endif
