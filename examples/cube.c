#include <glisy/geometry.h>
#include <glisy/camera.h>
#include <glisy/color.h>
#include <glisy/math.h>
#include "util.h"

#define WINDOW_NAME "CubeExample"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 640

// model
typedef struct Cube Cube;
struct Cube {
  // glisy
  GlisyGeometry geometry;
  GlisyUniform model;

  // gl
  vec3 position;
  mat4 transform;
  mat4 rotation;

  // vao
  int faceslen;
};

static mat4 transform;
static float aspect = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;
static float near = 1.0;
static float far = 1000.0;
static float fov = M_PI / 2.0;
static Cube cube;

static GlisyProgram program;
static GlisyCamera camera;
static GLFWwindow *window;

// forward decl
static void InitializeCube(Cube *cube);
static void UpdateCube(Cube *cube);
static void RotateCube(Cube *cube, float radians, vec3 axis);

// cube constructor
void
InitializeCube(Cube *cube) {
  const vec3 vertices[] = {
    vec3(-0.5, -0.5, +0.5),
    vec3(+0.5, -0.5, +0.5),
    vec3(-0.5, +0.5, +0.5),
    vec3(+0.5, +0.5, +0.5),

    vec3(-0.5, -0.5, -0.5),
    vec3(+0.5, -0.5, -0.5),
    vec3(-0.5, +0.5, -0.5),
    vec3(+0.5, +0.5, -0.5),
  };

  // init color
  GlisyColor color;
  glisyColorInit(&color, "blue", 0);

  // init uniforms
  GlisyUniform ucolor;
  glisyUniformInit(&ucolor, "color", GLISY_UNIFORM_VECTOR, 3);
  glisyUniformInit(&cube->model, "model", GLISY_UNIFORM_MATRIX, 4);

  // set uniforms
  glisyUniformSet(&ucolor, &vec3(color.r, color.g, color.b), sizeof(vec3));
  glisyUniformBind(&ucolor, 0);

  const GLushort faces[] = {
    0, 1, 3, 0, 3, 2,
    1, 5, 7, 1, 7, 3,
    5, 4, 6, 5, 6, 7,
    4, 0, 2, 4, 2, 6,
    4, 5, 1, 4, 1, 0,
    2, 3, 7, 2, 7, 6,
  };

  cube->position = vec3(0, 0, 0);
  cube->faceslen = sizeof(faces) / sizeof(GLushort);
  GLuint size = sizeof(vertices);

  GlisyVAOAttribute position;
  memset(&position, 0, sizeof(position));
  position.buffer.data = (void *) vertices;
  position.buffer.type = GL_FLOAT;
  position.buffer.size = size;
  position.buffer.usage = GL_STATIC_DRAW;
  position.buffer.dimension = 3;

  // init matrices
  mat4_identity(cube->transform);
  mat4_identity(cube->rotation);

  // init vao attributes
  glisyGeometryInit(&cube->geometry);
  glisyGeometryAttr(&cube->geometry, "position", &position);
  glisyGeometryFaces(&cube->geometry,
                       GL_UNSIGNED_SHORT,
                       cube->faceslen,
                       (void *) faces);

  // update geometry with attributes and faces
  glisyGeometryUpdate(&cube->geometry);

  UpdateCube(cube);
}

void
UpdateCube(Cube *cube) {
  mat4 model;
  mat4_identity(model);
  model = mat4_multiply(model, cube->rotation);
  glisyUniformSet(&cube->model, &model, sizeof(model));
  glisyUniformBind(&cube->model, 0);
}

void
DrawCube(Cube *cube) {
  UpdateCube(cube);
  glisyGeometryBind(&cube->geometry, 0);
  glisyGeometryDraw(&cube->geometry, GL_TRIANGLES, 0, cube->faceslen);
  glisyGeometryUnbind(&cube->geometry);
}

void
RotateCube(Cube *cube, float radians, vec3 axis) {
  (void) mat4_rotate(cube->rotation, radians, axis);
}

int
main(void) {

  // init gl
  GLFW_SHELL_CONTEXT_INIT(3, 2);
  GLFW_SHELL_WINDOW_INIT(window, WINDOW_WIDTH, WINDOW_HEIGHT);
  glfwSetWindowUserPointer(window, &camera);

  // create shader program
  program = CreateProgram("cube.v.glsl", "cube.f.glsl");

  // init objects
  InitializeCube(&cube);

  // bind current shader program
  glisyProgramBind(&program);

  // configure camera
  glisyCameraInitialize(&camera);
  transform = mat4_identity(mat4());
  camera.position = vec3(0, 0, -2);
  UpdateCamera(&camera, &program, transform, fov, aspect, near, far);

  GLFW_SHELL_RENDER(window, {
    const float time = glfwGetTime();
    const float angle = time * 45.0f;
    const float radians = dtor(angle);
    const vec3 rotation = vec3(0, 1, 0);

    aspect = (float) width / (float) height;

    UpdateCamera(&camera, &program, transform, fov, aspect, near, far);
    RotateCube(&cube, radians, vec3_negate(rotation));
    DrawCube(&cube);
  });

  return 0;
}
