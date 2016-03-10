#ifndef GLISY_VAO_H
#define GLISY_VAO_H

#include <glisy/gl.h>
#include <glisy/math.h>
#include <glisy/buffer.h>

#ifndef GLISY_MAX_VAO_ATTRIBS
#define GLISY_MAX_VAO_ATTRIBS 0xff
#endif

/**
 * Glisy VAO Attribute struct type.
 */

typedef struct GlisyVAOAttribute GlisyVAOAttribute;
struct GlisyVAOAttribute {
  GLuint location;
  const char *name;

  struct {
    GLvoid *data;
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

typedef struct GlisyVAO GlisyVAO;
struct GlisyVAO {
  GLuint handle;
  GLuint length;
  GlisyVAOAttribute attributes[GLISY_MAX_VAO_ATTRIBS];
  GLboolean useElements;
};

/**
 * This function initializes a GlisyVAO struct with default values. Memory is
 * allocated and initialized, and glGenVertexArrays() is called to generate a
 * value for the handle member. The length member defaults to 0 and useElements
 * defaults to false. If the vao param is NULL or undefined the function returns.
 *
 * @param vao - pointer to a GlisyVAO struct.
 */

void
glisyVAOInit(GlisyVAO *vao);

/**
 * This function calls glBindVertexArray() to bind the verticies stored in the
 * memory location of the vao handle member. If the vao param is NULL or
 * undefined the function returns.
 *
 * @param vao - pointer to a GlisyVAO struct.
 */

void
glisyVAOBind(GlisyVAO *vao);

/**
 * This function calls glBindVertexArray(0) to clear any bound verticies. If the
 * vao param is NULL or undefined the function returns.
 *
 * @param vao - pointer to a GlisyVAO struct.
 */

void
glisyVAOUnbind(GlisyVAO *vao);

/**
 * This function calls glDeleteVertexArrays() to destroy any verticies stored in
 * the memory location of the vao handle member. If the vao param is NULL or
 * undefined the function returns.
 *
 * @param vao - pointer to a GlisyVAO struct.
 */

void
glisyVAODispose(GlisyVAO *vao);

/**
 * This function resets and reinitializes the vao and all of its attributes. The
 * elements param is optional. If a properly initialized GlisyBuffer is passed
 * in, it will be bound and the vao useElements member will be set to true. If
 * elements are not being used, pass NULL to disable. If the vao param is NULL
 * or undefined the function will return.
 *
 * @param vao      - pointer to a GlisyVAO struct.
 * @param elements - pointer to a GlisyBuffer struct.
 */

void
glisyVAOUpdate(GlisyVAO *vao, GlisyBuffer *elements);

/**
 * This function pushes attr param onto the vao's internal attributes member
 * list of attributes. If the vao or attr params are NULL or undefined the
 * function returns false, otherwise it returns the new length of the vao.
 *
 * @param vao  - pointer to a GlisyVAO struct.
 * @param attr - pointer to a GlisyVAOAttribute struct.
 */

GLuint
glisyVAOPush(GlisyVAO *vao, GlisyVAOAttribute *attr);

/**
 * @TODO(jwerle): implement glisyVAOPop
 *
 * @param vao - pointer to a GlisyVAO struct.
 */

GLuint
glisyVAOPop(GlisyVAO *vao);

/**
 * @TODO(jwerle): implement glisyVAOSplice
 *
 * @param vao   - pointer to a GlisyVAO struct.
 * @param start - index at which to start slicing.
 * @param count - length of the slice.
 */

GLuint
glisyVAOSplice(GlisyVAO *vao,
                 GLint start,
                 GLuint count);

/**
 * This function places a vao attribute into vao at the index specified by
 * location. If the location exceeds GLISY_MAX_VAO_ATTRIBS or if the vao's
 * length is already at that maximum, nothing will be done. If the vao or attr
 * params are NULL or undefined the function returns false, otherwise it returns
 * the new vao length.
 *
 * @param vao      - pointer to a GlisyVAO struct.
 * @param location - index at which to set the new vao attribute.
 * @param attr     - pointer to a GlisyVAOAttribute struct.
 */

GLuint
glisyVAOSet(GlisyVAO *vao,
              GLuint location,
              GlisyVAOAttribute *attr);

/**
 * @TODO(jwerle): implement glisyVAORemove
 *
 * @param vao      - pointer to a GlisyVAO struct.
 * @param location - index of the attr to be removed.
 */

GLuint
glisyVAORemove(GlisyVAO *vao, GLuint location);

/**
 * This function initializes and binds a GlisyVAOAttribute struct. If the
 * attribute param is NULL or undefined the function returns.
 *
 * @param attribute - pointer to a GlisyVAOAttribute struct.
 */

void
glisyVAOAttributeBind(GlisyVAOAttribute *attribute);

#endif
