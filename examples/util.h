#ifndef GLISY_EXAMPLE_UTIL_H
#define GLISY_EXAMPLE_UTIL_H

// common example includes
#include <glfw-shell/glfw-shell.h>
#include <glisy/program.h>
#include <glisy/uniform.h>
#include <glisy/shader.h>
#include <fs/fs.h>
#include <stdio.h>

#define dtor(d) d * (M_PI / 180)
#define min(a, b) (a < b ? a : b < a ? b : a)
#define max(a, b) (a > b ? a : b > a ? b : a)

#define LoadShader(path) fs_read(path)
#define CreateProgram(vertex, fragment) ({   \
  GlisyProgram program;                      \
  GlisyShader vertexShader;                  \
  GlisyShader fragmentShader;                \
  glisyProgramInit(&program);                \
  glisyShaderInit(&vertexShader,             \
                  GL_VERTEX_SHADER,          \
                  LoadShader(vertex));       \
  glisyShaderInit(&fragmentShader,           \
                  GL_FRAGMENT_SHADER,        \
                  LoadShader(fragment));     \
  glisyProgramAttachShader(&program,         \
                           &vertexShader);   \
  glisyProgramAttachShader(&program,         \
                           &fragmentShader); \
  glisyProgramLink(&program);                \
  glisyProgramBind(&program);                \
  (program);                                 \
})

void
UpdateCamera(GlisyCamera *camera,
             GlisyProgram *program,
             mat4 transform,
             float fov,
             float aspect,
             float near,
             float far) {
  static mat4 projection;
  static mat4 view;
  GLint pid = program->id;

  glisyCameraUpdate(camera);
  glisyProgramBind(program);

  projection = mat4_perspective(fov, aspect, near, far);
  view = glisyCameraGetViewMatrix(camera);
  view = mat4_multiply(view, transform);
  if (glGetUniformLocation(pid, "view") > -1) {
    GlisyUniform uview; {
      glisyUniformInit(&uview, "view", GLISY_UNIFORM_MATRIX, 4);
      glisyUniformSet(&uview, &view, sizeof(mat4));
      glisyUniformBind(&uview, 0);
    }
  }

  if (glGetUniformLocation(pid, "projection") > -1) {
    GlisyUniform uprojection; {
      glisyUniformInit(&uprojection, "projection", GLISY_UNIFORM_MATRIX, 4);
      glisyUniformSet(&uprojection, &projection, sizeof(mat4));
      glisyUniformBind(&uprojection, 0);
    }
  }
}

#endif
