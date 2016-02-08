#ifndef GLISY_SHADER_H
#define GLISY_SHADER_H

#include <stdio.h>
#include <glisy/gl.h>

#define GLISY_GLSL_SHADER_HEADER                           \
  "uniform mat3 gl_NormalMatrix;"                          \
  "uniform mat4 gl_ModelViewMatrix;"                       \
  "uniform mat4 gl_ProjectionMatrix;"                      \
  "uniform mat4 gl_ModelViewProjectionMatrix;"             \
  "uniform mat4 gl_ModelViewMatrixInverse;"                \
  "uniform mat4 gl_ProjectionMatrixInverse;"               \
  "uniform mat4 gl_ModelViewProjectionMatrixInverse;"      \

#define GLISY_GLSL_VERTEX_SHADER_HEADER GLISY_GLSL_SHADER_HEADER     \
  "attribute vec4 gl_TexCoord;"                                      \
  "attribute vec4 gl_Vertex;"                                        \
  "attribute vec3 gl_Normal;"                                        \
  "attribute vec4 gl_Color;"                                         \
  "vec4 ftransform() {"                                              \
    "return gl_ModelViewProjectionMatrix * gl_Vertex;"               \
  "};"                                                               \

#define GLISY_GLSL_FRAGMENT_SHADER_HEADER                            \
  "precision highp float;"                                           \
  GLISY_GLSL_SHADER_HEADER                                           \

/**
 * Glisy Shader structure type.
 */

typedef struct glisy_shader glisy_shader;
struct glisy_shader {

  // Shader GLSL source buffer.
  char source[BUFSIZ];

  // Shader source type.
  GLuint type;

  // Shader source ID.
  GLuint id;

};

/**
 * Glisy Shader initializer.
 * @param shader - pointer to a Glisy Shader struct
 * @param type   - GL vertex or fragment shader type enum
 * @param source - pointer to a string buffer containing GLSL source
 *
 * This function uses glCreateShader(), glShaderSource(), and glShaderCompile()
 * to initializes a Glisy Vertex or Fragment Shader that can be attached to a
 * Glisy Program. It will return false if glGetShaderiv() reports a failure to
 * compile, shader is NULL, or shader->id is 0. Otherwise it will return true.
 * if glGetShaderiv() reports a failure glDeleteShader() is called to destroy
 * the shader.
 */

GLboolean
glisy_shader_init(glisy_shader *shader, GLuint type, const char *source);

#endif
