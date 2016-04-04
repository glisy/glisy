#ifndef GLISY_PROGRAM_H
#define GLISY_PROGRAM_H

#include <glisy/gl.h>
#include <glisy/shader.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Glisy Program struct type.
 */

typedef struct GlisyProgram GlisyProgram;
struct GlisyProgram {
  // GL Program ID.
  GLuint id;
};

/**
 * This function uses glCreateProgram() to initialize a GL program. If the
 * program param is NULL or undefined, or the program cannot properly be
 * initialized, the function returns false, otherwise it returns true.
 *
 * @param program * - pointer to a GlisyProgram struct.
 */

GLboolean
glisyProgramInit(GlisyProgram *program);

/**
 * This function uses glAttachShader() to attach a GlisyShader to a GlisyProgram.
 * It will return false if the program or shader param is NULL or undefined,
 * otherwise it returns true.
 *
 * @param program * - pointer to a GlisyProgram struct.
 * @param shader  * - pointer to a vertex or fragment GlisyShader.
 */

GLboolean
glisyProgramAttachShader(const GlisyProgram *program, const GlisyShader *shader);

/**
 * This function uses glLinkProgram() to link attached vertex and fragment
 * GlisyShaders. If the program param is NULL or undefined, if the result of
 * glGetProgramiv() is a failure, or if the program cannot be properly linked,
 * it will return false, otherwise it returns true. glisyProgramDelete() is
 * called to destroy the program on failure.
 *
 * @param program * - pointer to a GlisyProgram struct.
 */

GLboolean
glisyProgramLink(GlisyProgram *program);

/**
 * Bind program and use program. This function calls glUseProgram internally.
 */

GLboolean
glisyProgramBind(GlisyProgram *program);

/**
 * This function uses glDeleteProgram() to destroy a GlisyProgram. If the
 * program param is NULL or undefined, or the GlisyProgram ID member is 0,
 * false is returned, otherwise it returns true.
 *
 * @param program * - pointer to a GlisyProgram struct.
 */

GLboolean
glisyProgramDelete(GlisyProgram *program);

#ifdef __cplusplus
}
#endif

#endif
