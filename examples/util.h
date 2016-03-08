#ifndef GLISY_EXAMPLE_UTIL_H
#define GLISY_EXAMPLE_UTIL_H

// common example includes
#include <glisy/glisy.h>
#include <GLFW/glfw3.h>
#include <fs/fs.h>
#include <stdio.h>

#define dtor(d) d * (M_PI / 180)
#define min(a, b) (a < b ? a : b < a ? b : a)
#define max(a, b) (a > b ? a : b > a ? b : a)

#define GL_CONTEXT_INIT() \
  if (!glfwInit()) return 1; \
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); \
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); \
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); \
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, 0, 0); \
  if (!window) { return glfwTerminate(), 1; } \
  glfwMakeContextCurrent(window); \
  printf("OpenGL %s, GLSL %s\n", \
      glGetString(GL_VERSION), \
      glGetString(GL_SHADING_LANGUAGE_VERSION));

#define GL_RENDER(cb) { \
  while (!glfwWindowShouldClose(window)) { \
    int width; \
    int height; \
    glfwGetFramebufferSize(window, &width, &height); \
    glViewport(0, 0, width, height); \
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); \
    glDepthMask(GL_TRUE);\
    glEnable(GL_DEPTH_TEST); \
    glEnable(GL_CULL_FACE); \
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); \
    { cb } \
    glfwSwapBuffers(window); \
    glfwPollEvents(); \
  } \
  glfwTerminate(); \
}

#define LoadShader(path) fs_read(path)
#define CreateProgram(vertex, fragment) ({ \
  glisy_program program; \
  glisy_shader vertexShader; \
  glisy_shader fragmentShader; \
  glisy_program_init(&program); \
  glisy_shader_init(&vertexShader, GL_VERTEX_SHADER, LoadShader(vertex)); \
  glisy_shader_init(&fragmentShader, GL_FRAGMENT_SHADER, LoadShader(fragment)); \
  glisy_program_attach_shader(&program, &vertexShader); \
  glisy_program_attach_shader(&program, &fragmentShader); \
  glisy_program_link(&program); \
  glisy_program_bind(&program); \
  (program); \
})

typedef struct Camera Camera;
struct Camera {
  glisy_uniform uProjection;
  glisy_uniform uView;

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
  glisy_uniform_set(&camera->uProjection,
                    &camera->projection,
                    sizeof(camera->projection));
  glisy_uniform_bind(&camera->uProjection, 0);
}

void
UpdateCameraLookAt(Camera *camera) {
  vec3 target = vec3_transform_mat4(camera->target,
                                    camera->transform);
  camera->view = mat4_lookAt(target,
                             camera->position,
                             camera->up);
  glisy_uniform_bind(&camera->uView, 0);
  mat4_identity(camera->transform);
}

void
UpdateCamera(Camera *camera) {
  camera->orientation.direction =
    vec3_normalize(vec3_subtract(camera->position, camera->target));

  camera->orientation.right =
    vec3_normalize(vec3_cross(camera->up, camera->orientation.direction));

  glisy_uniform_set(&camera->uView,
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
  camera->far = 100.0f;
  camera->fov = 45.0f;

  mat4_identity(camera->projection);
  mat4_identity(camera->transform);
  mat4_identity(camera->view);

  glisy_uniform_init(&camera->uProjection,
                     "uProjection",
                     GLISY_UNIFORM_MATRIX, 4);

  glisy_uniform_init(&camera->uView,
                     "uView",
                     GLISY_UNIFORM_MATRIX, 4);

  UpdateCamera(camera);
}

#endif
