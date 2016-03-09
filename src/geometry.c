#include <glisy/program.h>
#include <glisy/geometry.h>

// push a vao attribute onto the geometry attributes array
static void
_upsert_attr(glisy_geometry *geometry, glisy_vao_attribute *attribute) {
  if (!geometry) return;
  if (!attribute) return;

  // if the incoming attribute has a name then check if it
  // exists in the current geometry by comparing attribute names
  // or attribute locations
  if (attribute->name) {
    for (int i = 0; i < geometry->vao.length; ++i) {
      glisy_vao_attribute *cursor = &geometry->vao.attributes[i];
      // if the current attribute cursor has a name and it is
      // the same as the incoming attribute or if the attribute
      // cursor has no name but the locations are the same then
      // update the cursor by copying data from the incoming vao
      // attribute pointer
      if ((cursor->name && 0 == strcmp(cursor->name, attribute->name)) ||
          (!cursor->name && cursor->location == attribute->location)) {
        attribute->location = cursor->location;
#define copy(P) cursor-> P = attribute-> P;
        copy(name);
        copy(buffer.data);
        copy(buffer.type);
        copy(buffer.size);
        copy(buffer.usage);
        copy(buffer.stride);
        copy(buffer.offset);
        copy(buffer.dimension);
        copy(buffer.normalized);
#undef copy
        return;
      }
    }
  }

  glisy_vao_push(&geometry->vao, attribute);
}

void
glisy_geometry_init(glisy_geometry *geometry) {
  if (!geometry) return;

  geometry->elementsType = GL_UNSIGNED_SHORT;
  geometry->useElements = GL_FALSE;
  geometry->faceslen = 0;
  geometry->program = 0;
  geometry->dirty = GL_FALSE;
  geometry->usage = GL_STATIC_DRAW;

  glisy_vao_init(&geometry->vao);
}

void
glisy_geometry_update(glisy_geometry *geometry) {
  // index buffer object (GL_ELEMENT_ARRAY_BUFFER)
  GLuint ibo;
  // geometry program ID or current active program
  GLint pid;

  // update geometry if pointer points somewhere
  // and the geometry is dirty
  if (!geometry) return;
  if (!geometry->dirty) return;

  for (int i = 0; i < geometry->vao.length; ++i) {
    glisy_vao_attribute *attr = &geometry->vao.attributes[i];

    // if a program pointer exists and the the attributes
    // name string is set then bind the attribute location
    // to the program by name.
    if (attr->name) {
      if (geometry->program || geometry->program->id) {
        pid = geometry->program->id;
      } else {
        glGetIntegerv(GL_CURRENT_PROGRAM, &pid);
      }

      // use current attribut index as attribute location
      attr->location = i;
      // bind attribute to geometry program or the current
      // active program by location and attribute name
      glBindAttribLocation(pid,
                           attr->location,
                           attr->name);
    }
  }

  // mark clean
  geometry->dirty = GL_FALSE;

  // update VAO
  if (GL_TRUE != geometry->useElements) {
    glisy_vao_update(&geometry->vao, 0);
  } else {
    // size of the vertex faces (faces * sizeof(elementsType))
    GLsizei facesSize = geometry->faceslen * (
        // assume GLushort if GL_UNSIGNED_SHORT
        GL_UNSIGNED_SHORT == geometry->elementsType ?
        sizeof(GLushort) :
        // assume GLuint if GL_UNSIGNED_INT
        GL_UNSIGNED_INT ?
        sizeof(GLuint) :
        // otherwise assume GL_UNSIGNED_SHORT as default
        sizeof(GLushort));

    glisy_vao_update(&geometry->vao, &geometry->index);
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 // geometry vertex faces (indices)
                 facesSize, geometry->faces,

                 // buffer initialization usage type that is one of:
                 // GL_STREAM_DRAW
                 // GL_STREAM_READ
                 // GL_STREAM_COPY
                 // GL_STATIC_DRAW
                 // GL_STATIC_READ
                 // GL_STATIC_COPY
                 // GL_DYNAMIC_DRAW
                 // GL_DYNAMIC_READ
                 // GL_DYNAMIC_COPY
                 geometry->usage);
  }
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
  _upsert_attr(geometry, attr);
}

void
glisy_geometry_faces(glisy_geometry *geometry,
                     GLenum type,
                     GLuint count,
                     void *faces) {

  if (!geometry) return;
  if (!faces) return;

  geometry->elementsType = type;
  geometry->useElements = GL_TRUE;
  geometry->faceslen = count;
  geometry->faces = faces;
  geometry->dirty = GL_TRUE;
}

void
glisy_geometry_dispose(glisy_geometry *geometry) {
  if (!geometry) return;
  glisy_vao_dispose(&geometry->vao);
  glisy_buffer_dispose(&geometry->index);
}

void
glisy_geometry_bind(glisy_geometry *geometry, glisy_program *program) {
  if (!geometry) return;
  // set geometry program if given, otherwise the geometry
  // update will use the current active program
  if (program) geometry->program = program;
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
