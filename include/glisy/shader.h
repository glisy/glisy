#ifndef GLISY_SHADER_H
#define GLISY_SHADER_H

#include <stdio.h>

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

typedef struct glisy_shader glisy_shader;
struct glisy_shader {
  const unsigned char source[BUFSIZ];
  unsigned int type;
};


int
glisy_shader_init (glisy_shader, const char *, const char *);

#endif
