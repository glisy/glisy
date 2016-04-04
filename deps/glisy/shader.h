#ifndef GLISY_SHADER_H
#define GLISY_SHADER_H

#include <stdio.h>
#include <glisy/gl.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Glisy Shader structure type.
 */

typedef struct GlisyShader GlisyShader;
struct GlisyShader {

  // Shader GLSL source buffer.
  char *source;

  // Shader source type.
  GLuint type;

  // Shader source ID.
  GLuint id;

};

/**
 * This function uses glCreateShader(), glShaderSource(), and glShaderCompile()
 * to initializes a Glisy Vertex or Fragment Shader that can be attached to a
 * Glisy Program. It will return false if glGetShaderiv() reports a failure to
 * compile, shader is NULL, or shader->id is 0. Otherwise it will return true.
 * if glGetShaderiv() reports a failure glDeleteShader() is called to destroy
 * the shader.
 *
 * @param shader * - pointer to a GlisyShader struct.
 * @param type     - GL vertex or fragment shader type enum.
 * @param source * - pointer to a string buffer containing GLSL source.
 */

GLboolean
glisyShaderInit(GlisyShader *shader, GLuint type, const char *source);

#ifdef __cplusplus
}
#endif

#endif
