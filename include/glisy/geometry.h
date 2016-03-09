#ifndef GLISY_GEOMETRY_H
#define GLISY_GEOMETRY_H

#include <glisy/vao.h>
#include <glisy/buffer.h>
#include <glisy/program.h>

/**
 * Glisy Geometry struct type.
 */

typedef struct glisy_geometry glisy_geometry;
struct glisy_geometry {
  glisy_vao vao;
  GLuint faceslen;
  glisy_buffer index;
  GLboolean dirty;
  GLenum elementsType;
  GLenum usage;
  GLvoid *faces;
  GLboolean useElements;
  glisy_program *program;
};

/**
 * This function initializes a glisy_geometry struct with default values. Any
 * existing vao attributes bound to the geometry are cleared and the internal
 * VAO is reinitialized. If the geometry param is NULL or undefined the function
 * returns.
 *
 * @param glisy_geometry * - A pointer to a glisy_geometry struct.
 */

void
glisy_geometry_init(glisy_geometry *geometry);

/**
 * Updates an existing geometry object when changes have been made. Any existing
 * VAO's are disposed of and reinitialized using glisy_vao_dispose() and
 * glisy_vao_init(). If the glisy_geometry useElements member has been set to
 * true The VAO is updated using glisy_vao_update() and the buffers generated,
 * bound and initialized using the relevant OpenGL functions. If the geometry
 * param is NULL or undefined, or the dirty member has not been set to true, the
 * function returns.
 *
 * @param glisy_geometry * - A pointer to a glisy_geometry struct.
 */

void
glisy_geometry_update(glisy_geometry *geometry);

/**
 * Push a new glisy_vao_attribute into a glisy_geometry struct. This function
 * finishes by marking the geometry param as dirty so it can be passed to
 * glisy_geometry_update(). If the geometry, name or attr params are NULL or
 * undefined, the function returns.
 *
 * @param glisy_geometry *      - pointer to a glisy_geometry struct.
 * @param name *                - pointer to a char array.
 * @param glisy_vao_attribute * - pointer to a glisy_vao_attribute struct.
 */

void
glisy_geometry_attr(glisy_geometry *geometry,
                    const char *name,
                    glisy_vao_attribute *attr);

/**
 * Setup the glisy_geometry indices and indiceslen members to support rendering
 * faces. This function completes by setting the glisy_geometry useElements
 * and dirty members to true so the geometry can be sent back to
 * glisy_geometry_update(). If the geometry or indices params are NULL or
 * undefined, the function returns.
 *
 * @param glisy_geometry * - pointer to a glisy_geometry struct.
 * @param count            - count of indices for faces.
 * @param indices        * - pointer to an array of index faces.
 */

void
glisy_geometry_faces(glisy_geometry *geometry,
                     GLenum type,
                     GLuint count,
                     GLvoid *indices);

/**
 * This function clears out the members of a geometry and disposes of its VAO
 and buffers. If the geometry param is NULL or undefined, the function returns.
 *
 * @param glisy_geometry * - pointer to a glisy_geometry struct.
 */

void
glisy_geometry_dispose(glisy_geometry *geometry);

/**
 * This function takes the geometry and program params, assigns the program to
 * the geometry, updates the geometry and binds it VAO. If the geometry or
 * program params are NULL or undefined, the function returns.
 *
 * @param glisy_geometry * - pointer to a glisy_geometry struct.
 * @param glisy_program  * - pointer to a glisy_program struct.
 */

void
glisy_geometry_bind(glisy_geometry *geometry, glisy_program *program);

/**
 * This function calls glisy_geometry_update() and glisy_vao_unbind() t
 * disassociate the VAO from the geometry. If the geometry param is NULL or
 * undefined, the function returns.
 *
 * @param glisy_geometry * - pointer to a glisy_geometry struct.
 */

void
glisy_geometry_unbind(glisy_geometry *geometry);

/**
 * If the glisy_geometry useElements member has been set to true this function
 * calls glDrawElements() passing the remaining params. If not, glDrawArrays()
 * is called instead. If the geometry param is NULL or undefined, the function
 * returns.
 *
 * @param glisy_geometry * - pointer to a glisy_geometry struct.
 * @param mode             - OpenGL mode to draw.
 * @param start            - starting element.
 * @param stop             - number of elements to draw.
 */

void
glisy_geometry_draw(glisy_geometry *geometry,
                    GLuint mode,
                    GLuint start,
                    GLuint stop);

#endif
