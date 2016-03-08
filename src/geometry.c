#include <strings.h>
#include <glisy/program.h>
#include <glisy/geometry.h>

// push a vao attribute onto the geometry attributes array
static void
upsert_attr(glisy_geometry *geometry, glisy_vao_attribute *attribute) {
  if (!geometry) return;
  if (!attribute) return;

  // if attr has a name and exists, just update it
  if (attribute->name) {
    for (int i = 0; i < geometry->attrlen; ++i) {
      glisy_vao_attribute *cursor = &geometry->attributes[i];
      if ((cursor->name && 0 == strcmp(cursor->name, attribute->name)) ||
          (!cursor->name && cursor->location == attribute->location)) {
        attribute->location = cursor->location;
#define copy(P) cursor-> P = attribute-> P;
        copy(name);
        copy(buffer.type);
        copy(buffer.size);
        copy(buffer.usage);
        copy(buffer.stride);
        copy(buffer.offset);
        copy(buffer.dimension);
        copy(buffer.normalized);
        memcpy(cursor->buffer.data, attribute->buffer.data, attribute->buffer.size);
#undef copy
        return;
      }
    }
  }

  if (geometry->attrlen < GLISY_MAX_VAO_ATTRIBS) {
    memcpy(&geometry->attributes[geometry->attrlen++],
           attribute,
           sizeof(glisy_vao_attribute));
  }
}

void
glisy_geometry_init(glisy_geometry *geometry) {
  if (!geometry) return;

  geometry->elementsType = GL_UNSIGNED_SHORT;
  geometry->useElements = GL_FALSE;
  geometry->faceslen = 0;
  geometry->attrlen = 0;
  geometry->program = 0;
  geometry->dirty = GL_FALSE;

  memset(&geometry->attributes, 0, sizeof(glisy_vao_attribute *) * GLISY_MAX_VAO_ATTRIBS);
  glisy_vao_init(&geometry->vao);
}

void
glisy_geometry_update(glisy_geometry *geometry) {
  // index buffer object (GL_ELEMENT_ARRAY_BUFFER)
  GLuint ibo;
  if (!geometry) return;
  if (!geometry->dirty) return;

  // dispose and reinitialize VAO
  glisy_vao_dispose(&geometry->vao);
  glisy_vao_init(&geometry->vao);

  for (int i = 0; i < geometry->attrlen; ++i) {
    glisy_vao_attribute *attr = &geometry->attributes[i];

    // push geometry attribute to VAO
    glisy_vao_push(&geometry->vao, attr);

    // if a program pointer exists and the the attributes
    // name string is set then bind the attribute location
    // to the program by name.
    if (attr->name && geometry->program && geometry->program->id) {
      attr->location = i;
      glBindAttribLocation(geometry->program->id,
                           attr->location,
                           attr->name);
    }
  }

  // update VAO
  if (geometry->useElements) {
    glisy_vao_update(&geometry->vao, &geometry->index);
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 geometry->faceslen * (
                   GL_UNSIGNED_SHORT == geometry->elementsType ?
                   sizeof(GLushort) :
                   GL_UNSIGNED_INT ? sizeof(GLuint) : 0
                 ),
                 geometry->faces,
                 GL_STATIC_DRAW);
  } else {
    glisy_vao_update(&geometry->vao, 0);
  }

  geometry->dirty = GL_FALSE;
}

void
glisy_geometry_attr(glisy_geometry *geometry,
                    const char *name,
                    glisy_vao_attribute *attr) {
  if (!geometry) return;
  if (!name) return;
  if (!attr) return;

  attr->name = name;
  geometry->dirty = GL_TRUE;
  upsert_attr(geometry, attr);
}

void
glisy_geometry_faces(glisy_geometry *geometry,
                     GLenum type,
                     GLuint count,
                     void *faces) {

  if (!geometry) return;
  if (!faces) return;
  geometry->elementsType = type;
  geometry->faceslen = count;
  geometry->faces = faces;
  geometry->useElements = GL_TRUE;
  geometry->dirty = GL_TRUE;
}

void
glisy_geometry_dispose(glisy_geometry *geometry) {
  if (!geometry) return;
  geometry->attrlen = 0;
  glisy_vao_dispose(&geometry->vao);
  glisy_buffer_dispose(&geometry->index);
}

void
glisy_geometry_bind(glisy_geometry *geometry, glisy_program *program) {
  if (!geometry) return;
  if (!program)  return;
  geometry->program = program;
  glisy_geometry_update(geometry);
  glisy_vao_bind(&geometry->vao);
}

void
glisy_geometry_unbind(glisy_geometry *geometry) {
  if (!geometry) return;
  glisy_geometry_update(geometry);
  glisy_vao_unbind(&geometry->vao);
}

void
glisy_geometry_draw(glisy_geometry *geometry,
                    GLuint mode,
                    GLuint start,
                    GLuint stop) {
  if (!geometry) return;
  glisy_geometry_update(geometry);
  if (geometry->vao.useElements) {
    glDrawElements(mode,
                  stop - start,
                  geometry->elementsType, 0);

  } else {
    glDrawArrays(mode, start, stop - start);
  }
}
