#ifndef GLISY_PROGRAM_H
#define GLISY_PROGRAM_H

#include <glisy/gl.h>
#include <glisy/shader.h>

/**
 * Glisy Program struct type.
 *
 * This struct stores the ID that is used by the GL functions that control
 * the creation, manipulation and destruction of GL programs.
 */

typedef struct glisy_program glisy_program;
struct glisy_program {

  // GL Program ID.
  GLuint id;

};

/**
 * Glisy Program initializer.
 * @param program - pointer to a Glisy Program struct
 *
 * This function uses glCreateProgram() to initialize a GL program. It will
 * return false if the program pointer argument is NULL or the program cannot
 * properly be initialized, otherwise it returns true.
 */

GLboolean
glisy_program_init(glisy_program *program);

/**
 * Attaches a Glisy Vertext or Fragment Shader to a Glisy Program.
 * @param program - pointer to a Glisy Program struct
 * @param shader  - pointer to a Glisy Vertex or Fragment Shader
 *
 * This function will return false if the Glisy Program or Shader is NULL
 * otherwise it returns true.
 */

GLboolean
glisy_program_attach_shader(const glisy_program *program, const glisy_shader *shader);

/**
 * Glisy Program link.
 * @param program - pointer to a Glisy Program struct
 *
 * This function uses glLinkProgram() to link attached Glisy Vertex/Fragment
 * Shaders. If the Glisy Program argument is NULL or if the result of
 * glGetProgramiv() is a failure it will return false. If the program cannot
 * be properly linked, the Glisy Program Delete function is called to destroy
 * the program.
 */

GLboolean
glisy_program_link(glisy_program *program);

/**
 * Glisy Program delete.
 * @param program - pointer to a Glisy Program struct
 *
 * This function uses glDeleteProgram() to destroy a Glisy Program. If the program
 * argument is NULL or the ID member is 0 false is returned, otherwise it returns true.
 */

GLboolean
glisy_program_delete(glisy_program *program);

#endif
