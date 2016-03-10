#ifndef GLISY_GEOMETRY_H
#define GLISY_GEOMETRY_H

#include <glisy/vao.h>
#include <glisy/buffer.h>
#include <glisy/program.h>

/**
 * Glisy Geometry struct type.
 */

typedef struct GlisyGeometry GlisyGeometry;
struct GlisyGeometry {
  GlisyProgram *program;
  GlisyBuffer index;
  GlisyVAO vao;

  GLboolean dirty;
  GLboolean useElements;
  GLuint faceslen;
  GLenum elementsType;
  GLenum usage;
  GLvoid *faces;
};

/**
 * This function initializes a GlisyGeometry struct with default values. Any
 * existing vao attributes bound to the geometry are cleared and the internal
 * VAO is reinitialized. If the geometry param is NULL or undefined the function
 * returns.
 *
 * @param GlisyGeometry * - A pointer to a GlisyGeometry struct.
 */

void
glisyGeometryInit(GlisyGeometry *geometry);

/**
 * Updates an existing geometry object when changes have been made. Any existing
 * VAO's are disposed of and reinitialized using GlisyVAODispose() and
 * GlisyVAOInit(). If the GlisyGeometry useElements member has been set to
 * true The VAO is updated using GlisyVAOUpdate() and the buffers generated,
 * bound and initialized using the relevant OpenGL functions. If the geometry
 * param is NULL or undefined, or the dirty member has not been set to true, the
 * function returns.
 *
 * @param GlisyGeometry * - A pointer to a GlisyGeometry struct.
 */

void
glisyGeometryUpdate(GlisyGeometry *geometry);

/**
 * Push a new GlisyVAOAttribute into a GlisyGeometry struct. This function
 * finishes by marking the geometry param as dirty so it can be passed to
 * GlisyGeometryUpdate(). If the geometry, name or attr params are NULL or
 * undefined, the function returns.
 *
 * @param GlisyGeometry *      - pointer to a GlisyGeometry struct.
 * @param name *                - pointer to a char array.
 * @param GlisyVAOAttribute * - pointer to a GlisyVAOAttribute struct.
 */

void
glisyGeometryAttr(GlisyGeometry *geometry,
                    const char *name,
                    GlisyVAOAttribute *attr);

/**
 * Setup the GlisyGeometry indices and indiceslen members to support rendering
 * faces. This function completes by setting the GlisyGeometry useElements
 * and dirty members to true so the geometry can be sent back to
 * GlisyGeometryUpdate(). If the geometry or indices params are NULL or
 * undefined, the function returns.
 *
 * @param GlisyGeometry * - pointer to a GlisyGeometry struct.
 * @param count            - count of indices for faces.
 * @param indices        * - pointer to an array of index faces.
 */

void
glisyGeometryFaces(GlisyGeometry *geometry,
                     GLenum type,
                     GLuint count,
                     GLvoid *indices);

/**
 * This function clears out the members of a geometry and disposes of its VAO
 and buffers. If the geometry param is NULL or undefined, the function returns.
 *
 * @param GlisyGeometry * - pointer to a GlisyGeometry struct.
 */

void
glisyGeometryDispose(GlisyGeometry *geometry);

/**
 * This function takes the geometry and program params, assigns the program to
 * the geometry, updates the geometry and binds it VAO. If the geometry or
 * program params are NULL or undefined, the function returns.
 *
 * @param GlisyGeometry * - pointer to a GlisyGeometry struct.
 * @param GlisyProgram  * - pointer to a GlisyProgram struct.
 */

void
glisyGeometryBind(GlisyGeometry *geometry, GlisyProgram *program);

/**
 * This function calls GlisyGeometryUpdate() and GlisyVAOUnbind() t
 * disassociate the VAO from the geometry. If the geometry param is NULL or
 * undefined, the function returns.
 *
 * @param GlisyGeometry * - pointer to a GlisyGeometry struct.
 */

void
glisyGeometryUnbind(GlisyGeometry *geometry);

/**
 * If the GlisyGeometry useElements member has been set to true this function
 * calls glDrawElements() passing the remaining params. If not, glDrawArrays()
 * is called instead. If the geometry param is NULL or undefined, the function
 * returns.
 *
 * @param GlisyGeometry * - pointer to a GlisyGeometry struct.
 * @param mode             - OpenGL mode to draw.
 * @param start            - starting element.
 * @param stop             - number of elements to draw.
 */

void
glisyGeometryDraw(GlisyGeometry *geometry,
                    GLuint mode,
                    GLuint start,
                    GLuint stop);
#endif
