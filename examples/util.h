#ifndef GLISY_EXAMPLE_UTIL_H
#define GLISY_EXAMPLE_UTIL_H

// common example includes
#include <glfw-shell/glfw-shell.h>
#include <glisy/glisy.h>
#include <fs/fs.h>
#include <stdio.h>

#define dtor(d) d * (M_PI / 180)
#define min(a, b) (a < b ? a : b < a ? b : a)
#define max(a, b) (a > b ? a : b > a ? b : a)

#define LoadShader(path) fs_read(path)
#define CreateProgram(vertex, fragment) ({ \
  GlisyProgram program; \
  GlisyShader vertexShader; \
  GlisyShader fragmentShader; \
  glisyProgramInit(&program); \
  glisyShaderInit(&vertexShader, GL_VERTEX_SHADER, LoadShader(vertex)); \
  glisyShaderInit(&fragmentShader, GL_FRAGMENT_SHADER, LoadShader(fragment)); \
  glisyProgramAttachShader(&program, &vertexShader); \
  glisyProgramAttachShader(&program, &fragmentShader); \
  glisyProgramLink(&program); \
  glisyProgramBind(&program); \
  (program); \
})

typedef struct Camera Camera;
struct Camera {
  GlisyUniform uProjection;
  GlisyUniform uView;

  mat4 projection;
  mat4 transform;
  mat4 view;

  vec3 position;
  vec3 target;
  vec3 up;

  struct {
    vec3 direction;
    vec3 right;
    vec3 up;
  } orientation;

  float aspect;
  float near;
  float far;
  float fov;
};

void
UpdateCameraProjectionMatrix(Camera *camera) {
  camera->projection = mat4_perspective(camera->fov,
                                        camera->aspect,
                                        camera->near,
                                        camera->far);
  glisyUniformSet(&camera->uProjection,
                    &camera->projection,
                    sizeof(camera->projection));
  glisyUniformBind(&camera->uProjection, 0);
}

void
UpdateCameraLookAt(Camera *camera) {
  vec3 target = camera->target;
  vec3 position = vec3_transform_mat4(camera->position,
                                      camera->transform);
  camera->view = mat4_lookAt(position, target, camera->up);
  glisyUniformBind(&camera->uView, 0);
  mat4_identity(camera->transform);
}

void
UpdateCamera(Camera *camera) {
  camera->orientation.direction =
    vec3_normalize(vec3_subtract(camera->position, camera->target));

  camera->orientation.right =
    vec3_normalize(vec3_cross(camera->up, camera->orientation.direction));

  glisyUniformSet(&camera->uView,
                    &camera->view,
                    sizeof(camera->view));

  UpdateCameraProjectionMatrix(camera);
  UpdateCameraLookAt(camera);
}

void
InitializeCamera(Camera *camera, int width, int height) {
  camera->position = vec3(0, 0, 0);
  camera->target = vec3(0, 0, 0);
  camera->up = vec3(0, 1, 0);

  camera->aspect = width / height;
  camera->near = 1.0f;
  camera->far = 1000.0f;
  camera->fov = 45.0f;

  mat4_identity(camera->projection);
  mat4_identity(camera->transform);
  mat4_identity(camera->view);

  glisyUniformInit(&camera->uProjection,
                     "uProjection",
                     GLISY_UNIFORM_MATRIX, 4);

  glisyUniformInit(&camera->uView,
                     "uView",
                     GLISY_UNIFORM_MATRIX, 4);

  UpdateCamera(camera);
}

#endif
