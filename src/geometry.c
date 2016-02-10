#include <strings.h>
#include <glisy/geometry.h>

// push a vao attribute onto the geometry attributes array
static void
push_attr(glisy_geometry *geometry, glisy_vao_attribute *attribute) {
  if (geometry == NULL) return;
  if (attribute == NULL) return;

  if (geometry->attrlen < GLISY_MAX_VAO_ATTRIBS) {
    geometry->attributes[geometry->attrlen++] = attribute;
  }
}

/**
 * Glisy Geometry initializer.
 */

void
glisy_geometry_init(glisy_geometry *geometry) {
  if (geometry == NULL) return;

  geometry->attrlen = 0;
  geometry->dirty = GL_FALSE;

  memset(&geometry->attributes, 0, sizeof(glisy_vao_attribute *) * GLISY_MAX_VAO_ATTRIBS);
  glisy_vao_init(&geometry->vao);
}

/**
 * Glisy Geometry update.
 */

void
glisy_geometry_update(glisy_geometry *geometry) {
  if (geometry == NULL) return;
  if (!geometry->dirty) return;

  glisy_vao_dispose(&geometry->vao);
  glisy_vao_init(&geometry->vao);
  //@TODO(jwerle): complete me
}

/**
 * Glisy Geometry attributes.
 */

void
glisy_geometry_attr(glisy_geometry *geometry, GLchar *name, glisy_vao_attribute *attr) {
  if (geometry == NULL) return;
  if (name == NULL) return;

  geometry->dirty = GL_TRUE;
  attr->name = name;
  push_attr(geometry, attr);
}
