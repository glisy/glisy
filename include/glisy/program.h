#ifndef GLISY_PROGRAM_H
#define GLISY_PROGRAM_H

#include <glisy/gl.h>
#include <glisy/shader.h>

/**
 * Glisy Program struct type.
 */

typedef struct glisy_program glisy_program;
struct glisy_program {

  // GL Program ID.
  GLuint id;

};

/**
 * This function uses glCreateProgram() to initialize a GL program. If the
 * program param is NULL or undefined, or the program cannot properly be
 * initialized, the function returns false, otherwise it returns true.
 *
 * @param program * - pointer to a glisy_program struct.
 */

GLboolean
glisy_program_init(glisy_program *program);

/**
 * This function uses glAttachShader() to attach a glisy_shader to a glisy_program.
 * It will return false if the program or shader param is NULL or undefined,
 * otherwise it returns true.
 *
 * @param program * - pointer to a glisy_program struct.
 * @param shader  * - pointer to a vertex or fragment glisy_shader.
 */

GLboolean
glisy_program_attach_shader(const glisy_program *program, const glisy_shader *shader);

/**
 * This function uses glLinkProgram() to link attached vertex and fragment
 * glisy_shaders. If the program param is NULL or undefined, if the result of
 * glGetProgramiv() is a failure, or if the program cannot be properly linked,
 * it will return false, otherwise it returns true. glisy_program_delete() is
 * called to destroy the program on failure.
 *
 * @param program * - pointer to a glisy_program struct.
 */

GLboolean
glisy_program_link(glisy_program *program);

/**
 * This function uses glDeleteProgram() to destroy a glisy_program. If the
 * program param is NULL or undefined, or the glisy_program ID member is 0,
 * false is returned, otherwise it returns true.
 *
 * @param program * - pointer to a glisy_program struct.
 */

GLboolean
glisy_program_delete(glisy_program *program);

#endif
