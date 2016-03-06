#include "util.h"

#define WINDOW_NAME "GridExample"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

typedef struct Grid Grid;
struct Grid {
  mat4 model;
};

// glfw
static GLFWwindow *window;

// glisy
static glisy_program program;
static glisy_uniform uProjection;
static glisy_uniform uModel;
static glisy_uniform uView;

// objects
static Camera camera;
static Grid grid;

int
main(void) {
  GL_CONTEXT_INIT();
  program = CreateProgram("grid.v.glsl", "grid.f.glsl");

  camera.position = vec3(0, 0, -1);
  camera.target = vec3(0, 0, 0);
  camera.center = vec3(0, 0, 0);
  camera.up = vec3(0, 1, 0);

  camera.aspect = WINDOW_WIDTH / WINDOW_HEIGHT;
  camera.near = 1.0f;
  camera.far = 1000.0f;
  camera.fov = 45.0f;

  UpdateCameraProjectionMatrix(&camera);
  UpdateCameraLookAt(&camera);

  glisy_uniform_init(&uProjection, "uProjection", GLISY_UNIFORM_MATRIX, 4);
  glisy_uniform_init(&uModel, "uModel", GLISY_UNIFORM_MATRIX, 4);
  glisy_uniform_init(&uView, "uView", GLISY_UNIFORM_MATRIX, 4);

  mat4_identity(grid.model);

  GL_RENDER({
    camera.aspect = width / height;
    UpdateCameraProjectionMatrix(&camera);
    UpdateCameraLookAt(&camera);

    glisy_uniform_set(&uProjection, &camera.projection, sizeof(camera.projection));
    glisy_uniform_set(&uView, &camera.view, sizeof(camera.view));
    glisy_uniform_set(&uModel, &grid.model, sizeof(grid.model));

    glisy_uniform_bind(&uProjection, &program);
    glisy_uniform_bind(&uModel, &program);
    glisy_uniform_bind(&uView, &program);
  });

  return 0;
}
