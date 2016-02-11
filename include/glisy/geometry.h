#ifndef GLISY_GEOMETRY_H
#define GLISY_GEOMETRY_H

#include <glisy/vao.h>
#include <glisy/buffer.h>
#include <glisy/program.h>

/**
 * Geometry structure to abstract interaction
 * with the VAO (vertex array object) and OpenGL
 * buffer objects (ARRAY_BUFFER, ELEMENT_ARRAY_BUFFER, etc)
 */

typedef struct glisy_geometry glisy_geometry;
struct glisy_geometry {

  // vertext array object
  glisy_vao vao;

  // array of vao attributes
  glisy_vao_attribute attributes[GLISY_MAX_VAO_ATTRIBS];

  // length of vao attributes array
  GLuint attrlen;

  // length of vertices needed to draw faces
  GLuint faceslen;

  // index buffer
  glisy_buffer index;

  // does the geometry need an update
  GLboolean dirty;

  // GL element type (GL_INT, GL_UNSIGNED_SHORT, etc)
  GLenum elementsType;

  // predicate to indicate that the geometry should
  // tell the underlying VAO to use elements for the
  // ELEMENT_ARRAY_BUFFER
  GLboolean useElements;

  // Bound pointer a glisy_program
  glisy_program *program;
};

/**
 * Initializes a pointer to a glisy_geometry structure. This function
 * sets the default element type to GL_UNSIGNED_SHORT. The faces vertices
 * length and attribute length is reset to 0. An existing attributes
 * bound to the geometry are cleared and the internal VAO is reinitialized.
 *
 * @param glisy_geometry * - A pointer to a glisy_geometry struct.
 */

void
glisy_geometry_init(glisy_geometry *geometry);

/**
 * Updates geometry VAO. The internal VAO is disposed and all bound attributes
 * to the geometry are bound to the VAO again. If the the geometry should use
 * elements then the geometry index buffer is given to the internal VAO when
 * it is updated.
 *
 * @param glisy_geometry * - A pointer to a glisy_geometry struct.
 */

void
glisy_geometry_update(glisy_geometry *geometry);

/**
 * Glisy Geometry attributes.
 * @param geometry - pointer to a Glisy Geometry struct
 */

void
glisy_geometry_attr(glisy_geometry *geometry,
                    char *name,
                    glisy_vao_attribute *attr);

/**
 */

void
glisy_geometry_faces(glisy_geometry *geometry,
                     glisy_vao_attribute *attr);

/**
 */

void
glisy_geometry_dispose(glisy_geometry *geometry);

/**
 */

void
glisy_geometry_bind(glisy_geometry *geometry, glisy_program *program);

/**
 */

void
glisy_geometry_unbind(glisy_geometry *geometry);

/**
 */

void
glisy_geometry_draw(glisy_geometry *geometry,
                    GLuint mode,
                    GLuint start,
                    GLuint stop);

#endif
