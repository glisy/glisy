#ifndef GLISY_GEOMETRY_H
#define GLISY_GEOMETRY_H

#include <glisy/vao.h>
#include <glisy/buffer.h>

/**
 * Glisy Geometry struct type.
 */

typedef struct glisy_geometry glisy_geometry;
struct glisy_geometry {

  // vertext array object
  glisy_vao vao;

  // array of vao attributes
  glisy_vao_attribute *attributes[GLISY_MAX_VAO_ATTRIBS];

  // length os vao attributes array
  GLuint attrlen;

  // index buffer
  glisy_buffer index;

  // does the geometry need an update
  GLboolean dirty;

};

/**
 * Glisy Geometry initializer.
 * @param geometry - pointer to a Glisy Geometry struct
 */

void
glisy_geometry_init(glisy_geometry *geometry);

/**
 * Glisy Geometry update.
 * @param geometry - pointer to a Glisy Geometry struct
 */

void
glisy_geometry_update(glisy_geometry *geometry);

/**
 * Glisy Geometry attributes.
 * @param geometry - pointer to a Glisy Geometry struct
 */

void
glisy_geometry_attr(glisy_geometry *geometry, GLchar *name, glisy_vao_attribute *attr);

#endif
