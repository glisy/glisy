#ifndef GLISY_PROGRAM_H
#define GLISY_PROGRAM_H

#include <glisy/gl.h>
#include <glisy/shader.h>

/**
 * glisy program.
 */

typedef struct glisy_program glisy_program;
struct glisy_program {

  /**
   * GL Program ID.
   */

  GLuint id;
};

GLboolean
glisy_program_init(glisy_program *program);

GLboolean
glisy_program_attach_shader(const glisy_program *program, const glisy_shader *shader);

GLboolean
glisy_program_link(glisy_program *program);

GLboolean
glisy_program_delete(glisy_program *program);

#endif
